#include <QApplication>
#include <QMainWindow>
#include <signal.h>
#include <QObject>

#include "ui_mainwindow.h"
#include "savemanager.h"
#include "filedialoghandler.h"
#include <QCommandLineParser>

void m_SetUp(Ui::MainWindow& main, SaveManager* saveMan, FileDialogHandler* fdHandler)
{
    QObject::connect(main.setSaveRootBtn, SIGNAL(clicked(bool)), fdHandler, SLOT(OpenDialog()));
    QObject::connect(fdHandler, &FileDialogHandler::DirectoryChange, saveMan, &SaveManager::SetSaveRoot);
    QObject::connect(fdHandler, &FileDialogHandler::DirectoryChangeForLabel, main.currentRootLabel, &QLabel::setText);
}



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
    m_SetUp(main, saveMan, fdHandler);

    w.show();

    int exCode = app.exec();
    delete saveMan;
    delete fdHandler;
    return exCode;
}

