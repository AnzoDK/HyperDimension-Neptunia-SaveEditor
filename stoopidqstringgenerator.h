#ifndef STOOPIDQSTRINGGENERATOR_H
#define STOOPIDQSTRINGGENERATOR_H
#include <libNepNep/include/ReBirth/ReBirthExtras.h>
#include <QString>
class StoopidQStringGenerator
{
public:
    StoopidQStringGenerator();
    static QString Generate(DataRefStructure structure);
};

#endif // STOOPIDQSTRINGGENERATOR_H
