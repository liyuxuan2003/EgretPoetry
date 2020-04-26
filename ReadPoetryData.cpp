#include "ReadPoetryData.h"

ReadPoetryData::ReadPoetryData(QString source)
{
    this->source=source;

    QFile file(source);
    file.open(QIODevice::ReadOnly);

    QByteArray jsonData=file.readAll();
    file.close();

    QJsonParseError jsonError;
    QJsonDocument jsonDoc(QJsonDocument::fromJson(jsonData,&jsonError));

    if(jsonError.error!=QJsonParseError::NoError)
    {
        isError=true;
        return;
    }

    isError=false;

    QJsonObject jsonObjectRoot=jsonDoc.object();

    QJsonArray temp;

    //Config Info
    title=jsonObjectRoot.value("title").toString();
    author=jsonObjectRoot.value("author").toString();
    type=jsonObjectRoot.value("type").toString();

    //Config Source
    temp=jsonObjectRoot.value("sentenceOrig").toArray();
    sentenceOrig.clear();
    for(int i=0;i<temp.size();i++)
        sentenceOrig.append(temp[i].toString());

    temp=jsonObjectRoot.value("sentenceTran").toArray();
    sentenceTran.clear();
    for(int i=0;i<temp.size();i++)
        sentenceTran.append(temp[i].toString());

    temp=jsonObjectRoot.value("partOrig").toArray();
    partOrig.clear();
    for(int i=0;i<temp.size();i++)
        partOrig.append(QPair<int,int>(temp[i].toObject().value("first").toInt(),temp[i].toObject().value("second").toInt()));

    temp=jsonObjectRoot.value("partTran").toArray();
    partTran.clear();
    for(int i=0;i<temp.size();i++)
        partTran.append(QPair<int,int>(temp[i].toObject().value("first").toInt(),temp[i].toObject().value("second").toInt()));

    splitMode=(SplitMode::Mode)jsonObjectRoot.value("splitMode").toInt();

    //Config Align
    temp=jsonObjectRoot.value("align").toArray();
    align.clear();
    for(int i=0;i<temp.size();i++)
        align.append(QPair<int,int>(temp[i].toObject().value("first").toInt(),temp[i].toObject().value("second").toInt()));

    //Config Word
    temp=jsonObjectRoot.value("wordInSentenceId").toArray();
    wordInSentenceId.clear();
    for(int i=0;i<temp.size();i++)
        wordInSentenceId.append(temp[i].toInt());

    temp=jsonObjectRoot.value("wordPos").toArray();
    wordPos.clear();
    for(int i=0;i<temp.size();i++)
        wordPos.append(QPair<int,int>(temp[i].toObject().value("first").toInt(),temp[i].toObject().value("second").toInt()));

    //Config Sent
    temp=jsonObjectRoot.value("wordMean").toArray();
    wordMean.clear();
    for(int i=0;i<temp.size();i++)
        wordMean.append(temp[i].toString());

    temp=jsonObjectRoot.value("sentenceId").toArray();
    sentenceId.clear();
    for(int i=0;i<temp.size();i++)
        sentenceId.append(QPair<int,int>(temp[i].toObject().value("first").toInt(),temp[i].toObject().value("second").toInt()));

    temp=jsonObjectRoot.value("sentenceMean").toArray();
    sentenceMean.clear();
    for(int i=0;i<temp.size();i++)
        sentenceMean.append(temp[i].toString());
}
