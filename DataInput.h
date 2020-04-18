#ifndef DATAINPUT_H
#define DATAINPUT_H

#include <QFrame>
#include <QFile>
#include <QFileDialog>
#include <QPushButton>

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

#include <QTime>

#include <LiLibrary/LiEasyLayout.h>
#include <LiLibrary/LiFixedToLayout.h>

#include "GlobalEnum.h"

namespace Ui
{
    class DataInput;
}

class DataInput : public QFrame
{
    Q_OBJECT

public:
    explicit DataInput(QWidget *parent = nullptr);
    ~DataInput();

    void Init(const QString& path,const QString& name);

    void WrtieInfo(const QString& title,const QString& author,const QString& type);

    void WriteSource(const QStringList& sentenceOrig,const QStringList& sentenceTran,const QList<QPair<int,int>>& partOrig,const QList<QPair<int,int>>& partTran,SplitMode::Mode splitMode);

    void WriteAlign(const QList<QPair<int,int>>& align);

    void WriteWord(const QList<int>& wordInSentenceId,const QList<QPair<int,int>>& wordPos,const QStringList& wordMean);

    void WriteSent(const QList<QPair<int,int>>& sentenceId,const QStringList& sentenceMean);

protected:
    virtual void resizeEvent(QResizeEvent * event);

private slots:
    void on_pushButtonExit_clicked();

    void on_pushButtonInfo_clicked();

    void on_pushButtonSource_clicked();

    void on_pushButtonAlign_clicked();

    void on_pushButtonWord_clicked();

    void on_pushButtonSent_clicked();

    void on_pushButtonWriteData_clicked();

    void on_pushButtonReadData_clicked();

private:
    Ui::DataInput *ui;

    LiEasyLayout* l1;
    LiFixedToLayout* l2;

    //Json File
    QString path;
    QString name;

    //Config Info
    QString title;
    QString author;
    QString type;

    //Config Source
    QStringList sentenceOrig;
    QStringList sentenceTran;

    QList<QPair<int,int>> partOrig;
    QList<QPair<int,int>> partTran;

    SplitMode::Mode splitMode;

    //Config Align
    QList<QPair<int,int>> align;

    //Config Word
    QList<int> wordInSentenceId;
    QList<QPair<int,int>> wordPos;
    QStringList wordMean;

    //Config Sent
    QList<QPair<int,int>> sentenceId;
    QStringList sentenceMean;

    const QString symbol[6]={"。","，","？","！","；","："};
    const int symbolNum=6;

    QString GenerateTextOrig();
    QString GenerateTextTran();

    void DisabledButton(QPushButton* button);
    void EnabledButton(QPushButton* button);

signals:
    void ShowMenu();

    void ShowDataInputConfigInfo(const QString& title,const QString& author,const QString& type);

    void ShowDataInputConfigSource(const QString& textOrig,const QString& textTran);

    void ShowDataInputConfigAlign(const QString& textOrig,const QString& textTran,const QStringList& sentenceOrig,const QStringList& sentenceTran,const QList<QPair<int,int>>& partOrig,const QList<QPair<int,int>>& partTran,const QList<QPair<int,int>>& align);

    void ShowDataInputConfigWord(const QString& textOrig,const QString& textTran,const QStringList& sentenceOrig,const QList<int>& wordInSentenceId,const QList<QPair<int,int>>& wordPos,const QStringList& wordMean);

    void ShowDataInputConfigSent(const QString& textOrig,const QString& textTran,const QStringList& sentenceOrig,const QStringList& sentenceTran,const QList<QPair<int,int>>& align,const QList<QPair<int,int>>& sentenceId,const QStringList& sentenceMean);
};

#endif // DATAINPUT_H
