#ifndef RECITEWHOLE_H
#define RECITEWHOLE_H

#include <QFrame>
#include <QTextToSpeech>

#include <LiLibrary/LiEasyLayout.h>
#include <LiLibrary/LiFixedToLayout.h>

#include "ReadPoetryData.h"
#include "UiFunction.h"

#include "ReciteWholeReview.h"

namespace Ui
{
    class ReciteWhole;
}

class ReciteWhole : public QFrame
{
    Q_OBJECT

public:
    explicit ReciteWhole(QWidget *parent = nullptr);
    ~ReciteWhole();

    void Init(QString sourcePath,bool isManual);
    void Init(QString sourcePath,bool isManual,const QList<int>& needTest);

protected:
    virtual void resizeEvent(QResizeEvent * event);

    virtual void keyPressEvent(QKeyEvent *ev);

private slots:
    void on_lineEditUserAns_textEdited(const QString &arg1);

    void on_pushButtonNext_clicked();

    void on_pushButtonExit_clicked();

    void on_pushButtonOne_clicked();

    void on_pushButtonTwo_clicked();

    void on_pushButtonRead_clicked();

    void on_pushButtonAll_clicked();

    void on_pushButtonPunctuation_clicked();

private:
    Ui::ReciteWhole *ui;

    LiEasyLayout* l1;

    LiFixedToLayout* l2;

    ReciteWholeReview* reciteWholeReview;

    QTextToSpeech* tts;

    QString sourcePath;
    bool isManual;
    QList<int> needTest;

    ReadPoetryData* rpd;
    int nowId;

    QList<int> userRecord;

    void GeneratePage();

signals:
    void ShowMenu();
};

#endif // RECITEWHOLE_H
