import QtQuick 6.9
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.0


Switch {
    id: control
    font.family: "Informe"
    font.pixelSize: 18
    checked: false
    property bool on:false
    property real scale: 1
    
    indicator: Rectangle {
        implicitWidth: 48*scale
        implicitHeight: 26*scale
        x: control.leftPadding
        y: parent.height / 2 - height / 2
        radius: 13
        color: control.checked ? "#17a81a" : "#ffffff"
        border.color: control.checked ? "#17a81a" : "#cccccc"
        Rectangle {
            x: control.checked ? parent.width - width : 0
            width: 26*scale
            height: 26*scale
            radius: height/2
            color: control.down ? "#cccccc" : "#ffffff"
            border.color: control.checked ? (control.down ? "#1719a8ff" : "#2e21beff") : "#999999"
        }

    }
    contentItem: Text {
        text: control.text
        font: control.font
        opacity: enabled ? 1.0 : 0.3
        //color: control.down ? "#000000ff" : "#21be2b"
        verticalAlignment: Text.AlignVCenter
        leftPadding: control.indicator.width + control.spacing
    }
}