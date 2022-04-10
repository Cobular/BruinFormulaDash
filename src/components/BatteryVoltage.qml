import QtQuick 2.0

AbstractImageTextComponent {
    id: coolantRectangle
    width: 250
    height: 113

    componentName: "Battery"
    image_path: "/media/battery"
    image_size: 75
    prefix: "\u2009"
    suffix: "V"
    dp: 2
    fontsize: 46

    property alias voltage: coolantRectangle.value
    property alias alert: coolantRectangle.alert
    property alias alertTarget: coolantRectangle.alertTarget
}
