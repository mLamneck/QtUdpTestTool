import QtQuick
import QtQuick.Window
import QtQuick.Layouts
import QtQuick.Controls.Material
import mark.udp

ApplicationWindow {
    id: root
    width: 300
    height: 600
    visible: true
    title: qsTr("Udp Test")
    Material.theme: Material.Light
    Material.accent: Material.Teal

    function appendText(_msg){
        received.text = received.text + _msg + "\n"
    }

    ColumnLayout{
        id: container
        anchors.fill: parent
        anchors.leftMargin: 10
        anchors.rightMargin: 5
        anchors.topMargin: 10
        spacing: 10

        Udp{
            id: udp
            onMsg: {
                console.log(_msg)
                root.appendText(_msg)
            }
        }

        RowLayout{
            spacing:10
            implicitWidth: 100
            TextField{
                id: iPort
                height:50
                implicitWidth: 100
                placeholderText: "Port"
                inputMethodHints: Qt.ImhDigitsOnly
            }
            RoundButton{
                radius: 10
                Material.background: Material.Teal
                implicitHeight: 60
                Layout.fillWidth: true
                text: udp.connected? "Unbind" : "bind"
                onClicked: udp.connected? udp.unbind() : udp.bind(iPort.text)
            }
        }
        Label{
            text: "<b>Status:</b> " + udp.status
        }

        Rectangle{
            Layout.topMargin: 20
            Layout.fillWidth: true;
            height: 1
            color: "gray"
        }

        Label{
            text: "<b>Destination:</b>"
        }

        RowLayout{
            TextField{
                id: iDestIp
                height:50
                implicitWidth: 100
                Layout.fillWidth: true
                placeholderText: "IP"
                text: "127.0.0.1"
            }
            TextField{
                id: iDestPort
                height:50
                implicitWidth: 100
                placeholderText: "Port"
                text: "9000"
                inputMethodHints: Qt.ImhDigitsOnly
            }
        }

        TextField{
            id: iMsg
            height:50
            Layout.fillWidth: true

            focus: true
            placeholderText: "Message"
            Keys.onReturnPressed: console.log("sending")
        }
        RoundButton{
            enabled: udp.connected
            radius: 10
            Material.background: Material.Teal
            implicitHeight: 60
            Layout.fillWidth: true
            text: "Sendmessage"
            onClicked: udp.send(iDestIp.text,iDestPort.text,iMsg.text)
        }
        TextArea{
            id: received
            placeholderText: "Reveived"
            text: " "
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.bottomMargin: 10
        }
        RoundButton{
            radius: 10
            Material.background: Material.Teal
            implicitHeight: 60
            Layout.fillWidth: true
            text: "Clear"
            onClicked: received.text = ""
        }

    }
}
