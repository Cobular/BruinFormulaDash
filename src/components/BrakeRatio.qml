import QtQuick 2.0

AbstractImageTextComponent {
    id: brakeRectangle
    width: 250
    height: 60

    color: "#FFB700"

    componentName: "Brake"
    image_path: "/media/brake"
    prefix: "F-"
    suffix: "%"
    fontsize: 40
    image_size: 85

    property double max: -1
    value: max.toFixed(2)
    dp: 1

    property alias alert: brakeRectangle.alert
    property alias alertTarget: brakeRectangle.alertTarget

}
