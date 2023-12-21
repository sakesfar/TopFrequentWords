#include "analyzerlistener.h"

AnalyzerListener::AnalyzerListener(QObject *parent)
    : QObject{parent}
{

}

void AnalyzerListener::receiveMap(const QVariantList &result)
{
    emit sendMap(result);
}

void AnalyzerListener::receiveProgPerc(int progressPercentage)
{
    emit sendProgPerc(progressPercentage);
}

void AnalyzerListener::catchError(const QString &error)
{

    emit emitError(error);

}
