import QtQuick 2.0
import QtGraphicalEffects 1.0

AlertRectangle {
    id: alertRectangle
    width: 250
    height: 113

    property string image_path: ""
    property int image_size: 90
    property double value: 55.5
    property int dp: 0
    property int fontsize: 80
    property string prefix: ""
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
            width: image_size
            height: image_size
            anchors.verticalCenter: parent.verticalCenter
            source: image_path
            fillMode: Image.PreserveAspectFit
            sourceSize.height: image.width
            sourceSize.width: image.height

            Colorize {
                anchors.fill: image
                source: image
                hue: 1
                saturation: 1
                lightness: 1
            }
        }

        Text {
            function parse(prefix, value, dp) {
                return prefix + value.toFixed(dp);
            }

            height: 130
            anchors.verticalCenter: parent.verticalCenter
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
            font.pointSize: fontsize
            color: alertRectangle.color
            text: parse(prefix, value, dp)
        }

        Text {
            height: 130
            text: suffix
            anchors.verticalCenter: parent.verticalCenter
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
            font.pointSize: fontsize
            color: alertRectangle.color
        }


    }

}

/*##^##
Designer {
    D{i:0;formeditorZoom:1.66}D{i:2;invisible:true}
}
##^##*/
