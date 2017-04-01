#ifndef LINUXCPUINFO_H
#define LINUXCPUINFO_H

#include "cpuinfobase.h"
#include "cpuvalues.h"

/// @class linuxCpuInfo
/// @brief Class to Access the Information of the CPU in a Linux System
/// Class reads the information out of the file in
class linuxCpuInfo : public cpuInfoBase
{
    Q_OBJECT
public:
    explicit linuxCpuInfo(QObject *parent = 0);
    virtual ~linuxCpuInfo();
    bool initialize();


signals:

public slots:

private:
    /// @struct typeInfo
    /// struct for saving information for each type
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
