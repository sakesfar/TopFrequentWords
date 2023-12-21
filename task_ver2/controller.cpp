#include "controller.h"

Controller::Controller(QObject *parent)
    : QObject{parent}
{

    WordFrequencyAnalyzer* analyzer = new WordFrequencyAnalyzer;
    analyzer->moveToThread(&workerThread);
    connect(&workerThread, &QThread::finished, analyzer, &QObject::deleteLater);



    connect(this, &Controller::startReading, analyzer, &WordFrequencyAnalyzer::startProcessingFile);
    connect(analyzer, &WordFrequencyAnalyzer::processingCompleted, this, &Controller::catchBarChart );
    connect(analyzer, &WordFrequencyAnalyzer::progressUpdated, this, &Controller::catchProgress );

    connect(this, &Controller::startPause, analyzer, &WordFrequencyAnalyzer::pauseProcessing);
    connect(this, &Controller::startResume, analyzer, &WordFrequencyAnalyzer::resumeProcessing);
    connect(this, &Controller::startCancel, analyzer, &WordFrequencyAnalyzer::cancelProcessing);



    workerThread.start();



}

Controller::~Controller()
{
    workerThread.quit();
    workerThread.wait();
}

void Controller::readPath(const QString &filepath)
{
    emit startReading(filepath);

}

void Controller::pause()
{
    emit startPause();

}

void Controller::resume()
{
    emit startResume();

}

void Controller::cancel()
{
    emit startCancel();

}


void Controller::catchBarChart(const QVariantList &result)
{
    emit barChartReady(result);
}

void Controller::catchProgress(int progress)
{
    emit sendProgress(progress);
}
