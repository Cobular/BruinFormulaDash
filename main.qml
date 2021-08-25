import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls

// Window is the class for an overall window, so that's what we want for now.
Window {
    width: 1024  // Setting overal window size. Matches the size of the screen we'll eventually use.
    height: 600
    visible: true
    color: "#000000"  // Set background color
    title: "Hello World"  // and the window title

    // Creates an instance of the slider component we just made in RPMSliderComponent.qml
    RPMSliderComponent {
        id: sliderComponent
        rpmPercent: slider.value  // Here we set the custom property we defined to be the value of the below slider.
        // You'll see when this is ran that it is linked, so changing the slider position is reflected in the rpm slider, controlled through this property binding
    }

    // This is just for testing, it's a slider that we can use to test our component
    Slider {
        id: slider
        // To figure out these properties, I googled for it and found an example in the QT documentation.
        from: 0
        value: 25
        to: 100
        width: parent.width
    }
}
