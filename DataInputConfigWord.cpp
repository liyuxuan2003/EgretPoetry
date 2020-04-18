#include "DataInputConfigWord.h"
#include "ui_DataInputConfigWord.h"

DataInputConfigWord::DataInputConfigWord(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::DataInputConfigWord)
{
    ui->setupUi(this);

    l1=new LiEasyLayout(0,width(),height(),LiEasyLayout::left,0.6f,0.1f);

    l1->AddUnit(ui->labelTitle);

    l1->AddUnit();
    l1->AddElementInUnit(ui->labelSent);
    l1->AddElementInUnit(ui->lineEditSent);
    l1->AddElementInUnit(ui->pushButtonSentLast);
    l1->AddElementInUnit(ui->pushButtonSentNext);

    l1->AddUnit();
    l1->AddElementInUnit(ui->labelWord);
    l1->AddElementInUnit(ui->lineEditWord);
    l1->AddElementInUnit(ui->pushButtonWordLast);
    l1->AddElementInUnit(ui->pushButtonWordNext);
    l1->AddElementInUnit(ui->pushButtonWordMinus);
    l1->AddElementInUnit(ui->pushButtonWordPlus);

    l1->AddUnit();
    l1->AddElementInUnit(ui->labelMean);
    l1->AddElementInUnit(ui->lineEditMean);

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

DataInputConfigWord::~DataInputConfigWord()
{
    delete ui;
}

void DataInputConfigWord::resizeEvent(QResizeEvent *event)
{
    l1->ResizeWithEasyLayout(width(),height());
}

void DataInputConfigWord::Init(const QString& textOrig,const QString& textTran,const QStringList& sentenceOrig,const QList<int>& wordInSentenceId,const QList<QPair<int,int>>& wordPos,const QStringList& wordMean)
{
    ui->plainTextEditRefOrig->setPlainText(textOrig);
    ui->plainTextEditRefTran->setPlainText(textTran);

    this->sentenceOrig=sentenceOrig;
    this->wordInSentenceId=wordInSentenceId;
    this->wordPos=wordPos;
    this->wordMean=wordMean;

    nowNoteId=0;

    if(wordInSentenceId.size()==0)
    {
        this->wordInSentenceId.append(0);
        this->wordPos.append(QPair<int,int>(0,0));
        this->wordMean.append("");
    }

    GenerateWord();
}

void DataInputConfigWord::GenerateWord()
{
    ui->labelNowId->setText("当前注释编号："+QString::number(nowNoteId+1)+"/"+QString::number(wordInSentenceId.size()));
    ui->lineEditSent->setText(sentenceOrig[wordInSentenceId[nowNoteId]]);
    ui->lineEditWord->setText(sentenceOrig[wordInSentenceId[nowNoteId]].mid(wordPos[nowNoteId].first,wordPos[nowNoteId].second-wordPos[nowNoteId].first+1));
    ui->lineEditMean->setText(wordMean[nowNoteId]);

    //Is the word's left side touch the start of sentence?
    if(wordPos[nowNoteId].first==0)
        DisabledButton(ui->pushButtonWordLast);
    else
        EnabledButton(ui->pushButtonWordLast);

    //Is the word's right side touch the end of sentence?
    if(wordPos[nowNoteId].second==sentenceOrig[wordInSentenceId[nowNoteId]].size()-2)
        DisabledButton(ui->pushButtonWordNext);
    else
        EnabledButton(ui->pushButtonWordNext);

    //Is the word can not be shorter?
    if(wordPos[nowNoteId].second-wordPos[nowNoteId].first==0)
        DisabledButton(ui->pushButtonWordMinus);
    else
        EnabledButton(ui->pushButtonWordMinus);

    //Is the word can not be longer?
    if(wordPos[nowNoteId].second==sentenceOrig[wordInSentenceId[nowNoteId]].size()-2)
        DisabledButton(ui->pushButtonWordPlus);
    else
        EnabledButton(ui->pushButtonWordPlus);

    //Is it the first note?
    if(nowNoteId==0)
        DisabledButton(ui->pushButtonNoteLast);
    else
        EnabledButton(ui->pushButtonNoteLast);

    //Is it the last note?
    if(nowNoteId==wordInSentenceId.size()-1)
        DisabledButton(ui->pushButtonNoteNext);
    else
        EnabledButton(ui->pushButtonNoteNext);

    //Is it the first sentence?
    if(wordInSentenceId[nowNoteId]==0)
        DisabledButton(ui->pushButtonSentLast);
    else
        EnabledButton(ui->pushButtonSentLast);

    //Is it the last sentence?
    if(wordInSentenceId[nowNoteId]==sentenceOrig.size()-1)
        DisabledButton(ui->pushButtonSentNext);
    else
        EnabledButton(ui->pushButtonSentNext);
}

void DataInputConfigWord::EnabledButton(QPushButton* button)
{
    button->setEnabled(true);
    button->setStyleSheet("background-color:rgb(117, 133, 67); color:rgb(255,255,255)");
}

void DataInputConfigWord::DisabledButton(QPushButton* button)
{
    button->setDisabled(true);
    button->setStyleSheet("background-color:rgb(106,106,106); color:rgb(255,255,255);");
}

void DataInputConfigWord::on_pushButtonSentLast_clicked()
{
    wordMean[nowNoteId]=ui->lineEditMean->text();
    wordInSentenceId[nowNoteId]--;
    GenerateWord();
}

void DataInputConfigWord::on_pushButtonSentNext_clicked()
{
    wordMean[nowNoteId]=ui->lineEditMean->text();
    wordInSentenceId[nowNoteId]++;
    GenerateWord();
}

void DataInputConfigWord::on_pushButtonWordLast_clicked()
{
    wordMean[nowNoteId]=ui->lineEditMean->text();
    wordPos[nowNoteId].first--;
    wordPos[nowNoteId].second--;
    GenerateWord();
}

void DataInputConfigWord::on_pushButtonWordNext_clicked()
{
    wordMean[nowNoteId]=ui->lineEditMean->text();
    wordPos[nowNoteId].first++;
    wordPos[nowNoteId].second++;
    GenerateWord();
}

void DataInputConfigWord::on_pushButtonWordMinus_clicked()
{
    wordMean[nowNoteId]=ui->lineEditMean->text();
    wordPos[nowNoteId].second--;
    GenerateWord();
}

void DataInputConfigWord::on_pushButtonWordPlus_clicked()
{
    wordMean[nowNoteId]=ui->lineEditMean->text();
    wordPos[nowNoteId].second++;
    GenerateWord();
}

void DataInputConfigWord::on_pushButtonNoteLast_clicked()
{
    wordMean[nowNoteId]=ui->lineEditMean->text();
    nowNoteId--;
    GenerateWord();
}

void DataInputConfigWord::on_pushButtonNoteNext_clicked()
{
    wordMean[nowNoteId]=ui->lineEditMean->text();
    nowNoteId++;
    GenerateWord();
}

void DataInputConfigWord::on_pushButtonNoteInsert_clicked()
{
    wordMean[nowNoteId]=ui->lineEditMean->text();
    nowNoteId++;
    if(wordInSentenceId[nowNoteId-1]<sentenceOrig.size()-1)
        wordInSentenceId.insert(nowNoteId,wordInSentenceId[nowNoteId-1]+1);
    else
        wordInSentenceId.insert(nowNoteId,wordInSentenceId[nowNoteId-1]+0);
    wordPos.insert(nowNoteId,QPair<int,int>(0,0));
    wordMean.insert(nowNoteId,"");
    GenerateWord();
}

void DataInputConfigWord::on_pushButtonDone_clicked()
{
    wordMean[nowNoteId]=ui->lineEditMean->text();
    emit(ConfigWordDone(wordInSentenceId,wordPos,wordMean));
}
