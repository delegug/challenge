/// @file cpuvalues.cpp
/// @brief Storing of the cpuValues for each processor
/// @author M. Gugenhan

#include "cpuvalues.h"

cpuValues::cpuValues()
{

}

/// Adds or Overwrites a cpu-Value of this processor
/// @param type Type of the Value
/// @param value Value as Variant
void cpuValues::addValue(myNamespace::CPUINFOTYPE type, const QVariant &value)
{
    m_valueMap.insert(type,value);
}

/// @return the Cpu-Value for a specific type
/// if the value is not found, an empty QVariant() will be returned
QVariant cpuValues::getValue(myNamespace::CPUINFOTYPE type)
{
    return m_valueMap.value(type,QVariant());
}

/// @return returns true if the map contains no cpu values
bool cpuValues::isEmpty()
{
    return m_valueMap.isEmpty();
}
