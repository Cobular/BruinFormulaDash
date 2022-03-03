import QtQuick 2.0

Item {
    width: 300
    height: 14

    property string canStatusMessage: "NO MESSAGE"
    property int canCountProp: -1

    Row {
        id: row
        width: 200
        height: 400

        Text {
            id: canStatusPrefix
            color: "#0900ff"
            text: qsTr("CAN Status:  ")
            font.pixelSize: 12
        }

        Text {
            id: canStatus
            color: "#0900ff"
            text: canStatusMessage
            font.pixelSize: 12
        }

        Text {
            id: canCountPrefix
            color: "#0900ff"
            text: qsTr("    CAN Count:  ")
            font.pixelSize: 12
        }

        Text {
            id: canCount
            color: "#0900ff"
            text: canCountProp
            font.pixelSize: 12
        }
    }



}
