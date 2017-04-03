/// Item for the presentation of the cpu-information data for a processor
/// the processorId of the visible data can be selected with the property processorId

import QtQuick 2.7
import ChallengeLib 1.0

Rectangle {
    id: processorItem
    /// Property processorId is the processor id of the data shown in the ListView
    property int processorId: -1
    /// Background Gradient
    gradient: Gradient {
        GradientStop { position: 0.0; color: "white" }
        GradientStop { position: 1.0; color: "#c7e1fc" }
    }
    onProcessorIdChanged: {

    }
    /// Model for the Cpu-DataTypes which are shown in the ListView
    ProcessorModel {
        id: cpuDataModel
        processorId: processorItem.processorId
    }

    /// Delegate of the Listview for the cpu-data
    /// The CpuCoreModel contains following propertys:
    /// translatedText: Translated Text of the cpuInfoType
    /// value: Value of the cpuInfoType
    /// textColor: Color of the visible text
    Component {
        id: listElementDelegate
        Item {
            id: delegateItem
            property color color: typeof(textColor) === "undefined" ? "black" : textColor
            width: parent.width
            height: listValue.contentHeight
            MyText {
                id: listText
                anchors.top: delegateItem.top
                anchors.left: delegateItem.left
                text: '<b>' + translatedText + ':</b> '
                clip: true
                width: listText.contentWidth > delegateItem.width ? delegateItem.width : listText.contentWidth
                color: delegateItem.color
            }
            MyText {
                id: listValue
                anchors.top: delegateItem.top
                anchors.left: listText.right
                anchors.right: delegateItem.right
                text: value
                wrapMode: Text.Wrap
                clip: true
                color: delegateItem.color
            }
        }
    }
    /// ListView of the Cpu-Processor-Information
    ListView {
        anchors.fill: parent
        anchors.leftMargin: 4
        clip: true
        model: cpuDataModel.model
        delegate: listElementDelegate
    }
}

