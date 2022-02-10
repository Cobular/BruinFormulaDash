import QtQuick 2.0

AlertRectangle {
    id: alertRectangle
    width: 250
    height: 113

    property string image_path: ""
    property double value: 50.5
    property string suffix: ""
    property alias componentName: alertRectangle.componentName
    property alias alert: alertRectangle.alert
    property alias alertTarget: alertRectangle.alertTarget
    property string color: "white"

    Row {
        id: row
        x: 0
        y: 0
        height: 113

        Image {
            id: image
            width: 90
            height: 90
            anchors.verticalCenter: parent.verticalCenter
            source: image_path
            fillMode: Image.PreserveAspectFit
            sourceSize.height: image.width
            sourceSize.width: image.height
        }

        Text {
            height: 130
            text: Math.round(value)
            anchors.verticalCenter: parent.verticalCenter
            font.pointSize: 90
            color: alertRectangle.color
        }

        Text {
            height: 130
            text: suffix
            anchors.verticalCenter: parent.verticalCenter
            font.pointSize: 90
            color: alertRectangle.color
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:1.66}
}
##^##*/