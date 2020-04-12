#include "DataInput.h"
#include "ui_DataInput.h"

DataInput::DataInput(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::DataInput)
{
    ui->setupUi(this);

    l1=new LiEasyLayout(0,width(),height(),LiEasyLayout::left,0.6f);
    l2=new LiFixedToLayout();

    l1->AddUnit(ui->labelTitle);
    l1->AddUnit(new QWidget*[2]{ui->labelInfo,ui->pushButtonInfo},2);
    l1->AddUnit(new QWidget*[2]{ui->labelSource,ui->pushButtonSource},2);
    l1->AddUnit(new QWidget*[2]{ui->labelAlign,ui->pushButtonAlign},2);
    l1->AddUnit(new QWidget*[2]{ui->labelWord,ui->pushButtonWord},2);
    l1->AddUnit(new QWidget*[2]{ui->labelSent,ui->pushButtonSent},2);
    l1->AddUnit(new QWidget*[2]{ui->pushButtonWriteData,ui->labelWriteData},2);
    l1->AddUnit(ui->labelWarning1);
    l1->AddUnit(ui->labelWarning2);

    l1->LayoutConfigDone();

    l2->AddUnit(ui->pushButtonExit,width(),height(),LiFixedCorner::RightBottom);
}

DataInput::~DataInput()
{
    delete ui;
}

void DataInput::resizeEvent(QResizeEvent *event)
{
    l1->ResizeWithEasyLayout(width(),height());
    l2->ResizeWithFixedToLayout(width(),height());
}

void DataInput::Init(const QString &path,const QString &name)
{
    this->path=path;
    this->name=name;

    title="";
    author="";
    type="文";

    original="";
    translate="";
}

void DataInput::on_pushButtonExit_clicked()
{
    emit(ShowMenu());
}

void DataInput::on_pushButtonInfo_clicked()
{
    emit(ShowDataInputConfigInfo(title,author,type));
}

void DataInput::WrtieInfo(const QString& title,const QString& author,const QString& type)
{
    this->title=title;
    this->author=author;
    this->type=type;
}

void DataInput::on_pushButtonSource_clicked()
{
    emit(ShowDataInputConfigSource(original,translate));
}

void DataInput::WriteSource(const QString& original,const QString& translate)
{
    this->original=original;
    this->translate=translate;
}
