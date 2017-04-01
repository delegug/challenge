import QtQuick 2.7
import QtQuick.Controls 1.5
import ChallengeLib 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Challenge")

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

    MyTriangle {
        Label {
            text: qsTr("Hello World")
            anchors.centerIn: parent
        }
        //color: "green"
        anchors.fill: parent
    }
}
