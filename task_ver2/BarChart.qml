import QtQuick 2.15
import QtQuick.Controls 2.15

Item {

    property var wordsModel:[]
    property int maxValue
    property int loadVal:0


    Row
    {
        id:roW
        anchors.top: parent.bottom
        anchors.topMargin: -120
        width: parent.width
        spacing:5

        Repeater
        {
            id:spread
            model: wordsModel
            delegate: BarComponent
            {
                maxVal:maxValue
                totalBars:spread.model.length
            }
        }

    }

    Rectangle{
        id:axisY
        anchors.left: roW.left
        anchors.leftMargin: -roW.spacing
        y: roW.y
        width:1
        color:"white"
        height:roW.height
        transform: Scale{yScale: -1}
    }

    Rectangle{
        id:axisX
        anchors.left: roW.left
        anchors.leftMargin: -roW.spacing
        y: roW.y
        width:roW.width
        height:1
        color:"white"
        visible: maxValue>0 ? true :false

    }












}
