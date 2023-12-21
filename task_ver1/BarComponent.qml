import QtQuick 2.15
import QtQuick.Controls 2.15



Item {
    width:parent.width/totalBars-roW.spacing
    height:0.65*barChart.height*modelData.value/maxVal
    property int totalBars
    property int maxVal

    property color startColor1: "darkturquoise"
    property color endColor1: "darkslateblue"
    property color startColor2: "darkslateblue"
    property color endColor2: "maroon"


    Rectangle{
        id:rec
        anchors.bottom: parent.bottom
        width:parent.width
        height:parent.height
        color: index < 5 ? interpolateColor(index, 0, 4, startColor1, endColor1)
                                         : interpolateColor(index, 5, 9, startColor2, endColor2)

        transform: Scale {yScale:-1}

        Text{
            anchors.bottom: parent.top
            text:modelData.key
            transform: Scale {yScale:-1}
            rotation: -90
            color:"white"
            font.pixelSize: 14
        }

    }

    Text{
        id:freqNum
        y: -rec.height
        x:rec.x
        text:modelData.value
        color:"white"
        font.pixelSize: 12

    }


    function interpolateColor(index, startIndex, endIndex, startColor, endColor)
    {
            var fraction = (index - startIndex) / (endIndex - startIndex);
            var startR = parseInt(startColor.toString().substring(1, 3), 16);
            var startG = parseInt(startColor.toString().substring(3, 5), 16);
            var startB = parseInt(startColor.toString().substring(5, 7), 16);
            var endR = parseInt(endColor.toString().substring(1, 3), 16);
            var endG = parseInt(endColor.toString().substring(3, 5), 16);
            var endB = parseInt(endColor.toString().substring(5, 7), 16);

            var interpR = Math.round(lerp(startR, endR, fraction));
            var interpG = Math.round(lerp(startG, endG, fraction));
            var interpB = Math.round(lerp(startB, endB, fraction));

            return Qt.rgba(interpR / 255, interpG / 255, interpB / 255, 1);
        }

        function lerp(a, b, fraction)
        {
            return a + (b - a) * fraction;
        }




}
