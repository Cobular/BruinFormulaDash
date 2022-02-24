import QtQuick 2.0

AbstractImageTextComponent {
    id: coolantRectangle
    width: 250
    height: 133
    color: "#FFFFFF"

    componentName: "Brake"
    image_path: "/media/brake"

    property double max: -1
    value: max.tofixed(2)

    property alias alert: coolantRectangle.alert
    property alias alertTarget: coolantRectangle.alertTarget

}
