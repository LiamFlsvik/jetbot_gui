import QtQuick 6.9
import QtGraphs
Rectangle{
    color: "black"
    width: parent.width
    height: parent.height
      
    Rectangle {
        radius:10
        anchors.left:parent.left
        anchors.top:parent.top;
        id: rect1
        color:"black"
        width: parent.width
        height: parent.height
        GraphsView {

            anchors.fill: parent
            axisX: ValueAxis {
                max: 3
            }
            axisY: ValueAxis {
                max: 3
            }
            theme: GraphsTheme {
            colorScheme: GraphsTheme.ColorScheme.Dark
            backgroundColor: "black"           // The area outside the grid
            plotAreaBackgroundColor: "black"   // The grid area itself
            labelTextColor: "white"            // Make text visible on black
            grid.mainColor: "#404040"          // Make grid lines subtle gray
        }

            ScatterSeries {
                color: "#00ff00"
                XYPoint { x: 0.5; y: 0.5 }
                XYPoint { x: 1; y: 1 }
                XYPoint { x: 2; y: 2 }
                XYPoint { x: 2.5; y: 1.5 }
            }
        }
    }
}

