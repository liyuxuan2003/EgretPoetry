#include "DataInputConfigSource.h"
#include "ui_DataInputConfigSource.h"

DataInputConfigSource::DataInputConfigSource(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::DataInputConfigSource)
{
    ui->setupUi(this);

    l1=new LiEasyLayout(0,width(),height(),LiEasyLayout::left,0.6f);

    l1->AddUnit(ui->labelTitle);
    l1->AddUnit(new QWidget*[2]{ui->labelOriginal,ui->labelTranslate},2);
    l1->AddUnit(new QWidget*[2]{ui->plainTextEditOriginal,ui->plainTextEditTranslate},2);
    l1->AddUnit(ui->pushButtonDone);

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
}

void DataInputConfigSource::on_pushButtonDone_clicked()
{
    emit(ConfigSourceDone(original,translate));
}
