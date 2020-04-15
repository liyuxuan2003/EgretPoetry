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

void DataInputConfigSource::Init(const QString& textOrig,const QString& textTran)
{
    ui->plainTextEditOriginal->setPlainText(textOrig);
    ui->plainTextEditTranslate->setPlainText(textTran);

    ui->labelFailed->hide();
}

void DataInputConfigSource::DataProcess(const QString& text,QStringList& sentence,QList<int>& lineBreak,QList<int>& section)
{
    int startFrom=0;

    for(int i=0;i<text.size();i++)
    {
        QString nowHandle=text.mid(i,1);

        if(nowHandle=="\n")
        {
            startFrom++;
            if(text.mid(i-1,1)!="\n" && text.mid(i+1,1)!="\n")
            {
                lineBreak.append(sentence.size()-1);
                continue;
            }
            else if(text.mid(i+1,1)=="\n")  //It is the first \n of section.
            {
                section.append(sentence.size()-1);
                continue;
            }
            else if(text.mid(i-1,1)=="\n")  //It is the second \n of section.
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
            sentence.append(text.mid(startFrom,i-startFrom+1));
            startFrom=i+1;
        }
    }
}

void DataInputConfigSource::SetErrorText(const QString& errorText,QString& errorTextVar)
{
    if(errorTextVar=="")
        errorTextVar=errorText;
}

void DataInputConfigSource::on_pushButtonDone_clicked()
{
    QString textOrig;
    QString textTran;

    QStringList sentenceOrig;
    QStringList sentenceTran;

    QList<QPair<int,int>> partOrig;
    QList<QPair<int,int>> partTran;

    SplitMode::Mode splitMode;

    QList<int> splitOrig[2];    //id=0 => lineBreak
    QList<int> splitTran[2];    //id=1 => section

    textOrig=ui->plainTextEditOriginal->toPlainText();
    textTran=ui->plainTextEditTranslate->toPlainText();

    while(textOrig.right(1)=="\n")
        textOrig.chop(1);

    while(textTran.right(1)=="\n")
        textTran.chop(1);

    splitMode=SplitMode::Section;

    DataProcess(textOrig,sentenceOrig,splitOrig[0],splitOrig[1]);
    DataProcess(textTran,sentenceTran,splitTran[0],splitTran[1]);

    QString errorTextVar="";

    if(splitOrig[0].size()!=0 && splitOrig[1].size()!=0 && splitTran[0].size()!=0 && splitTran[1].size()!=0)
        SetErrorText("原文和译文中出现了分句和分段的混用，这是不被允许的！",errorTextVar);

    if(splitOrig[0].size()!=0 && splitOrig[1].size()!=0)
        SetErrorText("原文中出现了分句和分段的混用，这是不被允许的！",errorTextVar);

    if(splitTran[0].size()!=0 && splitTran[1].size()!=0)
        SetErrorText("译文中出现了分句和分段的混用，这是不被允许的！",errorTextVar);

    int modeOrig=-1;
    int modeTran=-1;

    if(splitOrig[0].size()!=0)
        modeOrig=0;

    if(splitOrig[1].size()!=0)
        modeOrig=1;

    if(splitTran[0].size()!=0)
        modeTran=0;

    if(splitTran[1].size()!=0)
        modeTran=1;

    if(modeOrig==-1 && modeTran==-1)
    {
        modeOrig=1;
        modeTran=1;
    }
    else if(modeOrig==-1)
        modeOrig=modeTran;
    else if(modeTran==-1)
        modeTran=modeOrig;

    int mode=-1;
    if(modeOrig!=modeTran && mode)
        SetErrorText("原文和译文间使用的划分模式不一致，这是不被允许的！",errorTextVar);
    else
        mode=modeOrig;

    if(splitOrig[mode].size()!=splitTran[mode].size())
    {
        if(mode==0)
            SetErrorText("原文和译文间的分句数不同，请仔细检查！",errorTextVar);
        if(mode==1)
            SetErrorText("原文和译文间的分段数不同，请仔细检查！",errorTextVar);
    }

    if(errorTextVar!="")
    {
        ui->labelFailed->setText(errorTextVar);
        ui->labelFailed->show();
    }
    else
    {
        int splitAmount=splitOrig[mode].size();

        for(int i=0;i<splitAmount;i++)
        {
            partOrig.append(QPair<int,int>(0,splitOrig[mode][i]));
            partTran.append(QPair<int,int>(0,splitTran[mode][i]));
        }
        partOrig.append(QPair<int,int>(0,sentenceOrig.size()-1));
        partTran.append(QPair<int,int>(0,sentenceTran.size()-1));

        for(int i=1;i<=splitAmount;i++)
        {
            partOrig[i].first=partOrig[i-1].second+1;
            partTran[i].first=partTran[i-1].second+1;
        }

        if(mode==0)
            splitMode=SplitMode::LineBreak;
        if(mode==1)
            splitMode=SplitMode::Section;

        emit(ConfigSourceDone(sentenceOrig,sentenceTran,partOrig,partTran,splitMode));
    }
}




