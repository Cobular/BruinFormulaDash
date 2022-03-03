import QtQuick 2.0

AbstractImageTextComponent {
    id: coolantRectangle
    width: 250
    height: 133

    componentName: "Battery"
    image_path: "/media/battery"
    suffix: "V"

    property double voltage: -1
    value: voltage.toFixed(2)

    property alias alert: coolantRectangle.alert
    property alias alertTarget: coolantRectangle.alertTarget
}
