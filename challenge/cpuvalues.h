#ifndef CPUVALUES_H
#define CPUVALUES_H

#include "cpuinfobase.h"
#include <QMap>
#include <QVariant>

/// @class cpuValues
/// @brief Class saves the Cpu-Values for each Processor
class cpuValues
{
public:
    cpuValues();
    void addValue(myNamespace::CPUINFOTYPE type,const QVariant& value);
    QVariant getValue(myNamespace::CPUINFOTYPE type);
    bool isEmpty();

private:
    QMap<myNamespace::CPUINFOTYPE,QVariant> m_valueMap;
};

#endif // CPUVALUES_H
