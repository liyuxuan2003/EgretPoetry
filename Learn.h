#ifndef LEARN_H
#define LEARN_H

#include <QFrame>
#include <QFileDialog>

#include <LiLibrary/LiEasyLayout.h>
#include <LiLibrary/LiFixedToLayout.h>
#include <LiLibrary/LiFileName.h>

#include "ReadPoetryData.h"
#include "UiFunction.h"

namespace Ui
{
    class Learn;
}

class Learn : public QFrame
{
    Q_OBJECT

public:
    explicit Learn(QWidget *parent = nullptr);
    ~Learn();

    void Init();

protected:
    virtual void resizeEvent(QResizeEvent * event);

private slots:
    void on_pushButtonChoose_clicked();

    void on_pushButtonNormal_clicked();

    void on_pushButtonSplitRead_clicked();

    void on_pushButtonWord_clicked();

    void on_pushButtonSent_clicked();

    void on_pushButtonExit_clicked();

private:
    Ui::Learn *ui;

    LiEasyLayout* l1;
    LiFixedToLayout* l2;

    QString sourcePath;
    ReadPoetryData* rpd;

signals:
    void ShowLearnNormal(const QString& sourcePath);

    void ShowLearnSplit(const QString& sourcePath,int mode);

    void ShowMenu();

};

#endif // LEARN_H
