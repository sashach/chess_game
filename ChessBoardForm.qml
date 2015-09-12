import QtQuick 2.5
import QtQuick.Controls 1.3
import mymodule 1.0

Item {
    id: item
    property alias buttonSave: buttonSave

    Rectangle {
        id: root
        anchors.fill: parent
        color: "#c9cbbd"

        Button {
            id: buttonSave
            text: qsTr("Save")
            anchors.top: parent.top
            anchors.topMargin: 16
            anchors.left: parent.left
            anchors.leftMargin: 8
            onClicked: {
                chessGameStorage.saveGame()
            }
        }

        Rectangle {
            width: 200;
            height: 40;
            anchors.top: parent.top
            anchors.topMargin: 16
            anchors.left: buttonSave.right
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
                chessBoardModel.stopGame()
                item.destroy()
                mainWindow.enableButtons()
            }
        }

        ChessBoard{
            id: chessBoard
            anchors.top: buttonSave.bottom
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

