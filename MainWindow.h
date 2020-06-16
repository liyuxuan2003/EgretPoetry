#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "Menu.h"

#include "DataInputMenu.h"
#include "DataInput.h"
#include "DataInputConfigInfo.h"
#include "DataInputConfigSource.h"
#include "DataInputConfigAlign.h"
#include "DataInputConfigWord.h"
#include "DataInputConfigSent.h"

#include "TranWordMenu.h"
#include "TranWord.h"

#include "TranSentMenu.h"
#include "TranSent.h"

#include "ReciteWholeMenu.h"
#include "ReciteWhole.h"

#include "Learn.h"
#include "LearnNormal.h"
#include "LearnSplit.h"

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
    DataInputConfigWord* dataInputConfigWord;
    DataInputConfigSent* dataInputConfigSent;

    TranWordMenu* tranWordMenu;
    TranWord* tranWord;

    TranSentMenu* tranSentMenu;
    TranSent* tranSent;

    ReciteWholeMenu* reciteWholeMenu;
    ReciteWhole* reciteWhole;

    Learn* learn;
    LearnNormal* learnNormal;
    LearnSplit* learnSplit;

    void HideAllFrame();
};

#endif // MAINWINDOW_H
