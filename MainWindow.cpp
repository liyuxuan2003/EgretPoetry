#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    menu=new Menu(this);
    menu->move(0,0);

    dataInputMenu=new DataInputMenu(this);
    dataInputMenu->move(0,0);

    dataInput=new DataInput(this);
    dataInput->move(0,0);

    dataInputConfigInfo=new DataInputConfigInfo(this);
    dataInputConfigInfo->move(0,0);

    dataInputConfigSource=new DataInputConfigSource(this);
    dataInputConfigSource->move(0,0);

    //Menu
    connect(menu,&Menu::ShowDataInputMenu,[=]()
    {
        HideAllFrame();
        dataInputMenu->show();
        dataInputMenu->Init();
    });

    //DataInput
    connect(dataInputMenu,&DataInputMenu::ShowMenu,[=]()
    {
        HideAllFrame();
        menu->show();
    });

    connect(dataInput,&DataInput::ShowMenu,[=]()
    {
        HideAllFrame();
        menu->show();
    });

    connect(dataInputMenu,&DataInputMenu::ShowDataInput,[=](const QString& path,const QString& name)
    {
        HideAllFrame();
        dataInput->show();
        dataInput->Init(path,name);
    });

    //DataInput <=> DataInputConfigInfo
    connect(dataInput,&DataInput::ShowDataInputConfigInfo,[=](const QString& title,const QString& author,const QString& type)
    {
        HideAllFrame() ;
        dataInputConfigInfo->show();
        dataInputConfigInfo->Init(title,author,type);
    });

    connect(dataInputConfigInfo,&DataInputConfigInfo::ConfigInfoDone,[=](const QString& title,const QString& author,const QString& type)
    {
        HideAllFrame();
        dataInput->show();
        dataInput->WrtieInfo(title,author,type);
    });

    //DataInput <=> DataInputConfigSource

    connect(dataInput,&DataInput::ShowDataInputConfigSource,[=](const QString& original,const QString& translate)
    {
        HideAllFrame();
        dataInputConfigSource->show();
        dataInputConfigSource->Init(original,translate);
    });

    connect(dataInputConfigSource,&DataInputConfigSource::ConfigSourceDone,[=](const QString& original,const QString& translate)
    {
        HideAllFrame();
        dataInput->show();
        dataInput->WriteSource(original,translate);
    });


    HideAllFrame();
    menu->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    menu->resize(width(),height());

    dataInputMenu->resize(width(),height());
    dataInput->resize(width(),height());
    dataInputConfigInfo->resize(width(),height());
    dataInputConfigSource->resize(width(),height());
}

void MainWindow::HideAllFrame()
{
    menu->hide();

    dataInputMenu->hide();
    dataInput->hide();
    dataInputConfigInfo->hide();
    dataInputConfigSource->hide();
}
