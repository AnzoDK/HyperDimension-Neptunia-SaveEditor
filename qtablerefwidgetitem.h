#ifndef QTABLEREFWIDGETITEM_H
#define QTABLEREFWIDGETITEM_H

#include <QTableWidgetItem>
#include "libNepNep/include/ReBirth/ReBirthExtras.h"

class QTableRefWidgetItem : public QObject, public QTableWidgetItem
{
public:
    QTableRefWidgetItem();
    QTableRefWidgetItem(DataRefStructure dataStruct);
    QTableRefWidgetItem(const QString& str);
    ~QTableRefWidgetItem();
    void UpdateData();


protected:
    DataRefStructure* m_originalData = 0x0;

public slots:

signals:

};

#endif // QTABLEREFWIDGETITEM_H
