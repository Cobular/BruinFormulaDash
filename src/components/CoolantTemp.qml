import QtQuick 2.0

AlertRectangle {
    id: alertRectangle
    width: 250
    height: 113

    componentName: "Coolant"
    property double temp: 50.5
    property alias alert: alertRectangle.alert
    property alias alertTarget: alertRectangle.alertTarget

    Image {
        id: image
        x: 8
        y: 23
        width: 90
        height: 90
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        source: "/media/coolant"
        fillMode: Image.PreserveAspectFit
        sourceSize.height: image.width
        sourceSize.width: image.height
        anchors.leftMargin: 8
    }

    Text {
        x: 111
        y: -25
        width: 66
        height: 130
        text: Math.round(temp)
        font.pointSize: 90
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:4}
}
##^##*/
