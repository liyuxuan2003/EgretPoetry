#ifndef TRANSENTMENU_H
#define TRANSENTMENU_H

#include <QFrame>
#include <QFileDialog>

#include <LiLibrary/LiEasyLayout.h>
#include <LiLibrary/LiFixedToLayout.h>

#include "ReadPoetryData.h"
#include "RandomPoetryData.h"

namespace Ui
{
    class TranSentMenu;
}

class TranSentMenu : public QFrame
{
    Q_OBJECT

public:
    explicit TranSentMenu(QWidget *parent = nullptr);
    ~TranSentMenu();
    void Init();

protected:
    virtual void resizeEvent(QResizeEvent * event);

private:
    Ui::TranSentMenu* ui;

    LiEasyLayout* l1;

    LiFixedToLayout* l2;

    QStringList sourcePath;

private slots:
    void on_radioButtonOrdered_clicked();
    void on_radioButtonRandom_clicked();

    void on_radioButtonSelect_clicked();
    void on_pushButtonTest_clicked();
    void on_pushButtonStart_clicked();

    void on_pushButtonExit_clicked();

signals:
    void ShowTranSent(const QStringList& sourcePath,bool isRandom,QList<QPair<int,int>> needTest);

    void ShowMenu();
};

#endif // TRANSENTMENU_H
