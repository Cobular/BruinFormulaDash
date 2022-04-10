import QtQuick 2.0
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.15

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

    RowLayout {
        anchors.fill: parent


        Image {
            id: image
            source: image_path
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.preferredHeight: image_size
            Layout.preferredWidth: image_size
            fillMode: Image.PreserveAspectFit
        }

        Text {
            function parse(prefix, value, dp) {
                return prefix + value.toFixed(dp);
            }

            font.pointSize: 90
            color: alertRectangle.color
            text: parse(prefix, value, dp)
            verticalAlignment: Text.AlignVCenter
            Layout.fillHeight: true
            Layout.fillWidth: true
            fontSizeMode: Text.Fit
            Layout.preferredHeight: 130
        }

        Text {
            text: suffix
            color: alertRectangle.color
            verticalAlignment: Text.AlignVCenter
            Layout.fillHeight: true
            Layout.fillWidth: true
            font.pointSize: fontsize
        }


    }

}

/*##^##
Designer {
    D{i:0;formeditorZoom:1.66}D{i:2}D{i:3}D{i:4}D{i:1}
}
##^##*/
