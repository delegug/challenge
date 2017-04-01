/// @file linuxcpuinfo.cpp
/// @brief Controls the access to the cpuInfo
/// @author M. Gugenhan

#include "linuxcpuinfo.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

#define INFO_FILEPATH "/proc/cpuinfo"

linuxCpuInfo::linuxCpuInfo(QObject *parent) : cpuInfoBase(parent)
{
    initializeTypeMap();
}

linuxCpuInfo::~linuxCpuInfo()
{
    //Delete Typeinfo
    clearCpuInfos();
    clearCpuValues();
}


/// removes all items in the cpuInfolist
void linuxCpuInfo::clearCpuInfos()
{
    qDeleteAll(m_cpuTypeInfos);
    m_cpuTypeInfos.clear();
}

/// removes all items in the cpuValues
void linuxCpuInfo::clearCpuValues()
{
    qDeleteAll(m_cpuValues);
    m_cpuValues.clear();
}

/// Initialization of the TypeMap
void linuxCpuInfo::initializeTypeMap() {
    clearCpuInfos();
    m_cpuTypeInfos.append(createTypeInfo(myNamespace::PROCESSOR,QT_TR_NOOP("Processor"),"processor"));
    m_cpuTypeInfos.append(createTypeInfo(myNamespace::VENDOR_ID,QT_TR_NOOP("Vendor Id"),"vendor_id"));
    m_cpuTypeInfos.append(createTypeInfo(myNamespace::CPU_FAMILY,QT_TR_NOOP("CPU family"),"cpu family"));
    m_cpuTypeInfos.append(createTypeInfo(myNamespace::MODEL,QT_TR_NOOP("Model"),"model"));
    m_cpuTypeInfos.append(createTypeInfo(myNamespace::MODEL_NAME,QT_TR_NOOP("Model name"),"model name"));
    m_cpuTypeInfos.append(createTypeInfo(myNamespace::STEPPING,QT_TR_NOOP("Stepping"),"stepping"));
    m_cpuTypeInfos.append(createTypeInfo(myNamespace::MIRCOCODE,QT_TR_NOOP("Microcode"),"microcode"));
    m_cpuTypeInfos.append(createTypeInfo(myNamespace::CPUMHZ,QT_TR_NOOP("CPU MHz"),"cpu MHz"));
    m_cpuTypeInfos.append(createTypeInfo(myNamespace::CACHESIZE,QT_TR_NOOP("Cache size"),"cache size"));
    m_cpuTypeInfos.append(createTypeInfo(myNamespace::PHYSICAL_ID,QT_TR_NOOP("Physical id"),"physical id"));
    m_cpuTypeInfos.append(createTypeInfo(myNamespace::SIBLINGS,QT_TR_NOOP("Siblings"),"siblings"));
    m_cpuTypeInfos.append(createTypeInfo(myNamespace::CORE_ID,QT_TR_NOOP("Core Id"),"core id"));
    m_cpuTypeInfos.append(createTypeInfo(myNamespace::CPU_CORES,QT_TR_NOOP("cpu cores"),"Cpu cores"));
    m_cpuTypeInfos.append(createTypeInfo(myNamespace::APICID,QT_TR_NOOP("Apicid"),"apicid"));
    m_cpuTypeInfos.append(createTypeInfo(myNamespace::INIT_APICID,QT_TR_NOOP("Initial apicid"),"initial apicid"));
    m_cpuTypeInfos.append(createTypeInfo(myNamespace::FPU,QT_TR_NOOP("Fpu"),"fpu"));
    m_cpuTypeInfos.append(createTypeInfo(myNamespace::FPU_EXEPTION,QT_TR_NOOP("Fpu Exception"),"fpu_exception"));
    m_cpuTypeInfos.append(createTypeInfo(myNamespace::CPUID_LEVEL,QT_TR_NOOP("Cpuid level"),"cpuid level"));
    m_cpuTypeInfos.append(createTypeInfo(myNamespace::WP,QT_TR_NOOP("Wp"),"wp"));
    m_cpuTypeInfos.append(createTypeInfo(myNamespace::FLAGS,QT_TR_NOOP("Flags"),"flags"));
    m_cpuTypeInfos.append(createTypeInfo(myNamespace::BUGS,QT_TR_NOOP("Bugs"),"bugs"));
    m_cpuTypeInfos.append(createTypeInfo(myNamespace::BOGOMIPS,QT_TR_NOOP("Bogomips"),"bogomips"));
    m_cpuTypeInfos.append(createTypeInfo(myNamespace::CLFLUSH_SIZE,QT_TR_NOOP("Clflush size"),"clflush size"));
    m_cpuTypeInfos.append(createTypeInfo(myNamespace::CACHE_ALIGNMENT,QT_TR_NOOP("Cache Alignment"),"cache_alignment"));
    m_cpuTypeInfos.append(createTypeInfo(myNamespace::ADDRESS_SIZE,QT_TR_NOOP("Address sizes"),"address sizes"));
    m_cpuTypeInfos.append(createTypeInfo(myNamespace::POWER_MANAGEMENT,QT_TR_NOOP("Power management"),"power management"));
}

