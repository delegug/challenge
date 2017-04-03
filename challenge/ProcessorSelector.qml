/// ProcessorSelector displays the different Processors in a ListView and the user can select one

import QtQuick 2.7
import ChallengeLib 1.0
import QtQuick.Controls 2.1

FocusScope {
    property int currentProcessorId: -1
    Component.onCompleted: {
        fillModel();
    }
    Rectangle {
        anchors.fill: parent
        gradient: Gradient {
            GradientStop { position: 0.0; color: "white" }
            GradientStop { position: 1.0; color: "#c7e1fc" }
        }
        ListModel {
            id: processorModel
        }

        /// Delegate for the processor selection item with mouse events
        /// propertys of the model are 'processorId' and 'processor'
        Component {
            id: delegate
            Item {
                id: selectDelegate
                width: parent.width
                height: delegateText.contentHeight + 10
                property bool currentItem: ListView.isCurrentItem
                Rectangle {
                    anchors.fill: parent
                    anchors.leftMargin: 2
                    anchors.rightMargin: 2
                    anchors.topMargin: 2
                    color: selectDelegate.currentItem ? "#2774B0" : mouseArea.containsMouse ? "#D1E9FA" : "transparent"
                    border.color: "gray"
                    border.width: 1
                    radius: 5
                    MyText {
                        id: delegateText
                        color: selectDelegate.currentItem ? "white" : "black"
                        anchors.fill: parent
                        anchors.leftMargin: 5
                        text: qsTr("Processor") + (" ") + processorId
                    }
                }
                MouseArea {
                    id: mouseArea
                    acceptedButtons: Qt.LeftButton
                    anchors.fill: parent
                    hoverEnabled: true
                    onClicked: {
                       listView.currentIndex = index
                    }
                }
            }
        }
        /// List view of the Selection
        ListView {
            id: listView
            clip: true
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            width: listViewScroll.visible ? parent.width - listViewScroll.width : parent.width
            model: processorModel
            delegate: delegate
            focus: true
            interactive: true
            keyNavigationWraps: true
            onCurrentIndexChanged: {
                currentProcessorId=processorModel.get(currentIndex).processorId;
            }
            //Scrollbar outside of the listview
            ScrollBar.vertical: ScrollBar {
                id: listViewScroll
                parent: listView.parent
                anchors.top: listView.top
                anchors.left: listView.right
                anchors.bottom: listView.bottom
            }
            //Tab events + Send Events to scrollbar so scrollbar is also scrolling up/down on Keypress
            Keys.onPressed: {
                if (event.key===Qt.Key_Tab) {
                    incrementCurrentIndex();
                    listViewScroll.increase();
                    event.accepted=true;
                } else if (event.key===Qt.Key_Backtab) {
                    decrementCurrentIndex();
                    listViewScroll.decrease();
                    event.accepted=true;
                } else if (event.key===Qt.Key_Down) {
                    listViewScroll.increase();
                } else if (event.key===Qt.Key_Up) {
                    listViewScroll.decrease();
                }
            }
        }
    }
    /// Function fills the Listmodel with the cpuCore-Information
    function fillModel() {
        processorModel.clear();
        var numberOfCpuCores=_myCpuInfo.numberOfProcessors();
        for (var i=0;i<numberOfCpuCores;i++) {
            processorModel.append({"processorId": i,"processor":_myCpuInfo.getValue(i,MyNamespace.PROCESSOR)})
        }
    }
}

