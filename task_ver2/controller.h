#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QThread>
#include "wordfrequencyanalyzer.h"

class Controller : public QObject
{
    Q_OBJECT
    QThread workerThread;
public:
    explicit Controller(QObject *parent = nullptr);
    Q_INVOKABLE void readPath(const QString& filepath);

    Q_INVOKABLE void pause();
    Q_INVOKABLE void resume();
    Q_INVOKABLE void cancel();


    ~Controller();

public slots:
    void catchBarChart(const QVariantList& result);
    void catchProgress(int progress);




signals:
    void startReading(const QString& filepath);
    void barChartReady(const QVariantList& result);

    void startPause();
    void startResume();
    void startCancel();

    void sendProgress(int progress);

};

#endif // CONTROLLER_H
