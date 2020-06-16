#ifndef LEARNSPLIT_H
#define LEARNSPLIT_H

#include <QFrame>
#include <QTextToSpeech>
#include <QScrollBar>

#include <LiLibrary/LiEasyLayout.h>
#include <LiLibrary/LiFixedToLayout.h>

#include "ReadPoetryData.h"
#include "UiFunction.h"

#include "Help.h"

namespace Ui
{
    class LearnSplit;
}

class LearnSplit : public QFrame
{
    Q_OBJECT

public:
    explicit LearnSplit(QWidget *parent = nullptr);
    ~LearnSplit();

    void Init(const QString& sourcePath,int mode);

protected:
    virtual void resizeEvent(QResizeEvent * event);

    virtual void keyPressEvent(QKeyEvent* ev);

private slots:
    void on_pushButtonLast_clicked();

    void on_pushButtonNext_clicked();

    void on_comboBoxMode_currentIndexChanged(int index);

    void on_pushButtonExit_clicked();

    void on_pushButtonRead_clicked();

    void on_pushButtonHelp_clicked();

private:
    Ui::LearnSplit *ui;

    LiEasyLayout* l1;
    LiFixedToLayout* l2;

    QTextToSpeech* tts;
    QString textToRead;

    Help* help;

    ReadPoetryData* rpd;
    int mode;

    int nowId;
    int totalNum;

    int lastMode;

    void AddFontString(QString& source,int begin,int end,QString beginString,QString endString);

    void GeneratePage();

    void GenerateSplitRead();
    void GenerateWord();
    void GenerateTran();

signals:
    void ShowLearn();
};

#endif // LEARNSPLIT_H
