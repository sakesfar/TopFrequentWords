#ifndef ANALYZERLISTENER_H
#define ANALYZERLISTENER_H

#include <QObject>
#include <QVariantList>

class AnalyzerListener : public QObject
{
    Q_OBJECT
public:
    explicit AnalyzerListener(QObject *parent = nullptr);

public slots:
    void receiveMap(const QVariantList& result );
    void receiveProgPerc(int progressPercentage);
    void catchError(const QString &error);

signals:
    void sendMap( const QVariantList& result);
    void sendProgPerc(int progressPercentage);
    void emitError(const QString &error);

};

#endif // ANALYZERLISTENER_H
