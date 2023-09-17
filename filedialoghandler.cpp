#include "filedialoghandler.h"
#include <QFileDialog>
FileDialogHandler::FileDialogHandler(QObject *parent)
    : QObject{parent}
{

}

void FileDialogHandler::OpenDialog()
{
    QString chosenDir = QFileDialog::getExistingDirectory(nullptr,"Choose Neptune SaveData Root");
    m_chosenDir = chosenDir;
    emit DirectoryChange(m_chosenDir);
    chosenDir = "Current Root: " + chosenDir;
    emit DirectoryChangeForLabel(chosenDir);
}
