#ifndef CPUINFOBASE_H
#define CPUINFOBASE_H

#include <QObject>
#include "mynamespace.h"

/// @class cpuInfoBase
/// @brief Abstract Base Class for cpu information for different systems
class cpuInfoBase : public QObject
{
    Q_OBJECT
public:
    cpuInfoBase(QObject* parent=0);
    /// Initialization of the Cpu Information, Functions reads the CPU Information
    /// @warning must be called once during start process
    virtual bool initialize()=0;

    QString trErrorText() const;

protected:
    void setTrErrorText(const QString &trErrorText);

private:
    QString m_trErrorText;


};

#endif // CPUINFOBASE_H
