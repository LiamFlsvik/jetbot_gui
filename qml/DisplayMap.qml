import QtQuick 6.9
Rectangle{
    color: "transparent"
    width: parent.width
    height: parent.height
      
    Rectangle {
        radius:10
        anchors.left:parent.left
        anchors.top:parent.top;
        id: rect1
        color:"#6a89cc"
        width: parent.width
        height: parent.height
        Image{
            anchors.fill:parent
            id: cameraImage
            source: "qrc:/qml/images/lidar.jpeg"
            fillMode: Image.Stretch
        }
    }
}

