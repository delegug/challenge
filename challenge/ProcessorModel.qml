/// Contains a list with all Cpu-Information-Types displayed in the ListView of the Processor
/// the data in the model can be manipulated in this element

import QtQuick 2.7
import ChallengeLib 1.0

MyCpuInfoModel {
    id: infoModel
    cpuInfo: _myCpuInfo
    MyCpuInfoModelItem {
        type: MyNamespace.PROCESSOR
    }
    MyCpuInfoModelItem {
        type: MyNamespace.VENDOR_ID
    }
    MyCpuInfoModelItem {
        type: MyNamespace.CPU_FAMILY
    }
    MyCpuInfoModelItem {
        type: MyNamespace.MODEL
    }
    MyCpuInfoModelItem {
        type: MyNamespace.MODEL_NAME
    }
    MyCpuInfoModelItem {
        type: MyNamespace.STEPPING
    }
    MyCpuInfoModelItem {
        type: MyNamespace.MIRCOCODE
    }
    MyCpuInfoModelItem {
        type: MyNamespace.CPUMHZ
    }
    MyCpuInfoModelItem {
        type: MyNamespace.CACHESIZE
    }
    MyCpuInfoModelItem {
        type: MyNamespace.PHYSICAL_ID
    }
    MyCpuInfoModelItem {
        type: MyNamespace.SIBLINGS
    }
    MyCpuInfoModelItem {
        type: MyNamespace.CORE_ID
    }
    MyCpuInfoModelItem {
        type: MyNamespace.CPU_CORES
    }
    MyCpuInfoModelItem {
        type: MyNamespace.APICID
    }
    MyCpuInfoModelItem {
        type: MyNamespace.INIT_APICID
    }
    MyCpuInfoModelItem {
        type: MyNamespace.FPU
    }
    MyCpuInfoModelItem {
        type: MyNamespace.FPU_EXEPTION
    }
    MyCpuInfoModelItem {
        type: MyNamespace.CPUID_LEVEL
    }
    MyCpuInfoModelItem {
        type: MyNamespace.WP
    }
    /*
    MyCpuInfoModelItem {
        type: MyNamespace.FLAGS
    }
    */
    MyCpuInfoModelItem {
        type: MyNamespace.BUGS
    }
    MyCpuInfoModelItem {
        type: MyNamespace.BOGOMIPS
    }
    MyCpuInfoModelItem {
        type: MyNamespace.CLFLUSH_SIZE
    }
    MyCpuInfoModelItem {
        type: MyNamespace.CACHE_ALIGNMENT
    }
    MyCpuInfoModelItem {
        type: MyNamespace.ADDRESS_SIZE
    }
    MyCpuInfoModelItem {
        type: MyNamespace.POWER_MANAGEMENT
    }
}
