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
    //Button{}
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
        }
     }
    }


    

    Row{
        anchors.fill:parent
        anchors.rightMargin: parent.width*0.01
        spacing: parent.width*0.4
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
                source: "qrc:/qml/images/battery100.png"
                fillMode: Image.PreserveAspectFit
                HoverHandler{
                onHoveredChanged: {
                    if(hovered){
                        batteryIcon.scale = 1.2
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
                text: "IP:10.22.169.192"
                font.family: "Informe"
                font.bold: true
            }
        }
        

        //CheckBox{
        //    id:checkBox
        //    checked:false
        //    anchors.centerIn: parent
        //    width: 100; height:100;
        //    text: "Manual mode";
        //    onCheckedChanged:{
        //        console.log("CheckBox Status: " + checked)
        //    }
        //    background: Rectangle{
        //        border.width: 5;
        //        border.color:"#3c6382"
        //    }
        //    //indicator: Rectangle{
        //    //    id: checkBoxIndicator;
        //    //    width: 50;
        //    //    height: 50;
        //    //    //implicitwidth:50
        //    //    //implicitheight:50;
        //    //    radius:10
        //    //    border.color: #78e08f
        //    //    border.width: 3
        //    //    //x:10
        //    //    //y: (checkBox.height-checkBoxIndicator.height/2)
        //    //    
        //    //}
        //    
        //}
    }
}
