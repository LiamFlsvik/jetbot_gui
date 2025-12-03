import QtQuick 6.9

import QtQuick.Controls
import QtQuick.Layouts 1.0
import gui_uri 1.0
Rectangle {
    id: bottomBar
    anchors.left: parent.left
    anchors.right: parent.right
    height: parent.height*0.06
    color: "transparent"

    Text {
        anchors.centerIn: parent
        text: "Status: OK"
        color: "black"
    }
    Image {
        anchors.fill: parent       // Image fills the entire rectangle
        source: "qrc:/qml/images/taskbar.png"
        fillMode: Image.Stretch    // Stretch to fill (may distort)
    }
    
    
    
    Row{
        anchors.fill:parent
        anchors.rightMargin: parent.width*0.01
        spacing: parent.width*0.4
        layoutDirection: Qt.RightToLeft

        Rectangle{
            id: camera
            width:bottomBar.width*0.05
            height:bottomBar.height*0.7
            anchors.verticalCenter:parent.verticalCenter
            color:"transparent"
            Image{
                id: screenshot_button
                anchors.fill:parent
                source: "qrc:/qml/images/camera.png"
                fillMode: Image.PreserveAspectFit
                HoverHandler{
                onHoveredChanged: {
                    if(hovered){
                        screenshot_button.scale = 1.1
                    }
                    else{
                        screenshot_button.scale = 1                        
                    }
                }
            }
            }
        }

       

        Rectangle{
            id: ipAddress
            width:bottomBar.width*0.05
            height:bottomBar.height*0.7
            anchors.verticalCenter:parent.verticalCenter
            color:"transparent"
            

            Image{
                id: mode_menu
                anchors.fill:parent
                source: "qrc:/qml/images/mode_menu.png"
                fillMode: Image.PreserveAspectFit
                scale: 1.5
                HoverHandler{
                onHoveredChanged: {
                    if(hovered){
                        mode_menu.scale = 1.8
                    }
                    else{
                        mode_menu.scale = 1.5                 
                    }
                }
            }
            }
        }
        Rectangle{
            id: pid_menu_icon
            width:bottomBar.width*0.05
            height:bottomBar.height*0.7
            anchors.verticalCenter:parent.verticalCenter
            color:"transparent"
            Image{
                id: pid_menu_image
                anchors.fill:parent
                source: "qrc:/qml/images/pid_menu_up.png"
                fillMode: Image.PreserveAspectFit
                HoverHandler{
                onHoveredChanged: {
                    if(hovered){
                        pid_menu_image.scale = 1.1
                    }
                    else{
                        pid_menu_image.scale = 1                        
                       }
                    }
                }
                MouseArea {
                id: mouseArea
                anchors.fill: parent
                onClicked: {
                    pid_settings.open()
                    }
                }
            }
        }
    }
    Popup {
        id: pid_settings
        parent: bottomBar.parent.parent
        modal: true
        focus: false
        x: pid_menu_icon.x + pid_menu_icon.width / 2 
        y: bottomBar.y - implicitHeight 
        background: Rectangle {
            color: "black"
            radius: 5
        }
        ColumnLayout {
            Button{
                text: "Send PID Gains"
                
            }
           
            id: pid_settings_column
            RowLayout {
                spacing: 10
                DoubleSpinBox {
                    id: kp1
                    realValue: 1
                    realStepSize: 0.025
                }
                DoubleSpinBox {
                    id: ki1
                    realValue: 1
                    realStepSize: 0.1
                }
                DoubleSpinBox {
                    id: kd1
                    realValue: 1
                    realStepSize: 0.1
                    }
                }

            RowLayout {
                spacing: 10
                DoubleSpinBox {
                    id: kp2
                    realValue: 1
                    realStepSize: 0.1
                }
                DoubleSpinBox {
                    id: ki2
                    realValue: 1
                    realStepSize: 0.1
                }
                DoubleSpinBox {
                    id: kd2
                    realValue: 1
                    realStepSize: 0.1
                    }
                }
        }
    }
}
