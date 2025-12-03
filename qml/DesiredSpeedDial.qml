import QtQuick.Controls

Dial {
    from:0.5
    to
    anchors.left:parent.left
    anchors.bottom:parent.bottom
    onMoved : {
        backend.setDesiredSpeed(value);
    }
}