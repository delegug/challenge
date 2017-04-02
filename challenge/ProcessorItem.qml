import QtQuick 2.0
import ChallengeLib 1.0

Rectangle {
    property int processorId: -1
    color: "yellow"
    onProcessorIdChanged: {

    }
    ProcessorModel {
        id: processorModel
    }
    Component {
        id: listElementDelegate
        Item {
            property color color: typeof(textColor) === "undefined" ? "black" : textColor
            width: parent.width
            height: listText.contentHeight
            Text {
                id: listText
                text: '<b>' + translatedText + ':</b> ' + value
            }
        }
        /*
        Item {
            id: listItem



            property string text: typeof(text) === "undefined" ? "" : text
            height: listText.contentHeight
            width: parent.width
            onTextChanged: {
                console.log("TEXT CHANGED!!!");
            }

            Text {
                id: listText
                anchors.fill: parent
                text: listItem.text
                color: listItem.color
                font.family: "Arial Narrow"
                font.italic: false
                verticalAlignment: Text.AlignVCenter
            }
        }
        */

    }
    ListView {
        anchors.fill: parent
        model: processorModel.model
        delegate: listElementDelegate
    }

    /*
    Row {
        Text {
            Component.onCompleted: {
                text=readValue(MyNamespace.MODEL_NAME);
            }
        }
    }
    */


    function readValue(type) {
        return _myCpuInfo.getValue(processorId,type);
    }
}

