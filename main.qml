import QtQuick 2.5
import QtQuick.Controls 1.3
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.2

ApplicationWindow {
    id: mainWindow
    width: 640
    height: 550
    color: "#c9cbbd"
    visible: true

    property alias buttonEmpty: buttonEmpty
    property alias buttonLoad: buttonLoad
    property alias buttonStart: buttonStart

    function disableButtons() {
        buttonEmpty.enabled = false
        buttonStart.enabled = false
        buttonLoad.enabled = false
    }
    function enableButtons() {
        buttonEmpty.enabled = true
        buttonStart.enabled = true
        buttonLoad.enabled = true
    }

    RowLayout {
        width: 265
        height: 29
        anchors.verticalCenterOffset: 117
        anchors.centerIn: parent

        Button {
            id: buttonStart
            text: qsTr("Start")
            enabled: true
            onClicked: {
                Qt.createQmlObject('ChessBoardForm{anchors.fill: parent}', mainWindow, 'chessBoardForm')
                chessBoardModel.startNewGame()
                disableButtons()
                ChessBoardForm.buttonSave.visible = true
            }
        }

        Button {
            id: buttonLoad
            text: qsTr("Load")
            enabled: true
            onClicked: {
                Qt.createQmlObject('ChessReplayForm{anchors.fill: parent}', mainWindow, 'chessReplayForm')
                chessBoardModel.loadGame()
                disableButtons()
            }
        }

        Button {
            id: buttonEmpty
            text: qsTr("Empty")
            enabled: true
            onClicked: {
                Qt.createQmlObject('ChessBoardForm{anchors.fill: parent; buttonSave.visible: false}', mainWindow, 'chessBoardForm')
                chessBoardModel.clearBoard()
                disableButtons()
            }
        }
    }

    Image {
        id: image1
        x: 183
        width: 274
        height: 231
        anchors.top: parent.top
        anchors.topMargin: 40
        anchors.horizontalCenter: parent.horizontalCenter
        source: "images.jpeg"
    }
}

