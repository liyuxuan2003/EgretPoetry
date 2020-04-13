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

    original="";
    translate="";

    originalList.clear();
    translateList.clear();

    sectionOrig.clear();
    sectionTran.clear();
    lineBreak.clear();

    isSourceDone=false;
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

    isSourceDone=true;

    int startFrom;

    startFrom=0;
    for(int i=0;i<original.size();i++)
    {
        QString nowHandle=original.mid(i,1);

        if(nowHandle=="\n")
        {
            if(original.mid(i-1,1)!="\n" && original.mid(i+1,1)!="\n")
            {
                lineBreak.append(originalList.size());
                continue;
            }
            else if(original.mid(i+1,1)=="\n")  //It is the first \n of section.
            {
                sectionOrig.append(originalList.size());
                continue;
            }
            else if(original.mid(i-1,1)=="\n")  //It is the second \n of section.
            {
                continue;
            }
        }

        bool isSymbol=false;
        for(int j=0;j<symbolNum;j++)
        {
            if(nowHandle==symbol[j])
            {
                isSymbol=true;
                break;
            }
        }
        if(isSymbol==true)
        {
            originalList.append(original.mid(startFrom,i-startFrom+1));
            startFrom=i+1;
        }
    }

    startFrom=0;
    for(int i=0;i<translate.size();i++)
    {
        QString nowHandle=translate.mid(i,1);

        if(nowHandle=="\n")
        {
            if(translate.mid(i+1,1)=="\n")   //Judge it is the first or second \n of section.
                sectionTran.append(translateList.size());
            continue;
        }

        bool isSymbol=false;
        for(int j=0;j<symbolNum;j++)
        {
            if(nowHandle==symbol[j])
            {
                isSymbol=true;
                break;
            }
        }
        if(isSymbol==true)
        {
            translateList.append(translate.mid(startFrom,i-startFrom+1));
            startFrom=i+1;
        }
    }

}
