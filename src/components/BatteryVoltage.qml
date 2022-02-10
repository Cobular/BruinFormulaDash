import QtQuick 2.0

AbstractImageTextComponent {
    id: coolantRectangle
    width: 250
    height: 113

    componentName: "Battery"
    image_path: "/media/battery"
    suffix: "V"

    property alias voltage: coolantRectangle.value
    property alias alert: coolantRectangle.alert
    property alias alertTarget: coolantRectangle.alertTarget
}
