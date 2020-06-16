#include "Learn.h"
#include "ui_Learn.h"

Learn::Learn(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::Learn)
{
    ui->setupUi(this);

    l1=new LiEasyLayout(0,width(),height(),LiEasyLayout::left,0.6f,0.1f);
    l2=new LiFixedToLayout();

    l1->AddUnit(ui->labelTitle);
    l1->AddUnit(ui->labelAuthor);

    l1->AddUnit(new QWidget*[2]{ui->labelNormal,ui->pushButtonNormal},2);
    l1->AddUnit(new QWidget*[2]{ui->labelSplitRead,ui->pushButtonSplitRead},2);
    l1->AddUnit(new QWidget*[2]{ui->labelWord,ui->pushButtonWord},2);
    l1->AddUnit(new QWidget*[2]{ui->labelSent,ui->pushButtonSent},2);

    l1->AddUnit(new QWidget*[2]{ui->pushButtonChoose,ui->labelChoose},2);

    l1->LayoutConfigDone();

    l2->AddUnit(ui->pushButtonExit,width(),height(),LiFixedCorner::RightBottom);
}

Learn::~Learn()
{
    delete ui;
}

void Learn::resizeEvent(QResizeEvent *event)
{
    l1->ResizeWithEasyLayout(width(),height());
    l2->ResizeWithFixedToLayout(width(),height());
}

void Learn::Init()
{
    ui->labelTitle->setText("自主学习模式");
    ui->labelAuthor->setText("未选择篇目");

    SetButtonStatus(ui->pushButtonNormal,false);
    SetButtonStatus(ui->pushButtonSplitRead,false);
    SetButtonStatus(ui->pushButtonWord,false);
    SetButtonStatus(ui->pushButtonSent,false);

    ui->labelChoose->setText("未选择篇目！");
}

void Learn::on_pushButtonChoose_clicked()
{
    QString file=QFileDialog::getOpenFileName(this,"请选择测试诗文库","D:/","JSON File (*.json)");
    if(file.length()==0)
        return;
    sourcePath=file;

    rpd=new ReadPoetryData(sourcePath);
    if(rpd->IsError()==true)
        ui->labelChoose->setText("选择的诗文库已损坏！");
    else
    {
        ui->labelChoose->setText("当前诗文库路径："+sourcePath);
        ui->labelTitle->setText(rpd->GetTitle());
        ui->labelAuthor->setText("作者："+rpd->GetAuthor());
        SetButtonStatus(ui->pushButtonNormal,true);
        SetButtonStatus(ui->pushButtonSplitRead,true);
        SetButtonStatus(ui->pushButtonWord,rpd->GetWordInSentenceId().size()!=0);
        SetButtonStatus(ui->pushButtonSent,rpd->GetSentenceId().size()!=0);
    }
}

void Learn::on_pushButtonNormal_clicked()
{
    emit(ShowLearnNormal(sourcePath));
}

void Learn::on_pushButtonSplitRead_clicked()
{
    emit(ShowLearnSplit(sourcePath,0));
}

void Learn::on_pushButtonWord_clicked()
{
    emit(ShowLearnSplit(sourcePath,1));
}

void Learn::on_pushButtonSent_clicked()
{
    emit(ShowLearnSplit(sourcePath,2));
}

void Learn::on_pushButtonExit_clicked()
{
    emit(ShowMenu());
}
