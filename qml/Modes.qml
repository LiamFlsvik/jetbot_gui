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
            Rectangle{
                width:bottomBar.width*0.05
                height:bottomBar.height*0.7
                Switch {
                    text: qsTr("ARM")
                    anchors.fill:parent
                    
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
        }
        
    }

