import QtQuick 2.0

AbstractImageTextComponent {
    id: brakeRectangle
    width: 270
    height: 64

    color: "#FFB700"

    componentName: "Brake"
    image_path: "/media/brake"
    prefix: "F-"
    suffix: "%"
    image_size: 96
    fontsize: 48

    property double max: -1
    value: max.toFixed(2)
    dp: 1

    property alias alert: brakeRectangle.alert
    property alias alertTarget: brakeRectangle.alertTarget

}
