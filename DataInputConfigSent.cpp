#include "DataInputConfigSent.h"
#include "ui_DataInputConfigSent.h"

DataInputConfigSent::DataInputConfigSent(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::DataInputConfigSent)
{
    ui->setupUi(this);

    l1=new LiEasyLayout(0,width(),height(),LiEasyLayout::left,0.6f,0.1f);

    l1->AddUnit(ui->labelTitle);

    l1->AddUnit();
    l1->AddElementInUnit(ui->labelSentOrig);
    l1->AddElementInUnit(ui->lineEditSentOrig);
    l1->AddElementInUnit(ui->pushButtonSentLast);
    l1->AddElementInUnit(ui->pushButtonSentNext);
    l1->AddElementInUnit(ui->pushButtonSentMinus);
    l1->AddElementInUnit(ui->pushButtonSentPlus);

    l1->AddUnit();
    l1->AddElementInUnit(ui->labelSentTran);
    l1->AddElementInUnit(ui->lineEditSentTran);
    l1->AddElementInUnit(ui->pushButtonUseTran);

    l1->AddUnit();
    l1->AddElementInUnit(ui->pushButtonNoteLast);
    l1->AddElementInUnit(ui->pushButtonNoteNext);
    l1->AddElementInUnit(ui->pushButtonNoteInsert);
    l1->AddElementInUnit(ui->labelNowId);

    l1->AddUnit(new QWidget*[2]{ui->labelRefOrig,ui->labelRefTran},2);
    l1->AddUnit(new QWidget*[2]{ui->plainTextEditRefOrig,ui->plainTextEditRefTran},2);
    l1->AddUnit(ui->pushButtonDone);

    l1->LayoutConfigDone();
}

DataInputConfigSent::~DataInputConfigSent()
{
    delete ui;
}

void DataInputConfigSent::resizeEvent(QResizeEvent *event)
{
    l1->ResizeWithEasyLayout(width(),height());
}
