#include "savemanager.h"
#include <string.h>
#include <string>
#include <QDialog>
#include <QMessageBox>

//MultiSave
MultiSave::MultiSave(const std::string& path)
{
    if(path.find("Hyperdimension Neptunia Re;Birth1") != std::string::npos)
    {
        m_reBirthVersion = REBIRH1;
    }
    switch(m_reBirthVersion)
    {
    case REBIRH1:
        rb1SaveManager = new ReBirth1::ReBirth1Manager(path);
        m_currentManager = rb1SaveManager;
        break;
    default:
        //PANIC!
        //std::cout << "Extreme panic - game version out of bounds??????" << std::endl;
        QMessageBox messageBox;
        messageBox.critical(0,"Invalid SavaData Directory","The selected folder doesn't contain Neptune Save Data!");
        messageBox.setFixedSize(500,200);
        break;
        //exit(1);
    }
}


MultiSave::~MultiSave()
{
    if(rb1SaveManager != 0x0)
    {
        delete rb1SaveManager;
    }
    /*
    if(m_rb2SaveManager != 0x0)
    {
        delete rb2SaveManager;
    }*/
    /*
    if(m_rb3SaveManager != 0x0)
    {
        delete rb3SaveManager;
    }
    */
}

ReBirthVersion MultiSave::GetRebirthVersion()
{
    return m_reBirthVersion;
}

std::vector<std::string> MultiSave::ItereateSlots()
{
    if(m_currentManager == 0x0)
    {
        std::cout << "No manager Loaded -> Please create a new MultiSave object" << std::endl;
        return std::vector<std::string>();
    }
    return m_currentManager->PopulatedSlots();
}

bool MultiSave::LoadSaveByPath(std::string savePath)
{
    if(m_currentManager != 0x0)
    {
        bool loadSuccess = m_currentManager->LoadSave(savePath);
        if(!loadSuccess)
        {
            QMessageBox messageBox;
            messageBox.critical(0,"Failed To load Save","A save load error occurred - Please check log/STDOUT!");
            messageBox.setFixedSize(500,200);
        }
        return loadSuccess;
    }
    std::cout << "No current Manager" << std::endl;
    return false;
}

void MultiSave::LoadSaveBySlotNumber(int num)
{
    if(m_currentManager != 0x0)
    {
        bool loadSuccess = m_currentManager->LoadSave(num);
        if(!loadSuccess)
        {
            QMessageBox messageBox;
            messageBox.critical(0,"Failed To load Save","A save load error occurred - Please check log/STDOUT!");
            messageBox.setFixedSize(500,200);
        }

    }
    std::cout << "No current Manager" << std::endl;
}

void MultiSave::m_LoadSaveIntoRAM()
{
    if(m_currentManager != 0x0)
    {
        m_currentManager->LoadSaveAndSlotIntoRAM(); //No reason to do this as its done when the SaveFile & Slot is created
    }
    std::cout << "No current Manager" << std::endl;
}

bool MultiSave::IsLoaded()
{
    return m_currentManager->GetSaveFile()->IsLoaded() && m_currentManager->GetSaveSlot()->IsLoaded();
}

std::pair<std::string, DataRefStructure> MultiSave::GetKeyPairByKey(const std::string& key)
{
    return m_currentManager->GetSaveFile()->GetDataPairByKey(key);
}

void MultiSave::CommitToDisk()
{
    std::cout << "Saving Updates to disk..." << std::endl;
    m_currentManager->CommitChanges();
}

//SaveManager

SaveManager::SaveManager(QObject *parent)
    : QObject{parent}
{

}

SaveManager::~SaveManager()
{
    DeleteMultiSave();
}

void SaveManager::DeleteMultiSave()
{
    if(m_rbSave != 0x0)
    {
        delete m_rbSave;
        m_rbSave = 0x0;
    }
}

void SaveManager::CommitToDisk()
{
    m_rbSave->CommitToDisk();
}

void SaveManager::SetSaveRoot(QString qpath)
{
    std::string path = qpath.toStdString();
    m_path = path;
    if(path.find("compatdata") != std::string::npos) //assumne that if we have a "compatdata" in the path that we are running WINE
    {
        m_os = LINUX;
    }
    DeleteMultiSave();
    m_rbSave = new MultiSave(path);
    ReBirthVersion ver = m_rbSave->GetRebirthVersion();
    if(ver == UNDETECTED)
    {
        DeleteMultiSave();
        std::cout << "Won't iterate invalid dir" << std::endl;
        return;
    }
    std::vector<std::string> saveSlots = m_rbSave->ItereateSlots();
    emit SaveSlotsUpdated(saveSlots);
}

void SaveManager::GetSaveDataForPath(QString path)
{
    std::string s = path.toStdString();
    m_rbSave->LoadSaveByPath(s);
    if(m_rbSave->IsLoaded())
    {
        emit SaveDataLoaded();
    }
}

void SaveManager::GetSaveDataByKeys(PageDataStructure<QList<QString>> keys)
{
    QList<std::pair<std::string, DataRefStructure>> keyValues = QList<std::pair<std::string, DataRefStructure>>();
    for(size_t i = 0; i < keys.Data.size(); i++)
    {
        keyValues.push_back(m_rbSave->GetKeyPairByKey(keys.Data.at(i).toStdString()));
    }
    PageDataStructure<QList<std::pair<std::string, DataRefStructure>>> pageKeyValues = { keys.pageName, keyValues };
    emit DataKeysReady(pageKeyValues);
}
