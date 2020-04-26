#ifndef RANDOMPOETRYDATA_H
#define RANDOMPOETRYDATA_H

#include <QTime>
#include <QList>
#include <QPair>

#include <QDebug>

QList<QPair<int,int>> RandomSelect(int totalNum,int selectNum,const QList<int>& sectionNum);

QList<int> RandomOrder(int totalNum,bool isRandom);

#endif // RANDOMPOETRYDATA_H
