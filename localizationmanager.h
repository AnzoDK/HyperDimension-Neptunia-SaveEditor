#ifndef LOCALIZATIONMANAGER_H
#define LOCALIZATIONMANAGER_H
#include <QString>
#include <map>
#include <iostream>
#include <fstream>
#include <filesystem>
namespace fs = std::filesystem;

class LocalizationManager
{
public:
    LocalizationManager(QString localizationFile);
    ~LocalizationManager();

    QString GetDefaultLanguageString(QString key);

protected:
    void m_BadSimpleJSONParse(char* buffs, size_t buffSize);
    QString m_localizationFilePath = "";
    std::map<std::string, std::string> m_defaultLocalizationMap = std::map<std::string, std::string>();
};

extern LocalizationManager* g_LocaleMan;

#endif // LOCALIZATIONMANAGER_H
