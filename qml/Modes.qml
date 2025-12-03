import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts 1.0
import gui_uri 1.0
//https://doc.qt.io/qt-6/qml-qtquick-layouts-columnlayout.html

Rectangle{
    color:"#ffffffff"
    opacity: 0.9
    width:parent.width;
    height:parent.height;
    radius: 10

        ColumnLayout{
            spacing: 2
            anchors.fill: parent

            CustomSwitch{
                id: switch0
                text: "Manual Mode"
                Layout.alignment: Qt.AlignLeft
                Layout.fillWidth: true
                width:parent.width
                height:parent.height

                onCheckedChanged: {
                    console.log(text +" "+ switch0.checked)
                    backend.setMode(switch0.checked)
                }
            }

            CustomSwitch{
                id: switch1
                text: "Arm/Disarm"
                Layout.alignment: Qt.AlignLeft
                Layout.fillWidth: true
                width:parent.width
                height:parent.height

                onCheckedChanged: {
                    console.log(text +" "+ switch1.checked)
                    backend.setArmMode(switch1.checked)
                }
            }

            ComboBox {
                id: combo_box_vision_mode
                editable: false
                textRole: "vision_mode"
                model: ListModel {
                    id: model
                    ListElement { vision_mode: "Linefollowing" }
                    ListElement { vision_mode: "none" }
                    ListElement { vision_mode: "none" }
                }
                onAccepted: {
                    if (find(editText) === -1)
                        model.append({text: editText})
                }
                onActivated: {
                    backend.setDetectionMode(combo_box_vision_mode.currentValue)
                }
            }
            CustomSwitch{
                id: switch2
                text: "SimulatorMode"
                Layout.alignment: Qt.AlignLeft
                Layout.fillWidth: true
                width:parent.width
                height:parent.height

                onCheckedChanged: {
                    console.log(text +" "+ switch2.checked)
                    backend.setSimulatorMode(switch2.checked)
                }
            }
        }
        
    }

