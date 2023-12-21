#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "WordFrequencyAnalyzer.h"
#include "analyzerlistener.h"



int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);


    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);


    WordFrequencyAnalyzer* analyzer = new WordFrequencyAnalyzer();
    QThread* workerThread = new QThread();
    AnalyzerListener listener;

    analyzer->moveToThread(workerThread);
    QObject::connect(analyzer, &WordFrequencyAnalyzer::processFile, analyzer, &WordFrequencyAnalyzer::handleFileProcessing);    
    QObject::connect(analyzer, &WordFrequencyAnalyzer::processingCompleted, &listener, &AnalyzerListener::receiveMap);    
    QObject::connect(analyzer, &WordFrequencyAnalyzer::progressUpdated, &listener, &AnalyzerListener::receiveProgPerc);

    QObject::connect(&app, &QCoreApplication::aboutToQuit, workerThread, &QThread::quit);
    QObject::connect(workerThread, &QThread::finished, analyzer, &QObject::deleteLater);
    QObject::connect(workerThread, &QThread::finished, workerThread, &QObject::deleteLater);
    workerThread->start();


    engine.rootContext()->setContextProperty("analyzer", analyzer);
    engine.rootContext()->setContextProperty("listener", &listener);



    engine.load(url);

    return app.exec();
}
