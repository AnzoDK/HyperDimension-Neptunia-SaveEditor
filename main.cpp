#include <QApplication>
#include <QMainWindow>
#include <signal.h>
#include <QObject>

#include "ui_mainwindow.h"
#include "savemanager.h"
#include "filedialoghandler.h"
#include "savedatauiupdater.h"
#include "localizationmanager.h"
#include <QCommandLineParser>

void m_SetUp(Ui::MainWindow& main, SaveManager* saveMan, FileDialogHandler* fdHandler, SaveDataUIUpdater* sdUpdater)
{
    main.miscTable->setColumnCount(2);
    main.miscTable->setHorizontalHeaderItem(0, new QTableWidgetItem("Key"));
    main.miscTable->setHorizontalHeaderItem(1, new QTableWidgetItem("Value"));

    /*Static signal stuff that I'm too stoopid to make better*/
    QObject::connect(main.setSaveRootBtn, SIGNAL(clicked(bool)), fdHandler, SLOT(OpenDialog()));
    QObject::connect(fdHandler, &FileDialogHandler::DirectoryChange, saveMan, &SaveManager::SetSaveRoot);
    QObject::connect(fdHandler, &FileDialogHandler::DirectoryChangeForLabel, main.currentRootLabel, &QLabel::setText);
    QObject::connect(saveMan, &SaveManager::SaveSlotsUpdated, sdUpdater, &SaveDataUIUpdater::UpdateSlotList);
    QObject::connect(sdUpdater, &SaveDataUIUpdater::RequestNewSaveDataForSlot, saveMan, &SaveManager::GetSaveDataForPath);
    QObject::connect(saveMan, &SaveManager::SaveDataLoaded, sdUpdater, &SaveDataUIUpdater::OnSaveLoaded);
    QObject::connect(sdUpdater, &SaveDataUIUpdater::RequestPageData, saveMan, &SaveManager::GetSaveDataByKeys);
    QObject::connect(saveMan, &SaveManager::DataKeysReady, sdUpdater, &SaveDataUIUpdater::OnKeysReady);
    QObject::connect(main.miscTable, &QTableWidget::itemChanged, sdUpdater, &SaveDataUIUpdater::OnItemsChanged);
    QObject::connect(main.saveChangesBtn, SIGNAL(clicked(bool)), saveMan, SLOT(CommitToDisk()));
    QObject::connect(main.restoreSaveBtn, SIGNAL(clicked(bool)), saveMan, SLOT(ReloadSave()));
    QObject::connect(saveMan, &SaveManager::CurrentSaveDataHasChanged, sdUpdater, &SaveDataUIUpdater::ForceReloadSlot);
}


LocalizationManager* g_LocaleMan = new LocalizationManager("locale.json");
int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    QCommandLineParser parser;
    QApplication::setApplicationName(QApplication::translate("main", "Neptune SaveEditor"));
    QApplication::setApplicationVersion("0.1");
    parser.addVersionOption();
    parser.process(app);
    QMainWindow w;
    Ui::MainWindow main;
    main.setupUi(&w);

    SaveManager* saveMan = new SaveManager();
    FileDialogHandler* fdHandler = new FileDialogHandler();
    SaveDataUIUpdater* sdUpdater = new SaveDataUIUpdater(main);
    m_SetUp(main, saveMan, fdHandler, sdUpdater);

    w.show();

    int exCode = app.exec();
    delete saveMan;
    delete fdHandler;
    delete sdUpdater;
    delete g_LocaleMan;
    return exCode;
}

