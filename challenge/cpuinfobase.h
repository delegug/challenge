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
    /// @warning must be called once during starting process
    virtual bool initialize()=0;
    /// Functions returns the value of the processor for a specific type
    virtual QVariant getValue(unsigned short procIndex,myNamespace::CPUINFOTYPE type)=0;
    /// Function returns the translated text for the cpuInfoType
    virtual QString getTranslatedText(myNamespace::CPUINFOTYPE type)=0;

    QString trErrorText() const;

public slots:
    /// Function returns the number of processors
    virtual short numberOfProcessors()=0;
    virtual QVariant getValue(unsigned short procIndex,int type);

protected:
    void setTrErrorText(const QString &trErrorText);
private:
    QString m_trErrorText;
};

#endif // CPUINFOBASE_H
