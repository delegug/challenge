/// @class cpuinfobase.cpp
/// @brief Base Class for the cpu information
/// @author M. Gugenhan

#include "cpuinfobase.h"
#include <QQmlEngine>

cpuInfoBase::cpuInfoBase(QObject *parent) : QObject(parent)
{
    m_trErrorText=QString();
    QQmlEngine::setObjectOwnership(this,QQmlEngine::CppOwnership);
    m_trErrorText=QString();
}

/// @return Returns the translated errortext of the last called faulty function
QString cpuInfoBase::trErrorText() const
{
    return m_trErrorText;
}

/// @return Returns the translated errortext of the last called faulty function
void cpuInfoBase::setTrErrorText(const QString &trErrorText)
{
    m_trErrorText = trErrorText;
}
