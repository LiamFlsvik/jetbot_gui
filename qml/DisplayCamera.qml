import QtQuick 6.9
//Followed tutorial from https://www.youtube.com/watch?v=-EYldBso0M4&t 
// To implement functionality to display camera


Rectangle{
    color: "transparent"
    width: parent.width*0.9
    height: parent.height*0.5
         
    Rectangle {
        radius:10
        anchors.left:parent.left
        anchors.top:parent.top;
        id: rect1
        color:"#6a89cc"
        width: parent.width/2
        height: parent.height
        Image{
            anchors.fill:parent
            id: cameraImage
            source: "qrc:/qml/images/jetpov.png"
            fillMode: Image.Stretch
            //property bool counter: false
            //function reload(){ 
            //    counter = !counter
            //    source = "image://live/image?id=" + counter;
            //}
        
        }
    }
    Rectangle{
        radius:10
        id: rect2
        color:"#82ccdd"
        height:rect1.height
        width:rect1.width
        anchors.left: rect1.right;
    
        Image {
            anchors.fill:parent
            id: lidarImage
            source: "qrc:/qml/images/lidar.jpeg"
            fillMode: Image.Stretch
        
        }
    }
    //Connections{
    //    target:liveImageProvider
    //    function onImageChanged() {
    //    cameraImage.reload()
    //    }
    //}
}


