import QtQuick
import QtQuick.Controls.Basic
// https://doc.qt.io/qt-6/qtquickcontrols-customize.html

CheckBox {
    id: control
    text: qsTr("CheckBox")
    checked: true
    width:parent.width
    height:parent.height

    indicator: Rectangle {
        id:button_outer
        width: parent.height*0.9
        height: parent.height*0.9
        x: control.leftPadding
        y: parent.height / 2 - height / 2
        radius: 3
        border.color: control.down ? "#17a81a" : "#21be2b"

        Rectangle {
            id: button_inner
            width: button_outer.width/2
            height: button_outer.height/2
            x: 6
            y: 6
            radius: 2
            color: control.down ? "#17a81a" : "#21be2b"
            visible: control.checked
        }
    }

    contentItem: Text {
        text: control.text
        font: control.font
        opacity: enabled ? 1.0 : 0.3
        color: control.down ? "#17a81a" : "#21be2b"
        verticalAlignment: Text.AlignVCenter
        leftPadding: control.indicator.width + control.spacing
    }
}

