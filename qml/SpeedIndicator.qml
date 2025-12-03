import QtQuick 6
import QtQuick.Controls
//https://doc.qt.io/qt-6/qml-qtquick-item.html#transformOrigin-prop
Item {
    property real max_speed: 2
    property real min_speed: 0
    property real min_angle: 0
    property real max_angle: 90
    property real speed: 1;
    property real angle_offset: -90
    Image{
        id: speedometer_background
        source: "qrc:/qml/images/speedometer_background.png"
        width:parent.width
        height:parent.height
        z: 1
    }

    Image{
        id: speedometer_indicator
        source: "qrc:/qml/images/speedometer_indicator.png"
        width: speedometer_background.width*0.05
        height:speedometer_background.height*0.8
        anchors.bottom: speedometer_background.bottom
        anchors.right: speedometer_background.right
        transformOrigin: Item.Bottom        
        rotation: speed_to_angle(backend.currentSpeed)
    }

    function speed_to_angle(new_speed){
        return new_speed*(max_angle-min_angle)/(max_speed-min_speed) +min_angle+angle_offset
    }

    
}