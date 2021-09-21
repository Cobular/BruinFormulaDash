import QtQuick 2.12
import QtQuick.Window 2.12

// Window is the class for an overall window, so that's what we want for now.
Window {
    width: 1024  // Setting overal window size. Matches the size of the screen we'll eventually use.
    height: 600
    visible: true
    color: "#000000"  // Set background color
    title: "Hello World"  // and the window title

    Layout {

    }


    Item {
        id: fpsCorner
        visible: Backend.showFPS
        enabled: visible

        Text {
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.margins: 5
            text: counter.fps + " FPS"
            font.pixelSize: 26
        }

        FpsCounter {
            id: counter
        }
    }
}
