#ifndef DATAINPUTMENU_H
#define DATAINPUTMENU_H

#include <QFrame>

namespace Ui {
class DataInputMenu;
}

class DataInputMenu : public QFrame
{
    Q_OBJECT

public:
    explicit DataInputMenu(QWidget *parent = nullptr);
    ~DataInputMenu();

private:
    Ui::DataInputMenu *ui;
};

#endif // DATAINPUTMENU_H
