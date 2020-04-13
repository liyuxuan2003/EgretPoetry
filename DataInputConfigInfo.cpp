#include "DataInputConfigInfo.h"
#include "ui_DataInputConfigInfo.h"

DataInputConfigInfo::DataInputConfigInfo(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::DataInputConfigInfo)
{
    ui->setupUi(this);

    l1=new LiEasyLayout(0,width(),height(),LiEasyLayout::left,0.6f,0.1f);

    l1->AddUnit(ui->labelTitle);
    l1->AddUnit(new QWidget*[2]{ui->labelArticleTitle,ui->lineEditArticleTitle},2);
    l1->AddUnit(new QWidget*[2]{ui->labelArticleAuthor,ui->lineEditArticleAuthor},2);
    l1->AddUnit(new QWidget*[2]{ui->labelArticleType,ui->comboBoxArticleType},2);
    l1->AddUnit(ui->pushButtonDone);

    l1->LayoutConfigDone();
}

DataInputConfigInfo::~DataInputConfigInfo()
{
    delete ui;
}

void DataInputConfigInfo::resizeEvent(QResizeEvent *event)
{
    l1->ResizeWithEasyLayout(width(),height());
}

void DataInputConfigInfo::Init(const QString& title,const QString& author,const QString& type)
{
    this->title=title;
    this->author=author;
    this->type=type;

    ui->lineEditArticleTitle->setText(this->title);
    ui->lineEditArticleAuthor->setText(this->author);
    ui->comboBoxArticleType->setCurrentText(this->type);
}

void DataInputConfigInfo::on_pushButtonDone_clicked()
{
    title=ui->lineEditArticleTitle->text();
    author=ui->lineEditArticleAuthor->text();
    type=ui->comboBoxArticleType->currentText();
    emit(ConfigInfoDone(title,author,type));
}
