import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts 1.0
import gui_uri 1.0
//https://doc.qt.io/qt-6/qml-qtquick-layouts-columnlayout.html

Rectangle{
    color:"#ffffffff"
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
                onCheckedChanged: {
                console.log(text +" "+ switch0.checked)
                backend.setMode(switch0.checked)
                }
                Layout.fillWidth: true
                width:parent.width
                height:parent.height
            }

            ComboBox {
                editable: false
                textRole: "vision_mode"
                model: ListModel {
                    id: model
                    ListElement { vision_mode: "Object detection" }
                    ListElement { vision_mode: "Face detection" }
                    ListElement { vision_mode: "Canny edge detection" }
                }
                onAccepted: {
                    if (find(editText) === -1)
                        model.append({text: editText})
                }
            }
        }
    }

