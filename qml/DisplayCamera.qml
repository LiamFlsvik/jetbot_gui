import QtQuick 6.9
Rectangle{
    color: "transparent"
    width: parent.width
    height: parent.height
      
    Rectangle {
        
        //radius:10
        anchors.left:parent.left
        anchors.top:parent.top;
        color: "#6a89cc"
        width: parent.width
        height: parent.height
        
    
        Image {
            id: videoImage
            anchors.fill: parent
            source: "image://videoprovider/frame"
            cache: false
            fillMode: Image.PreserveAspectCrop
            
            Timer {
                interval: 10
                running: true
                repeat: true
                onTriggered: {
                    videoImage.source = "image://videoprovider/frame?t=" + Date.now();
                }
            }
        }
        
    }
}


