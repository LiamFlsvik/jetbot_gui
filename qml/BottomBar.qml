import QtQuick 6.9
Rectangle {
    id: bottomBar
    anchors.left: parent.left
    anchors.right: parent.right
    height: parent.height*0.1
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
                id: batteryIcon
                anchors.fill:parent
                source: "qrc:/qml/images/camera.png"
                fillMode: Image.PreserveAspectFit
                HoverHandler{
                onHoveredChanged: {
                    if(hovered){
                        batteryIcon.scale = 1.1
                    }
                    else{
                        batteryIcon.scale = 1                        
                    }
                }
            }
            }
        }

        Rectangle{
            id: ipAddress
            width:bottomBar.width*0.05
            height:bottomBar.height*0.7
            anchors.rightMargin:ipAddressText.width
            anchors.verticalCenter:parent.verticalCenter
            color:"transparent"
            

            Text{
                id: ipAddressText
                anchors.centerIn:parent
                width:ipAddress.width
                height:ipAddress.height;
                font.pixelSize:parent.height *0.7
                text: "Test"
                font.family: "Informe"
                font.bold: true
            }
        }
}
}