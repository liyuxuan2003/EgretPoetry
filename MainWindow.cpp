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

    dataInputConfigSent=new DataInputConfigSent(this);
    dataInputConfigSent->move(0,0);

    tranWordMenu=new TranWordMenu(this);
    tranWordMenu->move(0,0);

    tranWord=new TranWord(this);
    tranWord->move(0,0);

    tranSentMenu=new TranSentMenu(this);
    tranSentMenu->move(0,0);

    tranSent=new TranSent(this);
    tranSent->move(0,0);

    reciteWholeMenu=new ReciteWholeMenu(this);
    reciteWholeMenu->move(0,0);

    reciteWhole=new ReciteWhole(this);
    reciteWhole->move(0,0);

    learn=new Learn(this);
    learn->move(0,0);

    learnNormal=new LearnNormal(this);
    learnNormal->move(0,0);

    learnSplit=new LearnSplit(this);
    learnSplit->move(0,0);

    //Menu
    connect(menu,&Menu::ShowDataInputMenu,[=]()
    {
        HideAllFrame();
        dataInputMenu->show();
        dataInputMenu->Init();
    });

    connect(menu,&Menu::ShowTranWordMenu,[=]()
    {
        HideAllFrame();
        tranWordMenu->show();
        tranWordMenu->Init();
    });

    connect(menu,&Menu::ShowTranSentMenu,[=]()
    {
        HideAllFrame();
        tranSentMenu->show();
        tranSentMenu->Init();
    });

    connect(menu,&Menu::ShowReciteWholeMenu,[=]()
    {
        HideAllFrame();
        reciteWholeMenu->show();
        reciteWholeMenu->Init();
    });

    connect(menu,&Menu::ShowLearn,[=]()
    {
        HideAllFrame();
        learn->show();
        learn->Init();
    });

    //TranWord
    connect(tranWordMenu,&TranWordMenu::ShowMenu,[=]()
    {
        HideAllFrame();
        menu->show();
    });

    connect(tranWord,&TranWord::ShowMenu,[=]()
    {
        HideAllFrame();
        menu->show();
    });

    connect(tranWordMenu,&TranWordMenu::ShowTranWord,[=](const QStringList& sourcePath,bool isRandom,QList<QPair<int,int>> needTest)
    {
        HideAllFrame();
        tranWord->show();
        tranWord->Init(sourcePath,isRandom,needTest);
    });

    //TranSent
    connect(tranSentMenu,&TranSentMenu::ShowMenu,[=]()
    {
        HideAllFrame();
        menu->show();
    });

    connect(tranSent,&TranSent::ShowMenu,[=]()
    {
        HideAllFrame();
        menu->show();
    });

    connect(tranSentMenu,&TranSentMenu::ShowTranSent,[=](const QStringList& sourcePath,bool isRandom,QList<QPair<int,int>> needTest)
    {
        HideAllFrame();
        tranSent->show();
        tranSent->Init(sourcePath,isRandom,needTest);
    });

    //ReciteWhole
    connect(reciteWholeMenu,&ReciteWholeMenu::ShowMenu,[=]()
    {
        HideAllFrame();
        menu->show();
    });

    connect(reciteWhole,&ReciteWhole::ShowMenu,[=]()
    {
        HideAllFrame();
        menu->show();
    });

    connect(reciteWholeMenu,&ReciteWholeMenu::ShowReciteWhole,[=](const QString& sourcePath,bool isManual)
    {
        HideAllFrame();
        reciteWhole->show();
        reciteWhole->Init(sourcePath,isManual);
    });

    //Learn
    connect(learn,&Learn::ShowLearnNormal,[=](const QString& sourcePath)
    {
        HideAllFrame();
        learnNormal->show();
        learnNormal->Init(sourcePath);
    });

    connect(learn,&Learn::ShowLearnSplit,[=](const QString& sourcePath,int mode)
    {
        HideAllFrame();
        learnSplit->show();
        learnSplit->Init(sourcePath,mode);
    });

    connect(learnNormal,&LearnNormal::ShowLearn,[=]()
    {
        HideAllFrame();
        learn->show();
    });

    connect(learnSplit,&LearnSplit::ShowLearn,[=]()
    {
        HideAllFrame();
        learn->show();
    });

    connect(learn,&Learn::ShowMenu,[=]()
    {
        HideAllFrame();
        menu->show();
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

    //DataInput <=> DataInputConfigSent
    connect(dataInput,&DataInput::ShowDataInputConfigSent,[=](const QString& textOrig,const QString& textTran,const QStringList& sentenceOrig,const QStringList& sentenceTran,const QList<QPair<int,int>>& align,const QList<QPair<int,int>>& sentenceId,const QStringList& sentenceMean)
    {
        HideAllFrame();
        dataInputConfigSent->show();
        dataInputConfigSent->Init(textOrig,textTran,sentenceOrig,sentenceTran,align,sentenceId,sentenceMean);
    });

    connect(dataInputConfigSent,&DataInputConfigSent::ConfigSentDone,[=](const QList<QPair<int,int>>& sentenceId,const QStringList& sentenceMean)
    {
        HideAllFrame();
        dataInput->show();
        dataInput->WriteSent(sentenceId,sentenceMean);
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
    dataInputConfigSent->resize(width(),height());

    tranWordMenu->resize(width(),height());
    tranWord->resize(width(),height());

    tranSentMenu->resize(width(),height());
    tranSent->resize(width(),height());

    reciteWholeMenu->resize(width(),height());
    reciteWhole->resize(width(),height());

    learn->resize(width(),height());
    learnNormal->resize(width(),height());
    learnSplit->resize(width(),height());
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
    dataInputConfigSent->hide();

    tranWordMenu->hide();
    tranWord->hide();

    tranSentMenu->hide();
    tranSent->hide();

    reciteWholeMenu->hide();
    reciteWhole->hide();

    learn->hide();
    learnNormal->hide();
    learnSplit->hide();
}
