#include "RandomPoetryData.h"

QList<QPair<int,int>> RandomSelect(int totalNum,int selectNum,const QList<int>& sectionNum)
{
    QTime time=QTime::currentTime();
    qsrand(time.msec()+time.second()*1000);

    QList<QPair<int,int>> result;

    bool* randomArray=new bool[totalNum]{false};
    for(int i=0;i<selectNum;i++)
    {
        int randNum=0;

        do randNum=qrand()%totalNum;
        while(randomArray[randNum]==true);

        randomArray[randNum]=true;
    }

    int nowSection=0;
    int nowSectionInsideId=0;
    int preSectionSum=0;
    for(int i=0;i<totalNum;i++)
    {
        if(nowSectionInsideId==sectionNum[nowSection])
        {
            preSectionSum+=sectionNum[nowSection];
            nowSection++;
            nowSectionInsideId=0;
        }

        if(randomArray[i]==true)
            result.append(QPair<int,int>(nowSection,i-preSectionSum));

        nowSectionInsideId++;
    }

    return result;
}

QList<int> RandomOrder(int totalNum,bool isRandom)
{
    QTime time=QTime::currentTime();
    qsrand(time.msec()+time.second()*1000);

    QList<int> result;
    for(int i=0;i<totalNum;i++)
        result.append(i);

    if(isRandom==false)
        return result;
    else
    {
        for(int i=0;i<10*result.size();i++)
        {
            int q1=qrand()%result.size();
            int q2=qrand()%result.size();
            qSwap(result[q1],result[q2]);
        }
    }

    return result;
}
