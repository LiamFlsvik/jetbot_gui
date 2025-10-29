import QtQuick 6.9
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.0
import gui_uri 1.0

ApplicationWindow {
	id: app_window
	width: Screen.width;
	height: Screen.height;
	visible: true
	title: "Jetson GUI"
	
    Background {
        id: background;
        anchors.right: parent.right;
        anchors.bottom: parent.bottom;
        width: parent.width;
        height: width;

        DisplayCamera {
            anchors.horizontalCenter: background.horizontalCenter
            anchors.bottom: bottomBar.top
            anchors.bottomMargin: parent.height*0.01            
        }

        TopBar{
            id:topBar
            anchors.top: parent.top
        }

        Modes{
            id:modes_
            anchors.top:topBar.bottom
            anchors.topMargin:50;
            anchors.left:parent.left;
            anchors.leftMargin:50;
            width:parent.width*0.2; height:parent.height*0.25;
        }

        BottomBar { 
        id: bottomBar
        anchors.bottom: parent.bottom
        }  
    }
}
