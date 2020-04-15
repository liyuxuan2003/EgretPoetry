#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "Menu.h"

#include "DataInputMenu.h"
#include "DataInput.h"
#include "DataInputConfigInfo.h"
#include "DataInputConfigSource.h"
#include "DataInputConfigAlign.h"

#include "GlobalEnum.h"

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

    DataInputMenu* dataInputMenu;
    DataInput* dataInput;
    DataInputConfigInfo* dataInputConfigInfo;
    DataInputConfigSource* dataInputConfigSource;
    DataInputConfigAlign* dataInputConfigAlign;

    void HideAllFrame();
};

#endif // MAINWINDOW_H
