import QtQuick 2.0

AbstractImageTextComponent {
    id: brakeRectangle
    width: 250
    height: 60

    color: "#FFB700"

    componentName: "Brake"
    image_path: "/media/brake"

    property string location: "F"
    property double percent: 52.1
    prefix: location + "-"
    value: percent
    suffix: "%"
    dp: 1
    fontsize: 40
    image_size: 85
    property alias alert: brakeRectangle.alert
    property alias alertTarget: brakeRectangle.alertTarget
}

/*##^##
Designer {
    D{i:0;formeditorZoom:1.5}
}
##^##*/
