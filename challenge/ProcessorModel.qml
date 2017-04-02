import QtQuick 2.0
import ChallengeLib 1.0

MyCpuInfoModel {
    id: infoModel
    cpuInfo: _myCpuInfo
    MyCpuInfoModelItem {
        type: MyNamespace.MODEL_NAME
    }
    MyCpuInfoModelItem {
        type: MyNamespace.ADDRESS_SIZE
    }
    MyCpuInfoModelItem {
        type: MyNamespace.MODEL
    }
    MyCpuInfoModelItem {
        type: MyNamespace.FLAGS
    }
}
