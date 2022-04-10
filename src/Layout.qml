import QtQuick 2.0
import QtQuick.Controls 2.0
import com.cobular.CanHandler 1.0
import "components"

Rectangle {
    id: rectangle
    width: 1024
    height: 600
    color: dataObj.alert ? "red" : "#00ffffff"

    QtObject {
        id: dataObj
        property bool alert: false;
        property int maxRPM: 14000
    }

    CanHandler {
        id: canhandler
    }

    // Creates an instance of the slider component we just made in RPMSliderComponent.qml
    RPMSliderComponent {
        id: sliderComponent
        rpm: canhandler.testCanData // Here we set the custom property we defined to be the value of the below slider.
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
        y: 90
        width: 140
        height: 80
        afr: 82.1
    }

    Button {
        id: alertButton
        y: 100
        text: canhandler.userName
        onClicked: () => dataObj.alert = !dataObj.alert
    }

    GearComponent {
        anchors.bottom: parent.bottom
        rpm: canhandler.testCanData
        alert: dataObj.alert
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottomMargin: 0
    }

    CoolantTemp {
        x: 8
        y: 91
    }

    BrakeBias {
        x: 730
        y: 500
    }

    BatteryVoltage {
        x: 8
        y: 479
    }
    
    CanDebugInfo {
        x: 8
        y: 578
        canCountProp: canhandler.numberFramesWritten
        canStatusMessage: canhandler.canStatusMessage
        socketCanStatusMessage: canhandler.socketCanStatus
    }
}
