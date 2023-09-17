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


}
