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

private:
    Ui::Menu *ui;

    LiEasyLayout* l1;

    LiFixedToLayout* l2;
};

#endif // MENU_H
