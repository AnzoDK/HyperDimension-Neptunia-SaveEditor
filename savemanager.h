#ifndef SAVEMANAGER_H
#define SAVEMANAGER_H

#include <QObject>
#include <libNepNep/include/nepnep.h>
#include <libNepNep/include/ReBirth/ReBirthBase.h>
#include <vector>

enum HostOS {WINDOWS, LINUX};
enum ReBirthVersion {UNDETECTED, REBIRH1, REBIRTH2, REBIRTH3};

class MultiSave //Contain a save for each version and expose the one in use
{
public:
    MultiSave(const std::string& path);
    ~MultiSave();
    ReBirthVersion GetRebirthVersion();
    std::vector<std::string> ItereateSlots();
    //Since only RB1 is created in LibNepNep - we just add that one for now
    ReBirth1::ReBirth1Manager* rb1SaveManager = 0x0;
    //ReBirth2::ReBirth2Manager* rb2SaveManager = 0x0;
    //ReBirth3::ReBirth3Manager* rb3SaveManager = 0x0;

private:
    ReBirthVersion m_reBirthVersion = UNDETECTED;
    ReBirthBase* m_currentManager = 0x0;

};

class SaveManager : public QObject
{
    Q_OBJECT
public:
    explicit SaveManager(QObject *parent = nullptr);
    ~SaveManager();
    void DeleteMultiSave();

public slots:
    void SetSaveRoot(QString path);

signals:


private:
    std::string m_path = "";
    MultiSave* m_rbSave = 0x0;
    HostOS m_os = WINDOWS;



};

#endif // SAVEMANAGER_H
