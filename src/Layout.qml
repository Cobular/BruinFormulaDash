import QtQuick 2.0
import QtQuick.Controls 2.0
import com.cobular.CanHandler 1.0

import "components"

Rectangle {
    id: rectangle
    width: 1024
    height: 576
    color: dataObj.alert ? "red" : "#00ffffff"

    QtObject {
        id: dataObj
        property bool alert: false;
        property int maxRPM: 14000
    }

    CanHandler {
        id: canhandler
        debug: canDebugConsole
    }

    // Creates an instance of the slider component we just made in RPMSliderComponent.qml
    RPMSliderComponent {
        id: sliderComponent
        rpm: canhandler.rpmData // Here we set the custom property we defined to be the value of the below slider.
        // You'll see when this is ran that it is linked, so changing the slider position is reflected in the rpm slider, controlled through this property binding
        maxRpm: dataObj.maxRPM
    }

    RPMSliderLabels {
        id: sliderLabels
        maxRpm: dataObj.maxRPM
        width: sliderComponent.width - 4
        height: sliderComponent.height
        x: sliderComponent.x
        y: sliderComponent.y
    }

    MPHDisplayComponent {
        id: mphCounter
        height: sliderComponent.height
        mph: 23
    }

    AFRDisplayComponent {
        id: afrCounter
        x: 820
        y: 84
        width: 140
        height: 80
        afr: canhandler.afrData
    }

    Button {
        id: alertButton
        x: 12
        y: 322
        text: canhandler.userName
        onClicked: () => {dataObj.alert = !dataObj.alert; canhandler.numberFramesWritten++;}
    }

    GearComponent {
        id: gearComponent
        anchors.bottom: parent.bottom
        rpm: canhandler.rpmData
        alert: dataObj.alert
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottomMargin: 0
    }

    CoolantTemp {
        x: 8
        y: 86
        temp: canhandler.coolantData

    }

    BatteryVoltage {
        x: 8
        y: 479
        voltage: canhandler.voltageData
    }

    BrakeRatio {
        x: 730
        y: 500
        max: canhandler.biasData
    }

    CanDebugInfo {
        x: 8
        y: 578
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.leftMargin: 8
        anchors.bottomMargin: 8
        canCountProp: canhandler.numberFramesWritten
        canStatusMessage: canhandler.canStatusMessage
        socketCanStatusMessage: canhandler.socketCanStatus
    }

    Rectangle {
        x: 750
        y: 200
        width: 200
        height: 303
        border.color: "white"
        color: "transparent"
        DebugConsole {
            id: canDebugConsole
            color: "white"
            fontSize: 10
            lineHeight: 1.5
            x: 2
            y: 4
            width: parent.width - 4
            height: parent.height - 8
            numLines: 20
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.5}D{i:1}D{i:2}D{i:3}D{i:4}D{i:5}D{i:6}D{i:7}D{i:8}D{i:9}D{i:10}
D{i:11}D{i:12}
}
##^##*/
