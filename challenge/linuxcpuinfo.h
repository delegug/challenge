#ifndef LINUXCPUINFO_H
#define LINUXCPUINFO_H

#include "cpuinfobase.h"
#include "cpuvalues.h"

/// @class linuxCpuInfo
/// @brief Class to access the information of the CPU in a linux system
/// Class reads the information from the file located in /proc/cpuinfo
/// The read information can be requested with the function @link linuxCpuInfo::getValue @endlink
/// or @link linuxCpuInfo::numberOfProcessors @endlink
class linuxCpuInfo : public cpuInfoBase
{
    Q_OBJECT
public:
    explicit linuxCpuInfo(QObject *parent = 0);
    virtual ~linuxCpuInfo();
    bool initialize();
    virtual QVariant getValue(unsigned short procIndex, myNamespace::CPUINFOTYPE type);
    virtual QString getTranslatedText(myNamespace::CPUINFOTYPE type);

signals:

public slots:
    virtual short numberOfProcessors();

private:
    /// @struct typeInfo
    /// struct for saving additional information for each cpu-typeinfo
    struct typeInfo {
        myNamespace::CPUINFOTYPE type;
        QByteArray sourceText; ///<Source Text for Translation
        QByteArray typeText;
    };
    void clearCpuInfos();
    void clearCpuValues();
    typeInfo* createTypeInfo(myNamespace::CPUINFOTYPE type,const QByteArray& sourceText,const QByteArray& typeText);
    QList<typeInfo*> m_cpuTypeInfos;
    void initializeTypeMap();
    bool readInfoFile();
    QList<cpuValues*> m_cpuValues;
    myNamespace::CPUINFOTYPE getInfoTypeForString(const QString &typeText);

};

#endif // LINUXCPUINFO_H
