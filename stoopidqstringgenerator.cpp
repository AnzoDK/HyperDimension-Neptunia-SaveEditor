#include "stoopidqstringgenerator.h"

StoopidQStringGenerator::StoopidQStringGenerator()
{

}


QString StoopidQStringGenerator::Generate(DataRefStructure structure)
{
    switch(structure.expectedDataType)
    {
    case UNKNOWN:
        return QString();
        break;
    case UINT8:
        return QString::number(*structure.ThrowToUint8());
        break;
    case UINT16:
        return QString::number(*structure.ThrowToUint16());
        break;
    case UINT32:
        return QString::number(*structure.ThrowToUint32());
        break;
    case UINT64:
        return QString::number(*structure.ThrowToUint64());
        break;
    case INT8:
        return QString::number(*structure.ThrowToInt8());
        break;
    case INT16:
        return QString::number(*structure.ThrowToInt16());
        break;
    case INT32:
        return QString::number(*structure.ThrowToInt32());
        break;
    case INT64:
        return QString::number(*structure.ThrowToInt64());
        break;
    case FLOAT:
        return QString::number(*structure.ThrowToFloat());
        break;
    case CSTRING:
        return QString(structure.ThrowToCString());
        break;
    default:
        std::cout << "expectedDataType was not set" << std::endl;
        return QString();
        break;
    }
}
