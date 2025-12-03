import QtQuick.Controls

Dial {
    
    anchors.left:parent.left
    anchors.bottom:parent.bottom
    onMoved : {
        backend.setDesiredSpeed(value);
    }
}