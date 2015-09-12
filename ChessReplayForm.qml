import QtQuick 2.5
import QtQuick.Controls 1.3
import mymodule 1.0

Item {
    id: item
    Rectangle {
        id: root
        anchors.fill: parent
        color: "#c9cbbd"

        Button {
            id: buttonPrev
            text: qsTr("Prev")
            anchors.top: parent.top
            anchors.topMargin: 16
            anchors.left: parent.left
            anchors.leftMargin: 8
            onClicked: chessBoardModel.prevStep()
        }

        Button {
            id: buttonNext
            text: qsTr("Next")
            anchors.top: parent.top
            anchors.topMargin: 16
            anchors.left: buttonPrev.right
            anchors.leftMargin: 8
            onClicked: chessBoardModel.nextStep()
        }

        Rectangle {
            width: 200;
            height: 40;
            anchors.top: parent.top
            anchors.topMargin: 16
            anchors.left: buttonNext.right
            anchors.leftMargin: 8
            anchors.right: buttonStop.left
            anchors.rightMargin: 8
            color: parent.color

            Text {
                id: currentPlayerText
                anchors.centerIn: parent
                text: ""
            }

            Connections {
                target: chessBoardModel
                onCurrentPlayerChanged: {
                    currentPlayerText.text = ((id == 1) ? "White Move" : "Black Move") + " [" + move_num + "]"
                }
                onReplayMoveChanged: {
                    currentPlayerText.text = "Move " +move + " of " + size + " moves"
                }
            }
            Connections {
                target: chessGameStorage
                onRecordIOMessage: {
                    currentPlayerText.text = str
                }
            }
        }

        Button {
            id: buttonStop
            x: 307
            text: qsTr("Stop")
            anchors.top: parent.top
            anchors.topMargin: 16
            anchors.right: parent.right
            anchors.rightMargin: 8
            onClicked: {
                item.destroy()
                mainWindow.enableButtons()
            }
        }

        ChessBoard{
            id: chessBoard
            anchors.top: buttonPrev.bottom
            anchors.topMargin: 8
            anchors.right: parent.right
            anchors.rightMargin: 8
            anchors.left: parent.left
            anchors.leftMargin: 8
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 8

            Connections {
                target: chessBoardModel
                onModelChanged: {
                    chessBoard.update()
                }
            }
        }
    }

}
