#ifndef TRANSENT_H
#define TRANSENT_H

#include <QFrame>

#include <LiLibrary/LiEasyLayout.h>
#include <LiLibrary/LiFixedToLayout.h>

#include "ReadPoetryData.h"
#include "RandomPoetryData.h"

#include "TranWordReview.h"

namespace Ui
{
    class TranSent;
}

class TranSent : public QFrame
{
    Q_OBJECT

public:
    explicit TranSent(QWidget *parent = nullptr);
    ~TranSent();

    void Init(const QStringList& sourcePath,bool isRandom,QList<QPair<int,int>> needTest);

protected:
    virtual void resizeEvent(QResizeEvent * event);

    virtual void keyPressEvent(QKeyEvent *ev);

private:
    Ui::TranSent *ui;

    LiEasyLayout* l1;

    LiFixedToLayout* l2;

    QStringList sourcePath;
    bool isRandom;
    QList<QPair<int,int>> needTest;
};

#endif // TRANSENT_H
