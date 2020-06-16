#ifndef TRANSENT_H
#define TRANSENT_H

#include <QFrame>
#include <QScrollBar>

#include <LiLibrary/LiEasyLayout.h>
#include <LiLibrary/LiFixedToLayout.h>

#include "ReadPoetryData.h"
#include "RandomPoetryData.h"

#include "TranSentReview.h"

#include "Help.h"

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

private slots:
    void on_pushButtonCheck_clicked();

    void on_pushButtonAnsR_clicked();

    void on_pushButtonAnsW_clicked();

    void on_pushButtonExit_clicked();

    void on_pushButtonHelp_clicked();

private:
    Ui::TranSent *ui;

    LiEasyLayout* l1;

    LiFixedToLayout* l2;

    Help* help;

    TranSentReview* tranSentReview;

    QStringList sourcePath;
    bool isRandom;
    QList<QPair<int,int>> needTest;

    QList<ReadPoetryData*> rpd;
    QList<int> order;

    int nowId;
    QList<int> userRecord;

    void GeneratePage();

signals:
    void ShowMenu();
};

#endif // TRANSENT_H
