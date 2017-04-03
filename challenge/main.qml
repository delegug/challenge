import QtQuick 2.7
import QtQuick.Controls 1.5
import ChallengeLib 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Challenge")
    Component.onCompleted: {
        selector.forceActiveFocus();
    }
    /*
    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("&Open")
                onTriggered: console.log("Open action triggered");
            }
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }
    */

    /// Selects the processor for data visualitation
    ProcessorSelector {
        id: selector
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        width: 150
    }
    /// Shows the data of the selcted processor item
    ProcessorItem {
        id: coreInfoItem
        //Reference to the current selected id in the ProcessorSelector
        processorId: selector.currentProcessorId
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: selector.right
        anchors.right: parent.right
    }
}
