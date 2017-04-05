#ifndef MYNAMESPACE_H
#define MYNAMESPACE_H

#include <QtCore>

/// @class myNamespace
/// @brief Namespace-Class includes the ENUMS of the project for QML/C++ access
/// Is declared as QGadget-Class, to acces the enums in qml
class myNamespace
{
    Q_GADGET
public:
    /// @enum CPUINFOTYPE
    /// @brief Types of CPU Informations
    enum CPUINFOTYPE {
        NO_TYPE=0x0,
        PROCESSOR=0x1,
        VENDOR_ID=0x2,
        CPU_FAMILY=0x4,
        MODEL=0x10,
        MODEL_NAME=0x20,
        STEPPING=0x40,
        MIRCOCODE=0x80,
        CPUMHZ=0x100,
        CACHESIZE=0x200,
        PHYSICAL_ID=0x400,
        SIBLINGS=0x800,
        CORE_ID=0x1000,
        CPU_CORES=0x2000,
        APICID=0x4000,
        INIT_APICID=0x8000,
        FPU=0x10000,
        FPU_EXEPTION=0x20000,
        CPUID_LEVEL=0x40000,
        WP=0x80000,
        FLAGS=0x100000,
        BUGS=0x200000,
        BOGOMIPS=0x400000,
        CLFLUSH_SIZE=0x800000,
        CACHE_ALIGNMENT=0x1000000,
        ADDRESS_SIZE=0x2000000,
        POWER_MANAGEMENT=0x4000000
    };
    Q_ENUM(CPUINFOTYPE)
    Q_DECLARE_FLAGS(CPUINFOTYPES, CPUINFOTYPE)

};
Q_DECLARE_OPERATORS_FOR_FLAGS(myNamespace::CPUINFOTYPES)


#endif // MYNAMESPACE_H
