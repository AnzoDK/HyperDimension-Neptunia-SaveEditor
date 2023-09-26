#include "savedatauiupdater.h"
#include "qtablerefwidgetitem.h"
#include <libNepNep/include/ReBirth/ReBirthExtras.h>
#include "localizationmanager.h"
SaveDataUIUpdater::SaveDataUIUpdater(Ui::MainWindow& mainWindow) : m_window(mainWindow)
{
    QObject::connect(m_window.saveGamesList, &QListWidget::itemSelectionChanged, this, &SaveDataUIUpdater::NewSaveSlotSelected);
}


void SaveDataUIUpdater::UpdateSlotList(std::vector<std::string> saveSlots)
{
    m_window.saveGamesList->clear();
    QStringList list = QStringList();
    for(size_t i = 0; i < saveSlots.size();i++)
    {
        QString s = QString::fromStdString(saveSlots.at(i));
        list.append(s);
    }
    m_window.saveGamesList->addItems(list);
}

void SaveDataUIUpdater::NewSaveSlotSelected()
{
    QListWidgetItem* item = m_window.saveGamesList->selectedItems()[0];
    QString slotName = item->text();
    emit RequestNewSaveDataForSlot(slotName);
}

void SaveDataUIUpdater::OnSaveLoaded()
{

    QList<QString> miscList = {
        "playTimeHours",
        "playTimeMinutes",
        "playTimeSeconds",
        "saveCount",
        "sharesPlaneptune",
        "sharesLeanbox",
        "sharesLastation",
        "sharesOther"
    };
    PageDataStructure<QList<QString>> miscDataRequest = { "miscPage", miscList };
    emit RequestPageData(miscDataRequest);

    //Emit rest of requests here
}

void SaveDataUIUpdater::OnKeysReady(PageDataStructure<QList<std::pair<std::string, DataRefStructure>>> pageData)
{
    m_window.miscTable->clearContents();
    m_window.miscTable->setRowCount(0); //reset all rows to avoid it spawing more each time xD
    //m_refList.clear();
    for(size_t i = 0; i < pageData.Data.size(); i++)
    {
        m_window.miscTable->insertRow(i);
        QString q = g_LocaleMan->GetDefaultLanguageString(QString::fromStdString(pageData.Data.at(i).first));
        QTableRefWidgetItem* item = new QTableRefWidgetItem(q);
        item->setFlags(item->flags() ^ Qt::ItemIsEditable);
        m_window.miscTable->setItem(i,0,item);
        QTableRefWidgetItem* valueItem = new QTableRefWidgetItem(pageData.Data.at(i).second);
        m_window.miscTable->setItem(i,1, valueItem);
        //m_refList.push_back(valueItem);

    }
}

void SaveDataUIUpdater::OnItemsChanged(QTableWidgetItem *item)
{
    try{
        ((QTableRefWidgetItem*)item)->UpdateData();
    }
    catch(std::exception e)
    {
        //Ignore
    }
}

void SaveDataUIUpdater::ForceReloadSlot()
{
    NewSaveSlotSelected();
}