/// Function creates a type information
/// @param type associated Type
/// @param sourceText sourceText for Translation
linuxCpuInfo::typeInfo *linuxCpuInfo::createTypeInfo(myNamespace::CPUINFOTYPE type, const QByteArray &sourceText, const QByteArray &typeText)
{
    typeInfo* info=new typeInfo();
    info->type=type;
    info->sourceText=sourceText;
    info->typeText=typeText;
    return info;
}

/// Initialization of the cpu info
/// Reading the CpuInfo-File on Linux
/// @return returns true on success
bool linuxCpuInfo::initialize()
{
    readInfoFile();
}

/// Reading the Linux-Cpu-Information file
/// @return returns true on success
bool linuxCpuInfo::readInfoFile() {
    QFile f(INFO_FILEPATH);
    if (!f.open(QIODevice::ReadOnly| QIODevice::Text)) {
        //TODO WRITE ERROR LOGFILE
        setTrErrorText(tr("Error initialize the application. Cannot open file '%1'!").arg(INFO_FILEPATH));
        return false;
    }
    //Fills a Stringlist with each line of the file
    QTextStream in(&f);
    QString line = in.readLine();
    QStringList strList;
    while (!line.isNull()) {
        strList.append(line);
        line = in.readLine();
    }
    f.close();
    if (strList.isEmpty()) {
        setTrErrorText(tr("Error initialize the application. File '%1' is empty!").arg(INFO_FILEPATH));
        return false;
    }
    //Clear cpuValue Objects
    clearCpuValues();
    //Create new CpuValues Object
    cpuValues* val=NULL;
    //Parse the information and fill the cpuValuesList with values
    foreach (QString str, strList) {
        if (!str.isEmpty()) {
            str.remove("\t");
            QStringList tmpList=str.split(":");
            if (tmpList.size()==2) {
                myNamespace::CPUINFOTYPE type=getInfoTypeForString(tmpList.at(0));
                if (type!=myNamespace::NO_TYPE) {
                    if (val==NULL) {
                        val=new cpuValues();
                        m_cpuValues.append(val);
                    }
                    val->addValue(type,QVariant(tmpList.at(1)));
                } else {
                    qWarning()<<"Warning type for string not found! Typstring: "<<tmpList.at(0);
                }
            }
        } else {
            if (val!=NULL) val=NULL;
        }
    }
    return true;
}

/// @return Returns the Typeinfo of a given string
/// if no type is found, myNamespace::NO_TYPE will be returned
myNamespace::CPUINFOTYPE linuxCpuInfo::getInfoTypeForString(const QString& typeText)
{
    foreach (typeInfo* info,m_cpuTypeInfos) {
        if (info->typeText==typeText) return info->type;
    }
    return myNamespace::NO_TYPE;
}

