import QtQuick.Controls

Dial {
    from: 0.0
    value: 0.5
    anchors.left:parent.left
    anchors.bottom:parent.bottom
    onMoved : {
        backend.setDesiredSpeed(value);
    }
}