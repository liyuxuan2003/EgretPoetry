#include "DataInputConfigSent.h"
#include "ui_DataInputConfigSent.h"

DataInputConfigSent::DataInputConfigSent(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::DataInputConfigSent)
{
    ui->setupUi(this);

    l1=new LiEasyLayout(0,width(),height(),LiEasyLayout::left,0.6f,0.1f);

    l1->AddUnit(ui->labelTitle);

    l1->AddUnit();
    l1->AddElementInUnit(ui->labelSentOrig);
    l1->AddElementInUnit(ui->lineEditSentOrig);
    l1->AddElementInUnit(ui->pushButtonSentLast);
    l1->AddElementInUnit(ui->pushButtonSentNext);
    l1->AddElementInUnit(ui->pushButtonSentMinus);
    l1->AddElementInUnit(ui->pushButtonSentPlus);

    l1->AddUnit();
    l1->AddElementInUnit(ui->labelSentTran);
    l1->AddElementInUnit(ui->lineEditSentTran);
    l1->AddElementInUnit(ui->pushButtonUseTran);

    l1->AddUnit();
    l1->AddElementInUnit(ui->pushButtonNoteLast);
    l1->AddElementInUnit(ui->pushButtonNoteNext);
    l1->AddElementInUnit(ui->pushButtonNoteInsert);
    l1->AddElementInUnit(ui->labelNowId);

    l1->AddUnit(new QWidget*[2]{ui->labelRefOrig,ui->labelRefTran},2);
    l1->AddUnit(new QWidget*[2]{ui->plainTextEditRefOrig,ui->plainTextEditRefTran},2);
    l1->AddUnit(ui->pushButtonDone);

    l1->LayoutConfigDone();
}

DataInputConfigSent::~DataInputConfigSent()
{
    delete ui;
}

void DataInputConfigSent::resizeEvent(QResizeEvent *event)
{
    l1->ResizeWithEasyLayout(width(),height());
}

void DataInputConfigSent::Init(const QString& textOrig,const QString& textTran,const QStringList& sentenceOrig,const QStringList& sentenceTran,const QList<QPair<int,int>>& align,const QList<QPair<int,int>>& sentenceId,const QStringList& sentenceMean)
{
    ui->plainTextEditRefOrig->setPlainText(textOrig);
    ui->plainTextEditRefTran->setPlainText(textTran);

    this->sentenceOrig=sentenceOrig;
    this->sentenceTran=sentenceTran;

    this->align=align;

    this->sentenceId=sentenceId;
    this->sentenceMean=sentenceMean;

    nowNoteId=0;

    if(sentenceId.size()==0)
    {
        this->sentenceId.append(QPair<int,int>(0,0));
        this->sentenceMean.append("");
    }

    GenerateSent();
}

void DataInputConfigSent::GenerateSent()
{
    ui->labelNowId->setText("当前重点句编号："+QString::number(nowNoteId+1)+"/"+QString::number(sentenceId.size()));

    QString temp="";
    for(int i=sentenceId[nowNoteId].first;i<=sentenceId[nowNoteId].second;i++)
        temp+=sentenceOrig[i];

    ui->lineEditSentOrig->setText(temp);
    ui->lineEditSentTran->setText(sentenceMean[nowNoteId]);

    //Is the orig sentence left side touch the start of text?
    if(sentenceId[nowNoteId].first==0)
        DisabledButton(ui->pushButtonSentLast);
    else
        EnabledButton(ui->pushButtonSentLast);

    //Is the orig sentence right side touch the end of text?
    if(sentenceId[nowNoteId].second==sentenceOrig.size()-1)
        DisabledButton(ui->pushButtonSentNext);
    else
        EnabledButton(ui->pushButtonSentNext);

    //Is the orig sentence can not be shorter?
    if(sentenceId[nowNoteId].second-sentenceId[nowNoteId].first==0)
        DisabledButton(ui->pushButtonSentMinus);
    else
        EnabledButton(ui->pushButtonSentMinus);

    //Is the orig sentence can not be longer?
    if(sentenceId[nowNoteId].second==sentenceOrig.size()-1)
        DisabledButton(ui->pushButtonSentPlus);
    else
        EnabledButton(ui->pushButtonSentPlus);

    //Is it the first note?
    if(nowNoteId==0)
        DisabledButton(ui->pushButtonNoteLast);
    else
        EnabledButton(ui->pushButtonNoteLast);

    //Is it the last note?
    if(nowNoteId==sentenceId.size()-1)
        DisabledButton(ui->pushButtonNoteNext);
    else
        EnabledButton(ui->pushButtonNoteNext);
}

void DataInputConfigSent::EnabledButton(QPushButton* button)
{
    button->setEnabled(true);
    button->setStyleSheet("background-color:rgb(117, 133, 67); color:rgb(255,255,255)");
}

void DataInputConfigSent::DisabledButton(QPushButton* button)
{
    button->setDisabled(true);
    button->setStyleSheet("background-color:rgb(106,106,106); color:rgb(255,255,255);");
}

void DataInputConfigSent::on_pushButtonSentLast_clicked()
{
    sentenceMean[nowNoteId]=ui->lineEditSentTran->text();
    sentenceId[nowNoteId].first--;
    sentenceId[nowNoteId].second--;
    GenerateSent();
}

void DataInputConfigSent::on_pushButtonSentNext_clicked()
{
    sentenceMean[nowNoteId]=ui->lineEditSentTran->text();
    sentenceId[nowNoteId].first++;
    sentenceId[nowNoteId].second++;
    GenerateSent();
}

void DataInputConfigSent::on_pushButtonSentMinus_clicked()
{
    sentenceMean[nowNoteId]=ui->lineEditSentTran->text();
    sentenceId[nowNoteId].second--;
    GenerateSent();
}

void DataInputConfigSent::on_pushButtonSentPlus_clicked()
{
    sentenceMean[nowNoteId]=ui->lineEditSentTran->text();
    sentenceId[nowNoteId].second++;
    GenerateSent();
}

void DataInputConfigSent::on_pushButtonUseTran_clicked()
{
    QString temp="";
    for(int i=sentenceId[nowNoteId].first;i<=sentenceId[nowNoteId].second;i++)
        for(int j=align[i].first;j<=align[i].second;j++)
            temp+=sentenceTran[j];
    ui->lineEditSentTran->setText(temp);
}

void DataInputConfigSent::on_pushButtonNoteLast_clicked()
{
    sentenceMean[nowNoteId]=ui->lineEditSentTran->text();
    nowNoteId--;
    GenerateSent();
}

void DataInputConfigSent::on_pushButtonNoteNext_clicked()
{
    sentenceMean[nowNoteId]=ui->lineEditSentTran->text();
    nowNoteId++;
    GenerateSent();
}

void DataInputConfigSent::on_pushButtonNoteInsert_clicked()
{
    sentenceMean[nowNoteId]=ui->lineEditSentTran->text();
    nowNoteId++;
    if(sentenceId[nowNoteId-1].second<sentenceTran.size()-1)
        sentenceId.insert(nowNoteId,QPair<int,int>(sentenceId[nowNoteId-1].second+1,sentenceId[nowNoteId-1].second+1));
    else
        sentenceId.insert(nowNoteId,QPair<int,int>(sentenceId[nowNoteId-1].second+0,sentenceId[nowNoteId-1].second+0));
    sentenceMean.insert(nowNoteId,"");
    GenerateSent();
}

void DataInputConfigSent::on_pushButtonDone_clicked()
{
    sentenceMean[nowNoteId]=ui->lineEditSentTran->text();
    emit(ConfigSentDone(sentenceId,sentenceMean));
}
