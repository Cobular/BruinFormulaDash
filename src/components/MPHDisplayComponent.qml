import QtQuick 2.0

Item {

    property int mph: 101
    width: 112

    Text {
        id: mphUnitsLabel
        text: "MPH"
        font.pixelSize: 34
        font.bold: true
        rotation: 90
        y: 21
        x: 56
    }

    function parseIntToString(num) {
        var out = String(num % 100);
        while (out.length < 2) {
            out = "0" + out;
        }
        return out;
    }

    Text {
        id: mphValue
        text: parseIntToString(parent.mph)
        font.pixelSize: 72
        x: 0
        y: -4
    }

}
