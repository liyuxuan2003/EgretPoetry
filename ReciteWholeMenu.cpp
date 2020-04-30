#include "ReciteWholeMenu.h"
#include "ui_ReciteWholeMenu.h"

ReciteWholeMenu::ReciteWholeMenu(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::ReciteWholeMenu)
{
    ui->setupUi(this);

    l1=new LiEasyLayout(0,width(),height(),LiEasyLayout::left,0.6f,0.1f);
    l2=new LiFixedToLayout();

    l1->AddUnit(ui->labelTitle);
    l1->AddUnit(new QWidget*[3]{ui->labelTest,ui->pushButtonTest,ui->labelTestInfo},3);
    l1->AddUnit(new QWidget*[3]{ui->labelPunctuation,ui->radioButtonManual,ui->radioButtonAuto},3);
    l1->AddUnit(ui->pushButtonStart);
    l1->AddUnit(ui->labelFailed);

    l1->LayoutConfigDone();

    l2->AddUnit(ui->pushButtonExit,width(),height(),LiFixedCorner::RightBottom);
}

ReciteWholeMenu::~ReciteWholeMenu()
{
    delete ui;
}

void ReciteWholeMenu::resizeEvent(QResizeEvent *event)
{
    l1->ResizeWithEasyLayout(width(),height());
    l2->ResizeWithFixedToLayout(width(),height());
}

void ReciteWholeMenu::Init()
{
    ui->radioButtonManual->click();
    ui->labelTestInfo->setText("未选择测试诗文库！");
    ui->labelFailed->hide();
    sourcePath.clear();
}

void ReciteWholeMenu::on_pushButtonTest_clicked()
{
    QString file=QFileDialog::getOpenFileName(this,"请选择测试诗文库","D:/","JSON File (*.json)");
    if(file.length()==0)
        return;
    sourcePath=file;
    ui->labelTestInfo->setText("已选择测试诗文库！");
}

void ReciteWholeMenu::on_pushButtonStart_clicked()
{
    if(sourcePath.size()==0)
    {
        ui->labelFailed->setText("请选择测试诗文库！");
        ui->labelFailed->show();
        return;
    }

    ReadPoetryData rpd(sourcePath);
    if(rpd.IsError()==true)
    {
        ui->labelFailed->setText("选中的诗文库中存在损坏文件！");
        ui->labelFailed->show();
        return;
    }

    bool isManual=true;
    if(ui->radioButtonManual->isChecked()==true)
        isManual=true;
    if(ui->radioButtonAuto->isChecked()==true)
        isManual=false;

    emit(ShowReciteWhole(sourcePath,isManual));
}

void ReciteWholeMenu::on_pushButtonExit_clicked()
{
    emit(ShowMenu());
}

