import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts 1.0
import gui_uri 1.0


Rectangle{
    color:"#ffffffff"
    width:parent.width;
    height:parent.height;
    radius:40
    
    GridLayout {
        anchors.fill:parent
        id: modes
        columns:2
        rows:3
        rowSpacing: parent.height*0.02
        columnSpacing:parent.width*0.02
        CustomSwitch{
            id: manualModeSwitch
            text: "Manual Mode"
            onCheckedChanged: {
            console.log(text +" "+ manualModeSwitch.checked)
            classA.callMe();
            scale:parent.width*0.01
            }
            
        }
        CustomSwitch{
            id: lidarModeSwitch;
            text: "LIDAR"
            onCheckedChanged: {
            console.log(text +" "+ lidarModeSwitch.checked)
            }
        }
        CustomSwitch{
            id: cameraModeSwitch
            text: "CAMERA"
            onCheckedChanged: {
            console.log(text +" "+ cameraModeSwitch.checked)
            }
        }
        CustomSwitch{
            text: "AUTONOMOUS MODE"
        }
        CustomSwitch{
            text: "Manual Mode"
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
