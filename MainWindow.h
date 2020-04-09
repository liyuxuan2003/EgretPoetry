#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "Menu.h"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    virtual void resizeEvent(QResizeEvent * event);

private:
    Ui::MainWindow* ui;

    Menu* menu;
};

#endif // MAINWINDOW_H
