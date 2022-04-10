import QtQuick 2.0

AbstractImageTextComponent {
    id: batteryVoltage
    width: 250
    height: 133

    componentName: "Battery"
    image_path: "/media/battery"
    image_size: 75
    prefix: "\u2009"
    suffix: "V"
    dp: 2
    fontsize: 46

    property double voltage: -1
    value: voltage.toFixed(2)

    property alias voltage: batteryVoltage.value
    property alias alert: batteryVoltage.alert
    property alias alertTarget: batteryVoltage.alertTarget
}
