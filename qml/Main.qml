import QtQuick 6.9
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.0
import gui_uri 1.0

ApplicationWindow {
	id: app_window
	width: Screen.width;
	height: Screen.height;
	visible: true
	title: "JetBot User Interface"
	
    Background {
        id: background;
        anchors.right: parent.right;
        anchors.bottom: parent.bottom;
        width: parent.width;
        height: parent.width;

        TopBar{
            id:topBar
            anchors.top: parent.top
        }

        BottomBar { 
            id: bottomBar
            anchors.bottom: parent.bottom
        } 

        DisplayCamera {
            anchors.horizontalCenter: background.horizontalCenter
            anchors.top:topBar.bottom
            anchors.bottom: bottomBar.top
            anchors.leftMargin:parent.width*0.01
            anchors.rightMargin:parent.width*0.01
            anchors.topMargin:parent.height*0.01
            anchors.bottomMargin:parent.height*0.01    
        }

        DisplayMap {
            anchors.top:topBar.bottom
            anchors.right:parent.right
            height:parent.height*0.2
            width:parent.height*0.2
        }

        Modes{
            id:modes_
            anchors.top:topBar.bottom
            anchors.topMargin:parent.height*0.01 ;
            anchors.left:parent.left;
            anchors.leftMargin:parent.width*0.01 ;
            width:parent.width*0.1; height:parent.height*0.35;
        }
        SpeedIndicator{
            id:speedIndicator_
            anchors.bottom:bottomBar.top
            anchors.right: background.right
            width: parent.width*0.2
            height: parent.width*0.2
        }
        DesiredSpeedDial{
            id:speed_dial;
            anchors.bottom:bottomBar.top
            anchors.left: background.left

        }
    }
}
