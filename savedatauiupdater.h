#ifndef SAVEDATAUIUPDATER_H
#define SAVEDATAUIUPDATER_H

#include <QObject>
#include "ui_mainwindow.h"
#include "qtablerefwidgetitem.h"
#include "libNepNep/include/ReBirth/ReBirthExtras.h"
#include <map>

template <typename T>
struct PageDataStructure
{
    QString pageName = "";
    T Data;
};

class SaveDataUIUpdater: public QObject
{
    Q_OBJECT
public:
    explicit SaveDataUIUpdater(QObject *parent = nullptr);
    SaveDataUIUpdater(Ui::MainWindow& mainWindow);

signals:
    void RequestNewSaveDataForSlot(QString);
    void RequestPageData(PageDataStructure<QList<QString>>); //Request a list of datakeys from savemanager

public slots:
    void ForceReloadSlot();
    void UpdateSlotList(std::vector<std::string> saveSlots);
    void NewSaveSlotSelected();
    void OnSaveLoaded();
    void OnKeysReady(PageDataStructure<QList<std::pair<std::string, DataRefStructure>>> pageData);
    void OnItemsChanged(QTableWidgetItem* item);

private:
    Ui::MainWindow& m_window;
    QList<QTableRefWidgetItem*> m_refList = QList<QTableRefWidgetItem*>();
};

#endif // SAVEDATAUIUPDATER_H
