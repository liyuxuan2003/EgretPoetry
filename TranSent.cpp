#include "TranSent.h"
#include "ui_TranSent.h"

TranSent::TranSent(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::TranSent)
{
    ui->setupUi(this);

    l1=new LiEasyLayout(0,width(),height(),LiEasyLayout::left,0.6f,0.1f);
    l2=new LiFixedToLayout();

    l1->AddUnit(ui->labelTitle);

    l1->AddUnit(ui->labelLocation);

    l1->AddUnit(ui->labelSentTitle);
    l1->AddUnit(ui->labelSent);

    l1->AddUnit(new QWidget*[3]{ui->labelUserAns,ui->lineEditUserAns,ui->pushButtonCheck},3);
    l1->AddUnit(new QWidget*[4]{ui->labelRightAns,ui->lineEditRightAns,ui->pushButtonAnsR,ui->pushButtonAnsW},4);

    l1->AddUnit(ui->labelReference);
    l1->AddUnit(ui->textBrowserReference);

    l1->LayoutConfigDone();

    l2->AddUnit(ui->pushButtonExit,width(),height(),LiFixedCorner::RightBottom);
}

TranSent::~TranSent()
{
    delete ui;
}

void TranSent::resizeEvent(QResizeEvent *event)
{
    l1->ResizeWithEasyLayout(width(),height());
    l2->ResizeWithFixedToLayout(width(),height());
}

void TranSent::Init(const QStringList& sourcePath,bool isRandom,QList<QPair<int,int>> needTest)
{
    this->sourcePath=sourcePath;
    this->isRandom=isRandom;
    this->needTest=needTest;
}
