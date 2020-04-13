#include "DataInputConfigSource.h"
#include "ui_DataInputConfigSource.h"

DataInputConfigSource::DataInputConfigSource(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::DataInputConfigSource)
{
    ui->setupUi(this);

    l1=new LiEasyLayout(0,width(),height(),LiEasyLayout::left,0.6f,0.1f);

    l1->AddUnit(ui->labelTitle);
    l1->AddUnit(new QWidget*[2]{ui->labelOriginal,ui->labelTranslate},2);
    l1->AddUnit(new QWidget*[2]{ui->plainTextEditOriginal,ui->plainTextEditTranslate},2);
    l1->AddUnit(ui->labelInfo);
    l1->AddUnit(new QWidget*[2]{ui->pushButtonDone,ui->labelFailed},2);

    l1->LayoutConfigDone();
}

DataInputConfigSource::~DataInputConfigSource()
{
    delete ui;
}

void DataInputConfigSource::resizeEvent(QResizeEvent *event)
{
    l1->ResizeWithEasyLayout(width(),height());
}

void DataInputConfigSource::Init(const QString& original,const QString& translate)
{
    this->original=original;
    this->translate=translate;

    ui->plainTextEditOriginal->setPlainText(original);
    ui->plainTextEditTranslate->setPlainText(translate);

    ui->labelFailed->hide();
}

void DataInputConfigSource::on_pushButtonDone_clicked()
{
    original=ui->plainTextEditOriginal->toPlainText();
    translate=ui->plainTextEditTranslate->toPlainText();

    if(original.count("\n\n")!=translate.count("\n\n"))
    {
        ui->labelFailed->setText("原文和译文的段落数量不匹配，请仔细检查！");
        ui->labelFailed->show();
    }
    else if(original.right(1)=="\n")
    {
        ui->labelFailed->setText("原文末尾存在多余换行，这是不被允许的！");
        ui->labelFailed->show();
    }
    else if(translate.right(1)=="\n")
    {
        ui->labelFailed->setText("译文末尾存在多余换行，这是不被允许的！");
        ui->labelFailed->show();
    }
    else
    {
        emit(ConfigSourceDone(original,translate));
    }
}
