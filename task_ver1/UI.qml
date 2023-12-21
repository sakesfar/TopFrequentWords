import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Dialogs

Item {

    property string fileName:""

    Connections{
        target:listener
        onSendMap:{

            if(result.length>0)
            {

            barChart.wordsModel=result
            barChart.maxValue=result[result.length-1].value

            }
            else
            {
                barChart.wordsModel=[]
                barChart.maxValue=0
            }

        }

        onSendProgPerc: loadingStatus.value=progressPercentage/100

        onEmitError : console.log(error);
    }

    BarChart{
        id:barChart
        anchors.bottom: parent.bottom
        anchors.top:parent.top
        anchors.right:parent.right
        anchors.rightMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10
        loadVal: 0
        wordsModel: []
    }



    FileDialog {
        id: fileDialog
        title: "Выберите .txt файл"
        nameFilters: ["Text files (*.txt)"] // Я попытался добавить "MS Word files (*.docx)"
        onAccepted: {
            var path =fileDialog.currentFile.toString().replace("file:///", "" )
            fileName=path
            }
        }

    Row{
        id:uiButtons
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        spacing:parent.width*0.05
        width:parent.width -anchors.leftMargin-anchors.rightMargin
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10


        property int numButtons: 5
        property real totalSpacing: (numButtons - 1) * spacing
        property real buttonW: (uiButtons.width - totalSpacing) / numButtons
        property real buttonH:parent.height*0.05



        Button {
            id:open
            width:uiButtons.buttonW
            height:uiButtons.buttonH
            text: "Открыть"
            onClicked: fileDialog.open()
        }

        Button {
            id:start
            width:uiButtons.buttonW
            height:uiButtons.buttonH
            text: "Старт"
            onClicked: analyzer.startProcessingFile(fileName)
        }

        Button {
            id:pause
            width:uiButtons.buttonW
            height:uiButtons.buttonH
            text: "Пауза"
            onClicked: analyzer.pauseProcessing()
        }

        Button {
            id:resume
            width:uiButtons.buttonW
            height:uiButtons.buttonH
            text: "Возобновить"
            onClicked: analyzer.resumeProcessing()
        }

        Button {
            id:cancel
            width:uiButtons.buttonW
            height:uiButtons.buttonH
            text: "Отмена"
            onClicked: {analyzer.cancelProcessing() ; barChart.wordsModel=[] ; barChart.maxValue=0 }
        }


    }




    ProgressBar{
        id:loadingStatus
        anchors.top: parent.top
        anchors.topMargin: 20
        width: parent.width
        height: 10
        value:0
        visible: (value !== 0 && value !== 1) ? true : false

    }

}
