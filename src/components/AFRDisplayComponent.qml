import QtQuick 2.0

Item {

    property double afr: 240.98

    Text {
        id: afrUnitsLabel
        text: "AFR"
        color: "#ffffff"
        font.pixelSize: 34
        rotation: -90
        y: 21
        x: 0
    }

    function parseAfrToString(num) {
        var out = String(Math.floor(num) % 100);
        while (out.length < 2) {
            out = "  " + out;
        }
        return out + "." + Math.floor((10*num) % 10);
    }

    Text {
        id: afrValue
        text: parseAfrToString(parent.afr)
        color: "#ffffff"
        font.pixelSize: 72
        x: 55
        y: -4
    }

}
