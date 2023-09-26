#include "qtablerefwidgetitem.h"
#include "stoopidqstringgenerator.h"

QTableRefWidgetItem::QTableRefWidgetItem(DataRefStructure dataStruct) : QTableWidgetItem(StoopidQStringGenerator::Generate(dataStruct))
{
    // The _dataPtr has been updated and no longer points to the start of the buffer, therefore,
    // we can't pass it as it is, and we need to subtract the m_dataOffset from it first
    m_originalData = new DataRefStructure(dataStruct.m_dataOffset,(dataStruct._dataPtr-dataStruct.m_dataOffset),dataStruct.expectedDataType,dataStruct.m_exptectedTypeSize);
}

QTableRefWidgetItem::QTableRefWidgetItem(const QString& str) : QTableWidgetItem(str)
{
    m_originalData = 0x0;
}

QTableRefWidgetItem::~QTableRefWidgetItem()
{
    if(m_originalData != 0x0)
    {
        delete m_originalData;
    }
}

void QTableRefWidgetItem::UpdateData()
{
    if(m_originalData == 0x0)
    {
        //std::cout << "Data Pointer missing - Can't access SaveFileBuffer for data update..." << std::endl;
        return;
    }
    unsigned long long int data = 0;
    float f = 0.0;
    switch(m_originalData->expectedDataType)
    {
    case UNKNOWN:
        return;
    case UINT8:
        data = text().toUInt();
        *((byte*)m_originalData->_dataPtr) = ((byte*)&data)[0];
        break;
    case UINT16:
        data = text().toUInt();
        *((uint16_t*)m_originalData->_dataPtr) = *((uint16_t*)&data);
        break;
    case UINT32:
        data = text().toUInt();
        *((uint32_t*)m_originalData->_dataPtr) =  *((uint32_t*)&data);
        break;
    case UINT64:
        data = text().toULong();
        *((uint64_t*)m_originalData->_dataPtr) = *((uint64_t*)&data);
        break;
    case INT8:
        data = text().toInt();
        *((char*)m_originalData->_dataPtr) = ((byte*)&data)[0];
        break;
    case INT16:
         data = text().toInt();
        *((int16_t*)m_originalData->_dataPtr) = *((int16_t*)&data);
         break;
    case INT32:
         data = text().toInt();
        *((int32_t*)m_originalData->_dataPtr) = *((int32_t*)&data);
        break;
    case INT64:
        data = text().toLong();
        *((int64_t*)m_originalData->_dataPtr) = *((int64_t*)&data);
        break;
    case FLOAT:
        f = text().toFloat();
        *((float*)m_originalData->_dataPtr) = *((float*)&f);
        break;
    case CSTRING:
        std::cout << "CSTRING HARD - No action" << std::endl;
        break;
    default:
        std::cout << "expectedDataType was not set" << std::endl;
        break;
    }

}
