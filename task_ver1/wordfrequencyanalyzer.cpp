#include "WordFrequencyAnalyzer.h"



auto comp = [](const WordFreqPair& a, const WordFreqPair& b)
{
    return a.second > b.second;
};

WordFrequencyAnalyzer::WordFrequencyAnalyzer(QObject *parent)
    : QObject{parent}
{

}

void WordFrequencyAnalyzer::startProcessingFile(const QString &filePath)
{
    isCancelled=false;
    emit processFile(filePath);    
}


void WordFrequencyAnalyzer::handleFileProcessing(const QString &filePath)
{

    auto wordFrequency = buildWordFrequencyMap(filePath);
    auto topWords = findMostFrequentWords(wordFrequency,15);
    convertToVariantList(topWords);

}

QHash<QString, int> WordFrequencyAnalyzer::buildWordFrequencyMap(const QString &filePath)
{


    int totalWords = countTotalWords(filePath);


    QHash<QString, int> wordFrequency{};
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        emit errorOccurred("Error opening file");
        return wordFrequency;
    }

    int processedWords = 0;

    QTextStream in(&file);
    QString word;

    while (!in.atEnd() && !isCancelled)
    {

        {
         std::unique_lock<std::mutex> lock(pauseMutex);
         pauseCondition.wait(lock, [this]{ return !isPaused; });
        }

        if(isCancelled)
        {
            file.close();
            emit progressUpdated(0);
            //emit processingCompleted(QVariantList{});
            return {};
        }

         ++processedWords;

        in >> word;
        if (isAlphaWord(word))
        {
            wordFrequency[word]++;

        }

        int progressPercentage =(processedWords*100)/totalWords ;
        emit progressUpdated(progressPercentage);

    }


    file.close();
    return  wordFrequency  ;



}

bool WordFrequencyAnalyzer::isAlphaWord(QString &word)
{
    for (QChar ch : word)
    {        
        if (!ch.isLetter())
            return false;

    }
    word = word.toLower();
    return true;
}

QVector<WordFreqPair> WordFrequencyAnalyzer:: findMostFrequentWords( const QHash<QString, int>& wordFrequency, int k)
{



    std::priority_queue<WordFreqPair, std::vector<WordFreqPair>, decltype(comp)> minHeap(comp);

    for ( const auto& key : wordFrequency.keys())
    {
        WordFreqPair wordPair(key, wordFrequency[key]);
        minHeap.push(wordPair);

        if (minHeap.size() > k)
            minHeap.pop();

    }

    QVector<WordFreqPair> topWords;
    while (!minHeap.empty())
    {
        topWords.push_back(minHeap.top());
        minHeap.pop();
    }

    return topWords;    



}

void WordFrequencyAnalyzer::convertToVariantList(const QVector<WordFreqPair>& vector)
{

    QVariantList list;
    for (const auto &pair : vector)
    {
        QVariantMap map;
        map["key"] = pair.first;
        map["value"] = pair.second;
        list.append(map);
    }

    emit processingCompleted(list);


}

int WordFrequencyAnalyzer::countTotalWords(const QString &filePath) const
{
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return 0;

    QTextStream in(&file);
    int wordCount = 0;
    QString word;


    while (!in.atEnd())
      {

        in >> word;
        if (!word.isEmpty())
            wordCount++;
      }

    return wordCount;

}

void WordFrequencyAnalyzer::pauseProcessing()
{
    isPaused=true;

}

void WordFrequencyAnalyzer::resumeProcessing()
{
    std::unique_lock<std::mutex> lock(pauseMutex);
    isPaused=false;
    isCancelled=false;

    pauseCondition.notify_one();
}

void WordFrequencyAnalyzer::cancelProcessing()
{

    emit progressUpdated(0);
    isPaused=false;
    isCancelled=true;
    std::unique_lock<std::mutex> lock(pauseMutex);
    pauseCondition.notify_one();

}



