#ifndef RECITEWHOLEMENU_H
#define RECITEWHOLEMENU_H

#include <QFrame>
#include <QFileDialog>

#include <LiLibrary/LiEasyLayout.h>
#include <LiLibrary/LiFixedToLayout.h>

#include "ReadPoetryData.h"

namespace Ui
{
    class ReciteWholeMenu;
}

class ReciteWholeMenu : public QFrame
{
    Q_OBJECT

public:
    explicit ReciteWholeMenu(QWidget *parent = nullptr);
    ~ReciteWholeMenu();

    void Init();

protected:
    virtual void resizeEvent(QResizeEvent * event);

private:
    Ui::ReciteWholeMenu* ui;

    LiEasyLayout* l1;

    LiFixedToLayout* l2;

    QString sourcePath;

private slots:
    void on_pushButtonTest_clicked();
    void on_pushButtonStart_clicked();

    void on_pushButtonExit_clicked();

signals:
    void ShowReciteWhole(const QString& sourcePath,bool isManual);

    void ShowMenu();
};

#endif // RECITEWHOLEMENU_H
