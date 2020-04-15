#ifndef DATAINPUTCONFIGSOURCE_H
#define DATAINPUTCONFIGSOURCE_H

#include <QFrame>

#include <LiLibrary/LiEasyLayout.h>
#include <LiLibrary/LiFixedToLayout.h>

#include "GlobalEnum.h"

namespace Ui
{
    class DataInputConfigSource;
}

class DataInputConfigSource : public QFrame
{
    Q_OBJECT

public:
    explicit DataInputConfigSource(QWidget *parent = nullptr);
    ~DataInputConfigSource();

    void Init(const QString& textOrig,const QString& textTran);

protected:
    virtual void resizeEvent(QResizeEvent * event);

private slots:
    void on_pushButtonDone_clicked();

private:
    Ui::DataInputConfigSource *ui;

    LiEasyLayout* l1;

    const QString symbol[6]={"。","，","？","！","；","："};
    const int symbolNum=6;

    void DataProcess(const QString& text,QStringList& sentence,QList<int>& lineBreak,QList<int>& section);
    void SetErrorText(const QString& errorText,QString& errorTextVar);

signals:
    void ConfigSourceDone(const QStringList& sentenceOrig,const QStringList& sentenceTran,const QList<QPair<int,int>>& partOrig,const QList<QPair<int,int>>& partTran,SplitMode::Mode splitMode);
};

#endif // DATAINPUTCONFIGSOURCE_H
