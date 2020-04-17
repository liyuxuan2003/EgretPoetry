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

    dataInputConfigAlign=new DataInputConfigAlign(this);
    dataInputConfigAlign->move(0,0);

    dataInputConfigWord=new DataInputConfigWord(this);
    dataInputConfigWord->move(0,0);

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
    connect(dataInput,&DataInput::ShowDataInputConfigSource,[=](const QString& textOrig,const QString& textTran)
    {
        HideAllFrame();
        dataInputConfigSource->show();
        dataInputConfigSource->Init(textOrig,textTran);
    });

    connect(dataInputConfigSource,&DataInputConfigSource::ConfigSourceDone,[=](const QStringList& sentenceOrig,const QStringList& sentenceTran,const QList<QPair<int,int>>& partOrig,const QList<QPair<int,int>>& partTran,SplitMode::Mode splitMode)
    {
        HideAllFrame();
        dataInput->show();
        dataInput->WriteSource(sentenceOrig,sentenceTran,partOrig,partTran,splitMode);
    });

    //DataInput <=> DataInputConfigAlign
    connect(dataInput,&DataInput::ShowDataInputConfigAlign,[=](const QString& textOrig,const QString& textTran,const QStringList& sentenceOrig,const QStringList& sentenceTran,const QList<QPair<int,int>>& partOrig,const QList<QPair<int,int>>& partTran,const QList<QPair<int,int>>& align)
    {
        HideAllFrame();
        dataInputConfigAlign->show();
        dataInputConfigAlign->Init(textOrig,textTran,sentenceOrig,sentenceTran,partOrig,partTran,align);
    });

    connect(dataInputConfigAlign,&DataInputConfigAlign::ConfigAlignDone,[=](const QList<QPair<int,int>>& align)
    {
        HideAllFrame();
        dataInput->show();
        dataInput->WriteAlign(align);
    });

    //DataInput <=> DataInputConfigWord
    connect(dataInput,&DataInput::ShowDataInputConfigWord,[=](const QString& textOrig,const QString& textTran,const QStringList& sentenceOrig,const QList<int>& wordInSentenceId,const QList<QPair<int,int>>& wordPos,const QStringList& wordMean)
    {
        HideAllFrame();
        dataInputConfigWord->show();
        dataInputConfigWord->Init(textOrig,textTran,sentenceOrig,wordInSentenceId,wordPos,wordMean);
    });

    connect(dataInputConfigWord,&DataInputConfigWord::ConfigWordDone,[=](const QList<int>& wordInSentenceId,const QList<QPair<int,int>>& wordPos,const QStringList& wordMean)
    {
        HideAllFrame();
        dataInput->show();
        dataInput->WriteWord(wordInSentenceId,wordPos,wordMean);
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
    dataInputConfigAlign->resize(width(),height());
    dataInputConfigWord->resize(width(),height());
}

void MainWindow::HideAllFrame()
{
    menu->hide();

    dataInputMenu->hide();
    dataInput->hide();
    dataInputConfigInfo->hide();
    dataInputConfigSource->hide();
    dataInputConfigAlign->hide();
    dataInputConfigWord->hide();
}
