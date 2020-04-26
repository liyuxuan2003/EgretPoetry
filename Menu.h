#ifndef MENU_H
#define MENU_H

#include <QFrame>

#include <LiLibrary/LiEasyLayout.h>
#include <LiLibrary/LiFixedToLayout.h>

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

private:
    Ui::Menu *ui;

    LiEasyLayout* l1;

    LiFixedToLayout* l2;

signals:
    void ShowDataInputMenu();

    void ShowTranWordMenu();
};

#endif // MENU_H
