#ifndef MENU_H
#define MENU_H

#include <QFrame>

#include <LiLibrary/LiEasyLayout.h>
#include <LiLibrary/LiFixedToLayout.h>

#include "UiFunction.h"
#include "About.h"

namespace Ui
{
    class Menu;
}

class Menu : public QFrame
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = nullptr);
    ~Menu();

protected:
    virtual void resizeEvent(QResizeEvent * event);

private slots:
    void on_pushButtonDataInput_clicked();

    void on_pushButtonTransWord_clicked();

    void on_pushButtonTransSent_clicked();

    void on_pushButtonReciteWhole_clicked();

    void on_pushButtonLearn_clicked();

    void on_pushButtonAbout_clicked();

    void on_pushButtonExit_clicked();

private:
    Ui::Menu *ui;

    LiEasyLayout* l1;

    LiFixedToLayout* l2;

    About* about;

signals:
    void ShowDataInputMenu();

    void ShowTranWordMenu();

    void ShowTranSentMenu();

    void ShowReciteWholeMenu();

    void ShowLearn();
};

#endif // MENU_H
