#ifndef LEARNNORMAL_H
#define LEARNNORMAL_H

#include <QFrame>
#include <QTextToSpeech>

#include <LiLibrary/LiEasyLayout.h>
#include <LiLibrary/LiFixedToLayout.h>

#include "ReadPoetryData.h"
#include "UiFunction.h"

namespace Ui
{
    class LearnNormal;
}

class LearnNormal : public QFrame
{
    Q_OBJECT

public:
    explicit LearnNormal(QWidget *parent = nullptr);
    ~LearnNormal();

    void Init(const QString& sourcePath);

protected:
    virtual void resizeEvent(QResizeEvent * event);

private slots:
    void on_pushButtonRead_clicked();

    void on_pushButtonExit_clicked();

private:
    Ui::LearnNormal *ui;

    LiEasyLayout* l1;
    LiFixedToLayout* l2;

    ReadPoetryData* rpd;

    QStringList toReadParagraph;
    QString toReadWholeText;

    QTextToSpeech* tts;

signals:
    void ShowLearn();
};

#endif // LEARNNORMAL_H
