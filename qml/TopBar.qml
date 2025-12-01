import QtQuick 6.9
import QtQuick.Controls 2.15
Rectangle {
    id: topBar
    color: "transparent"
    width: parent.width; height: parent.height*0.05;
    anchors.left: parent.left
    anchors.right: parent.right

    Image {
        anchors.fill: parent
        source: "qrc:/qml/images/taskbar_top.png"
        fillMode: Image.Stretch   
        }
    
    Row{
        anchors.fill:parent
        anchors.rightMargin: parent.width*0.01
        spacing: parent.width*0.4

        Rectangle {
            id: stack
            width:topBar.width*0.05
            height:topBar.height*0.7
            anchors.verticalCenter:parent.verticalCenter
            color:"transparent"

            Image{
                id:stackImage
            anchors.fill:parent
            source: "qrc:/qml/images/stack.png"
            fillMode: Image.PreserveAspectFit
            
            HoverHandler{
                onHoveredChanged: {
                    if(hovered){
                        stackImage.scale = 1.2
                        stackImage.source = "qrc:/qml/images/stack2.png"
                        
                    }
                    else{
                        stackImage.scale = 1
                        stackImage.source = "qrc:/qml/images/stack.png";
                        }
                    }
                }
            MouseArea {
                id: mouseArea
                anchors.fill: parent
                onClicked: {
                    contextMenu.open()
                }
            }
            }
             
            Menu {
                id: contextMenu
                y: stackImage.height*1.1
                
                MenuItem {
                    text: "Exit"
                    onTriggered: Qt.quit()
                }
            }
        }
    }
    Row{
        anchors.fill:parent
        anchors.rightMargin: parent.width*0.01
        spacing: parent.width*0.5
        layoutDirection: Qt.RightToLeft

        Rectangle{
            id: battery
            width:topBar.width*0.05
            height:topBar.height*0.7
            anchors.verticalCenter:parent.verticalCenter
            color:"transparent"

            Image{
                id: batteryIcon
                anchors.fill:parent
                source: "qrc:/qml/images/battery/battery100.png"
                fillMode: Image.PreserveAspectFit
                // https://wiki.qt.io/QML_States_Controlling
                //
                //states : [
                //    State {
                //        name: "100"
                //        PropertyChanges {target:batteryIcon; source:"qrc:/qml/images/battery100.png"}
                //    },
                //    State {
                //        name: "90"
                //        PropertyChanges {target:batteryIcon; source:"qrc:/qml/images/battery90.png"}
                //    },
                //    State {
                //        name: "80"
                //        PropertyChanges {target:batteryIcon; source:"qrc:/qml/images/battery80.png"}
                //    },
                //    State {
                //        name: "60"
                //        PropertyChanges {target:batteryIcon; source:"qrc:/qml/images/battery60.png"}
                //    },
                //    State {
                //        name: "50"
                //        PropertyChanges {target:batteryIcon; source:"qrc:/qml/images/battery50.png"}
                //    },
                //    State {
                //        name: "40"
                //        PropertyChanges {target:batteryIcon; source:"qrc:/qml/images/battery40.png"}
                //    },
                //    State {
                //        name: "25"
                //        PropertyChanges {target:batteryIcon; source:"qrc:/qml/images/battery25.png"}
                //    },
                //    State {
                //        name: "10"
                //        PropertyChanges {target:batteryIcon; source:"qrc:/qml/images/battery10.png"}
                //    }
                //]
                //Timer {
                //    id:battery_check_timer
                //    interval:2000
                //    running:true
                //    repeat:true
                //    onTriggered: {
                //        if(backend.getBatteryPercentage()>90){
                //            batteryIcon.
                //        }
                //    }
                //}
                
            }
        }
        Rectangle{
            id: ipAddress
            width:topBar.width*0.05
            height:topBar.height*0.7
            anchors.rightMargin:ipAddressText.width
            anchors.verticalCenter:parent.verticalCenter
            color:"transparent"
            
            Text{
                id: ipAddressText
                anchors.centerIn:parent
                width:ipAddress.width
                height:ipAddress.height;
                font.pixelSize:parent.height *0.7
                text: backend.ip
                font.family: "Informe"
                font.bold: true
            }
        }
    }
}
