#ifndef WORDFREQUENCYANALYZER_H
#define WORDFREQUENCYANALYZER_H

#include <QObject>
#include <QString>
#include <QHash>
#include <QVector>
#include <vector>
#include <queue>
#include <QVariantList>
#include <QThread>
#include <QFile>
#include <QTextStream>
#include <QVariantMap>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <QThreadPool>

using WordFreqPair = QPair<QString, int>;



class WordFrequencyAnalyzer : public QObject
{
    Q_OBJECT
public:
    explicit WordFrequencyAnalyzer(QObject *parent = nullptr);

    //Q_INVOKABLE void pauseProcessing();
    //Q_INVOKABLE void resumeProcessing();
    //Q_INVOKABLE void cancelProcessing();

signals:
    void processingCompleted( const QVariantList& result);
    void errorOccurred(const QString &error);   
    void progressUpdated(int progressPercentage);

public slots:
    void startProcessingFile(const QString &filePath);
    void handleFileProcessing(const QString &filePath);

     void pauseProcessing();
     void resumeProcessing();
     void cancelProcessing();


private:
    QHash<QString, int> buildWordFrequencyMap(const QString &filePath);
    bool isAlphaWord(QString &word);
    QVector<WordFreqPair> findMostFrequentWords(const QHash<QString, int>& wordFrequency, int k);
    void convertToVariantList(const QVector<WordFreqPair>& vector);
    int countTotalWords(const QString &filePath) const;


    std::atomic<bool> isPaused{false};
    std::atomic<bool> isCancelled{false};
    std::mutex pauseMutex;
    std::condition_variable pauseCondition;




};

#endif // WORDFREQUENCYANALYZER_H
