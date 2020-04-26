#ifndef TRANWORD_H
#define TRANWORD_H

#include <QFrame>

#include <LiLibrary/LiEasyLayout.h>
#include <LiLibrary/LiFixedToLayout.h>

#include "ReadPoetryData.h"
#include "RandomPoetryData.h"

#include "TranWordReview.h"

namespace Ui
{
    class TranWord;
}

class TranWord : public QFrame
{
    Q_OBJECT

public:
    explicit TranWord(QWidget *parent = nullptr);
    ~TranWord();

    void Init(const QStringList& sourcePath,bool isRandom,QList<QPair<int,int>> needTest);

protected:
    virtual void resizeEvent(QResizeEvent * event);

private slots:
    void on_pushButtonCheck_clicked();

    void on_pushButtonAnsR_clicked();

    void on_pushButtonAnsW_clicked();

    void on_pushButtonExit_clicked();

private:
    Ui::TranWord* ui;

    LiEasyLayout* l1;

    LiFixedToLayout* l2;

    TranWordReview* tranWordReview;

    QStringList sourcePath;
    bool isRandom;
    QList<QPair<int,int>> needTest;

    QList<ReadPoetryData> rpd;
    QList<int> order;

    int nowId;
    QList<int> userRecord;

    void GeneratePage();

    void AddFontString(QString& source,int begin,int end,QString beginString,QString endString);

signals:
    void ShowMenu();
};

#endif // TRANWORD_H
