#ifndef DATAINPUTCONFIGSENT_H
#define DATAINPUTCONFIGSENT_H

#include <QFrame>
#include <QPushButton>

#include <LiLibrary/LiEasyLayout.h>
#include <LiLibrary/LiFixedToLayout.h>

#include "UiFunction.h"

namespace Ui
{
    class DataInputConfigSent;
}

class DataInputConfigSent : public QFrame
{
    Q_OBJECT

public:
    explicit DataInputConfigSent(QWidget *parent = nullptr);
    ~DataInputConfigSent();

    void Init(const QString& textOrig,const QString& textTran,const QStringList& sentenceOrig,const QStringList& sentenceTran,const QList<QPair<int,int>>& align,const QList<QPair<int,int>>& sentenceId,const QStringList& sentenceMean);

protected:
    virtual void resizeEvent(QResizeEvent* event);

    virtual void keyPressEvent(QKeyEvent* ev);

private slots:
    void on_pushButtonSentLast_clicked();

    void on_pushButtonSentNext_clicked();

    void on_pushButtonSentMinus_clicked();

    void on_pushButtonSentPlus_clicked();

    void on_pushButtonUseTran_clicked();

    void on_pushButtonNoteLast_clicked();

    void on_pushButtonNoteNext_clicked();

    void on_pushButtonNoteInsert_clicked();

    void on_pushButtonNoteDelete_clicked();

    void on_pushButtonDone_clicked();

private:
    Ui::DataInputConfigSent *ui;

    LiEasyLayout* l1;

    QStringList sentenceOrig;
    QStringList sentenceTran;

    QList<QPair<int,int>> align;

    QList<QPair<int,int>> sentenceId;
    QStringList sentenceMean;

    int nowNoteId;

    void GenerateSent();

signals:
    void ConfigSentDone(const QList<QPair<int,int>>& sentenceId,const QStringList& sentenceMean);

};

#endif // DATAINPUTCONFIGSENT_H
