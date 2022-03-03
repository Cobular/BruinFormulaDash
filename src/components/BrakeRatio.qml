import QtQuick 2.0

AbstractImageTextComponent {
    id: coolantRectangle
    width: 250
    height: 133

    componentName: "Brake"
    image_path: "/media/brake"
    suffix: "%"

    property double max: -1
    value: max.toFixed(2)

    property alias alert: coolantRectangle.alert
    property alias alertTarget: coolantRectangle.alertTarget

}
