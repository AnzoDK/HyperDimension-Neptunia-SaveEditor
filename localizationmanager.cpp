#include "localizationmanager.h"
#include <string>

LocalizationManager::LocalizationManager(QString localizationFile)
{
    if(!fs::exists(localizationFile.toStdString()))
    {
        m_localizationFilePath = "";
        std::cout << "Failed to read file: \"" << localizationFile.toStdString() << "\" as it doesn't exist..." << std::endl;
        return;
    }
    std::ifstream in = std::ifstream(localizationFile.toStdString(), std::ios::in);
    size_t fileSize = fs::file_size(localizationFile.toStdString());
    char* buffer = new char[fileSize];

    in.read(buffer,fileSize);

    in.close();

    m_BadSimpleJSONParse(buffer,fileSize);
}

LocalizationManager::~LocalizationManager()
{

}

QString LocalizationManager::GetDefaultLanguageString(QString key)
{
    try{
        return QString::fromStdString(m_defaultLocalizationMap.at(key.toStdString()));
    }
    catch(std::out_of_range e)
    {
        std::cout << "Missing locale for \"" << key.toStdString() << "\"" << std::endl;
        return key;
    }
}

void LocalizationManager::m_BadSimpleJSONParse(char* buffer, size_t fileSize)
{
    std::string JSONstr = std::string(buffer); //This might be dumb

    size_t rightBracC = 0;
    size_t leftBracC = 0;
    size_t lastPos = 0;
    lastPos = JSONstr.find("{",lastPos);
    while(lastPos != std::string::npos)
    {
        rightBracC++;
        lastPos = JSONstr.find("{",lastPos+1);
    }

    lastPos = JSONstr.find("}",0);

    while(lastPos != std::string::npos)
    {
        leftBracC++;
        lastPos = JSONstr.find("}",lastPos+1);
    }

    if(leftBracC != rightBracC)
    {
        std::cout << "Brackets not matching (And yes it does count brackets inside of strings)" << std::endl;
        return;
    }
    lastPos = 0;
    while(1)
    {
        size_t keyStart = JSONstr.find("\"",lastPos);
        size_t keyEnd = JSONstr.find("\"",keyStart+1);
        std::string key = JSONstr.substr(keyStart+1, keyEnd-(keyStart+1));
        size_t seperator = JSONstr.find(":",keyEnd);
        keyStart = JSONstr.find("\"",seperator);
        keyEnd = JSONstr.find("\"",keyStart+1);
        std::string value = JSONstr.substr(keyStart+1, keyEnd-(keyStart+1));
        lastPos = JSONstr.find(",",keyEnd+1);
        m_defaultLocalizationMap.insert(std::pair<std::string, std::string>(key,value));
        if(lastPos == std::string::npos)
        {
            break;
        }
        lastPos++;
    }
    std::cout << "default LocaleMap has been generated..." << std::endl;
}

//LocalizationManager* g_LocaleMan = new LocalizationManager("locale.json");
