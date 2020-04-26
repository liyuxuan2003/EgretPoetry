#ifndef READPOETRYDATA_H
#define READPOETRYDATA_H

#include <QFile>

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

#include <QList>
#include <QString>
#include <QStringList>

#include <QDebug>

#include "GlobalEnum.h"

class ReadPoetryData
{
public:
    ReadPoetryData(QString source);

    bool IsError(){return isError;}

    const QString& GetTitle(){return title;}
    const QString& GetAuthor(){return author;}
    const QString& GetType(){return type;}

    const QStringList& GetSentenceOrig(){return sentenceOrig;}
    const QStringList& GetSentenceTran(){return sentenceTran;}

    const QList<QPair<int,int>>& GetPartOrig(){return partOrig;}
    const QList<QPair<int,int>>& GetPartTran(){return partTran;}

    const SplitMode::Mode& GetSplitMode(){return splitMode;}

    const QList<QPair<int,int>>& GetAlign(){return align;}

    const QList<int>& GetWordInSentenceId(){return wordInSentenceId;}
    const QList<QPair<int,int>>& GetWordPos(){return wordPos;}
    const QStringList& GetWordMean(){return wordMean;}

    const QList<QPair<int,int>>& GetSentenceId(){return sentenceId;}
    const QStringList& GetSentenceMean(){return sentenceMean;}

private:
    //Json File
    QString source;

    bool isError;

    //Config Info
    QString title;
    QString author;
    QString type;

    //Config Source
    QStringList sentenceOrig;
    QStringList sentenceTran;

    QList<QPair<int,int>> partOrig;
    QList<QPair<int,int>> partTran;

    SplitMode::Mode splitMode;

    //Config Align
    QList<QPair<int,int>> align;

    //Config Word
    QList<int> wordInSentenceId;
    QList<QPair<int,int>> wordPos;
    QStringList wordMean;

    //Config Sent
    QList<QPair<int,int>> sentenceId;
    QStringList sentenceMean;
};

#endif // READPOETRYDATA_H
