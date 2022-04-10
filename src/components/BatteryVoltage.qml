import QtQuick 2.0

AbstractImageTextComponent {
    id: batteryVoltage
    width: 250
    height: 133

    color: "#FBFF4E"

    componentName: "Battery"
    image_path: "/media/battery"
    prefix: "\u2009"
    suffix: "V"
    dp: 2
    fontsize: 48

    property double voltage: -1
    value: voltage.toFixed(2)

    property alias voltage: batteryVoltage.value
    property alias alert: batteryVoltage.alert
    property alias alertTarget: batteryVoltage.alertTarget

}
