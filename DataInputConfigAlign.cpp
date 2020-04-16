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

void DataInputConfigAlign::Init(const QString& textOrig,const QString& textTran,const QStringList& sentenceOrig,const QStringList& sentenceTran,const QList<QPair<int, int>>& partOrig,const QList<QPair<int, int>>& partTran,const QList<QPair<int, int>>& align)
{
    ui->plainTextEditRefOrig->setPlainText(textOrig);
    ui->plainTextEditRefTran->setPlainText(textTran);

    this->sentenceOrig=sentenceOrig;
    this->sentenceTran=sentenceTran;

    this->partOrig=partOrig;
    this->partTran=partTran;

    alignPrefix.clear();
    for(int i=0;i<align.size();i++)
        alignPrefix.append(align[i].second-align[i].first+1);

    nowIdOrig=0;
    nowIdTran=0;

    if(alignPrefix.size()==0)
        alignPrefix.append(1);

    GenerateOperate();
}

void DataInputConfigAlign::EnabledButton(QPushButton* button)
{
    button->setEnabled(true);
    button->setStyleSheet("background-color:rgb(117, 133, 67); color:rgb(255,255,255)");
}

void DataInputConfigAlign::DisabledButton(QPushButton* button)
{
    button->setDisabled(true);
    button->setStyleSheet("background-color:rgb(106,106,106); color:rgb(255,255,255);");
}

int DataInputConfigAlign::GetPartId(const QList<QPair<int,int>>& part,int sentenceId)
{
    int partId=0;

    for(int i=0;i<part.size();i++)
    {
        if(sentenceId>=part[i].first && sentenceId<=part[i].second)
        {
            partId=i;
            break;
        }
    }

    return partId;
}

void DataInputConfigAlign::GenerateOperate()
{
    QString operateOrig="";
    QString operateTran="";

    operateOrig=sentenceOrig[nowIdOrig];
    for(int i=0;i<alignPrefix[nowIdOrig];i++)
        operateTran+=sentenceTran[nowIdTran+i];

    ui->plainTextEditOperateOrig->setPlainText(operateOrig);
    ui->plainTextEditOperateTran->setPlainText(operateTran);

    //Is is it the final one?
    if(nowIdOrig==sentenceOrig.size()-1)
        DisabledButton(ui->pushButtonNext);
    else
        EnabledButton(ui->pushButtonNext);

    //Is is it the begin one?
    if(nowIdOrig==0)
        DisabledButton(ui->pushButtonLast);
    else
        EnabledButton(ui->pushButtonLast);

    int nowTranEndId=nowIdTran+alignPrefix[nowIdOrig]-1;
    int nextTranEndId=nowIdTran+alignPrefix[nowIdOrig];

    //Is the plus button should be disabled?
    if(GetPartId(partTran,nowTranEndId)!=GetPartId(partTran,nextTranEndId))
        DisabledButton(ui->pushButtonPlus);
    else
        EnabledButton(ui->pushButtonPlus);

    //Is the minus button should be disabled?
    if(alignPrefix[nowIdOrig]-1<1)
        DisabledButton(ui->pushButtonMinus);
    else
        EnabledButton(ui->pushButtonMinus);
}

void DataInputConfigAlign::on_pushButtonMinus_clicked()
{
    alignPrefix[nowIdOrig]--;
    GenerateOperate();
}

void DataInputConfigAlign::on_pushButtonPlus_clicked()
{
    alignPrefix[nowIdOrig]++;
    GenerateOperate();
}

void DataInputConfigAlign::on_pushButtonLast_clicked()
{
    nowIdOrig-=1;
    nowIdTran-=alignPrefix[nowIdOrig];
    GenerateOperate();
}

void DataInputConfigAlign::on_pushButtonNext_clicked()
{
    nowIdTran+=alignPrefix[nowIdOrig];
    nowIdOrig+=1;
    if(nowIdOrig==alignPrefix.size())
    {
        if(GetPartId(partOrig,nowIdOrig)==GetPartId(partTran,nowIdTran))
            alignPrefix.append(1);
        else
            alignPrefix.append(0);
    }
    else if(alignPrefix[nowIdOrig]==0)
    {
        if(GetPartId(partOrig,nowIdOrig)==GetPartId(partTran,nowIdTran))
            alignPrefix[nowIdOrig]=1;
    }
    GenerateOperate();
}

void DataInputConfigAlign::on_pushButtonDone_clicked()
{
    QList<QPair<int,int>> align;
    align.append(QPair<int,int>(0,alignPrefix[0]-1));
    for(int i=1;i<alignPrefix.size();i++)
        align.append(QPair<int,int>(align[i-1].second+1,align[i-1].second+alignPrefix[i]));
    emit(ConfigAlignDone(align));
}
