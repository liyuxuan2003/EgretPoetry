#ifndef DATAINPUTCONFIGALIGN_H
#define DATAINPUTCONFIGALIGN_H

#include <QFrame>

#include <QPushButton>

#include <LiLibrary/LiEasyLayout.h>
#include <LiLibrary/LiFixedToLayout.h>

#include <UiFunction.h>

namespace Ui
{
    class DataInputConfigAlign;
}

class DataInputConfigAlign : public QFrame
{
    Q_OBJECT

public:
    explicit DataInputConfigAlign(QWidget *parent = nullptr);
    ~DataInputConfigAlign();

    void Init(const QString& textOrig,const QString& textTran,const QStringList& sentenceOrig,const QStringList& sentenceTran,const QList<QPair<int,int>>& partOrig,const QList<QPair<int,int>>& partTran,const QList<QPair<int,int>>& align);

protected:
    virtual void resizeEvent(QResizeEvent* event);

    virtual void keyPressEvent(QKeyEvent* ev);

private slots:
    void on_pushButtonMinus_clicked();

    void on_pushButtonPlus_clicked();

    void on_pushButtonLast_clicked();

    void on_pushButtonNext_clicked();

    void on_pushButtonDone_clicked();

private:
    Ui::DataInputConfigAlign *ui;

    LiEasyLayout* l1;

    QStringList sentenceOrig;
    QStringList sentenceTran;

    QList<QPair<int,int>> partOrig;
    QList<QPair<int,int>> partTran;

    QList<int> alignPrefix;

    int nowIdOrig;
    int nowIdTran;

    void GenerateOperate();

    int GetPartId(const QList<QPair<int,int>>& part,int id);

signals:
    void ConfigAlignDone(const QList<QPair<int,int>>& align);
};

#endif // DATAINPUTCONFIGALIGN_H
