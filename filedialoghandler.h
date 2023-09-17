#ifndef FILEDIALOGHANDLER_H
#define FILEDIALOGHANDLER_H

#include <QObject>

class FileDialogHandler : public QObject
{
    Q_OBJECT
public:
    explicit FileDialogHandler(QObject *parent = nullptr);

signals:
    void DirectoryChange(QString);
    void DirectoryChangeForLabel(QString);

public slots:
    void OpenDialog();

private:
    QString m_chosenDir = QString();
};

#endif // FILEDIALOGHANDLER_H
