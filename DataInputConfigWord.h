#ifndef DATAINPUTCONFIGWORD_H
#define DATAINPUTCONFIGWORD_H

#include <QFrame>

#include <QPushButton>

#include <LiLibrary/LiEasyLayout.h>
#include <LiLibrary/LiFixedToLayout.h>

namespace Ui
{
    class DataInputConfigWord;
}

class DataInputConfigWord : public QFrame
{
    Q_OBJECT

public:
    explicit DataInputConfigWord(QWidget *parent = nullptr);
    ~DataInputConfigWord();

    void Init(const QString& textOrig,const QString& textTran,const QStringList& sentenceOrig,const QList<int>& wordInSentenceId,const QList<QPair<int,int>>& wordPos,const QStringList& wordMean);

protected:
    virtual void resizeEvent(QResizeEvent * event);

private slots:
    void on_pushButtonSentLast_clicked();

    void on_pushButtonSentNext_clicked();

    void on_pushButtonWordLast_clicked();

    void on_pushButtonWordNext_clicked();

    void on_pushButtonWordMinus_clicked();

    void on_pushButtonWordPlus_clicked();

    void on_pushButtonNoteLast_clicked();

    void on_pushButtonNoteNext_clicked();

    void on_pushButtonNoteInsert_clicked();

    void on_pushButtonDone_clicked();

private:
    Ui::DataInputConfigWord *ui;

    LiEasyLayout* l1;

    QStringList sentenceOrig;

    QList<int> wordInSentenceId;
    QList<QPair<int,int>> wordPos;
    QStringList wordMean;

    int nowNoteId;

    void GenerateWord();

    void DisabledButton(QPushButton* button);
    void EnabledButton(QPushButton* button);

signals:
    void ConfigWordDone(const QList<int>& wordInSentenceId,const QList<QPair<int,int>>& wordPos,const QStringList& wordMean);
};

#endif // DATAINPUTCONFIGWORD_H
