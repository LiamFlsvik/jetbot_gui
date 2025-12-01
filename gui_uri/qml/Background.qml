import QtQuick 6
Item{
    anchors.fill: parent
    
    Rectangle {	
        id: rectangleBG
        anchors.fill: parent
        
        gradient: Gradient {	
            GradientStop { position: 0.0; color: "#2e292e"; }
            GradientStop { position: 1.0; color: "#363536";   }
        }
    }
}
