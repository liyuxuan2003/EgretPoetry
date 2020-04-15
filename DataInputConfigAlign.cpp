#include "DataInputConfigAlign.h"
#include "ui_DataInputConfigAlign.h"

DataInputConfigAlign::DataInputConfigAlign(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::DataInputConfigAlign)
{
    ui->setupUi(this);

    l1=new LiEasyLayout(0,width(),height(),LiEasyLayout::left,0.6f,0.1f);

    l1->AddUnit(ui->labelTitle);
    l1->AddUnit(ui->labelOperateOrig);
    l1->AddUnit(ui->plainTextEditOperateOrig);
    l1->AddUnit(ui->labelOperateTran);
    l1->AddUnit(ui->plainTextEditOperateTran);
    l1->AddUnit(new QWidget*[4]{ui->pushButtonMinus,ui->pushButtonPlus,ui->pushButtonLast,ui->pushButtonNext},4);
    l1->AddUnit(new QWidget*[2]{ui->labelRefOrig,ui->labelRefTran},2);
    l1->AddUnit(new QWidget*[2]{ui->plainTextEditRefOrig,ui->plainTextEditRefTran},2);
    l1->AddUnit(ui->pushButtonDone);

    l1->LayoutConfigDone();
}

DataInputConfigAlign::~DataInputConfigAlign()
{
    delete ui;
}

void DataInputConfigAlign::resizeEvent(QResizeEvent *event)
{
    l1->ResizeWithEasyLayout(width(),height());
}

void DataInputConfigAlign::Init(const QString& textOrig,const QString& textTran,const QList<QPair<int, int>>& partOrig,const QList<QPair<int, int>>& partTran,const QList<QPair<int, int>>& align)
{

}
