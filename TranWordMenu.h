#ifndef TRANWORDMENU_H
#define TRANWORDMENU_H

#include <QFrame>
#include <QFileDialog>

#include <LiLibrary/LiEasyLayout.h>
#include <LiLibrary/LiFixedToLayout.h>

#include "ReadPoetryData.h"
#include "RandomPoetryData.h"

namespace Ui
{
    class TranWordMenu;
}

class TranWordMenu : public QFrame
{
    Q_OBJECT

public:
    explicit TranWordMenu(QWidget *parent = nullptr);
    ~TranWordMenu();

    void Init();

protected:
    virtual void resizeEvent(QResizeEvent * event);

private:
    Ui::TranWordMenu* ui;

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
    void ShowTranWord(const QStringList& sourcePath,bool isRandom,QList<QPair<int,int>> needTest);

    void ShowMenu();
};

#endif // TRANWORDMENU_H
