#include "DataInput.h"
#include "ui_DataInput.h"

DataInput::DataInput(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::DataInput)
{
    ui->setupUi(this);

    l1=new LiEasyLayout(0,width(),height(),LiEasyLayout::left,0.6f,0.1f);
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

    sentenceOrig.clear();
    sentenceTran.clear();

    partOrig.clear();
    partTran.clear();

    splitMode=SplitMode::Section;

    ui->pushButtonAlign->setDisabled(true);
    ui->pushButtonSent->setDisabled(true);
    ui->pushButtonWord->setDisabled(true);

    ui->pushButtonAlign->setStyleSheet("background-color:rgb(106,106,106); color:rgb(255,255,255);");
    ui->pushButtonSent->setStyleSheet("background-color:rgb(106,106,106); color:rgb(255,255,255);");
    ui->pushButtonWord->setStyleSheet("background-color:rgb(106,106,106); color:rgb(255,255,255);");
}

void DataInput::on_pushButtonExit_clicked()
{
    emit(ShowMenu());
}

QString DataInput::GenerateTextOrig()
{
    QString textOrig="";
    QString splitString;

    if(splitMode==SplitMode::LineBreak)
        splitString="\n";
    if(splitMode==SplitMode::Section)
        splitString="\n\n";

    int splitCounter=0;
    for(int i=0;i<sentenceOrig.size();i++)
    {
        textOrig+=sentenceOrig[i];
        if(partOrig[splitCounter].second==i && splitCounter!=partOrig.size())
        {
            splitCounter++;
            textOrig+=splitString;
        }
    }

    return textOrig;
}

QString DataInput::GenerateTextTran()
{
    QString textTran="";
    QString splitString;

    if(splitMode==SplitMode::LineBreak)
        splitString="\n";
    if(splitMode==SplitMode::Section)
        splitString="\n\n";

    int splitCounter=0;
    for(int i=0;i<sentenceTran.size();i++)
    {
        textTran+=sentenceTran[i];
        if(partTran[splitCounter].second==i && splitCounter!=partTran.size())
        {
            splitCounter++;
            textTran+=splitString;
        }
    }

    return textTran;
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
    emit(ShowDataInputConfigSource(GenerateTextOrig(),GenerateTextTran()));
}

void DataInput::WriteSource(const QStringList& sentenceOrig,const QStringList& sentenceTran,const QList<QPair<int,int>>& partOrig,const QList<QPair<int,int>>& partTran,SplitMode::Mode splitMode)
{
    this->sentenceOrig=sentenceOrig;
    this->sentenceTran=sentenceTran;
    this->partOrig=partOrig;
    this->partTran=partTran;
    this->splitMode=splitMode;

    if(sentenceOrig.size()!=0)
    {
        ui->pushButtonAlign->setEnabled(true);
        ui->pushButtonAlign->setStyleSheet("background-color:rgb(117, 133, 67); color:rgb(255,255,255);");
    }
}

void DataInput::on_pushButtonAlign_clicked()
{
    emit(ShowDataInputConfigAlign(GenerateTextOrig(),GenerateTextTran(),partOrig,partTran,align));
}
