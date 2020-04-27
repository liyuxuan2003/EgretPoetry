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
    l1->AddElementInUnit(ui->pushButtonNoteDelete);
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

void DataInputConfigWord::keyPressEvent(QKeyEvent *ev)
{
    switch (ev->key())
    {
        case Qt::Key_1:
        {
            ui->pushButtonNoteLast->click();
            break;
        }
        case Qt::Key_2:
        {
            ui->pushButtonNoteNext->click();
            break;
        }
        case Qt::Key_3:
        {
            ui->pushButtonNoteInsert->click();
            break;
        }
        case Qt::Key_4:
        {
            ui->pushButtonNoteDelete->click();
            break;
        }
        case Qt::Key_Left:
        {
            ui->pushButtonWordLast->click();
            break;
        }
        case Qt::Key_Right:
        {
            ui->pushButtonWordNext->click();
            break;
        }
        case Qt::Key_Up:
        {
            ui->pushButtonWordMinus->click();
            break;
        }
        case Qt::Key_Down:
        {
            ui->pushButtonWordPlus->click();
            break;
        }
        case Qt::Key_PageUp:
        {
            ui->pushButtonSentLast->click();
            break;
        }
        case Qt::Key_PageDown:
        {
            ui->pushButtonSentNext->click();
            break;
        }
    }
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
    this->setFocus();

    ui->labelNowId->setText("当前注释编号："+QString::number(nowNoteId+1)+"/"+QString::number(wordInSentenceId.size()));
    ui->lineEditSent->setText(sentenceOrig[wordInSentenceId[nowNoteId]]);
    ui->lineEditWord->setText(sentenceOrig[wordInSentenceId[nowNoteId]].mid(wordPos[nowNoteId].first,wordPos[nowNoteId].second-wordPos[nowNoteId].first+1));
    ui->lineEditMean->setText(wordMean[nowNoteId]);

    //Is the word's left side touch the start of sentence?
    SetButtonStatus(ui->pushButtonWordLast,!(wordPos[nowNoteId].first==0));

    //Is the word's right side touch the end of sentence?
    SetButtonStatus(ui->pushButtonWordNext,!(wordPos[nowNoteId].second==sentenceOrig[wordInSentenceId[nowNoteId]].size()-2));

    //Is the word can not be shorter?
    SetButtonStatus(ui->pushButtonWordMinus,!(wordPos[nowNoteId].second-wordPos[nowNoteId].first==0));

    //Is the word can not be longer?
    SetButtonStatus(ui->pushButtonWordPlus,!(wordPos[nowNoteId].second==sentenceOrig[wordInSentenceId[nowNoteId]].size()-2));

    //Is it the first note?
    SetButtonStatus(ui->pushButtonNoteLast,!(nowNoteId==0));

    //Is it the last note?
    SetButtonStatus(ui->pushButtonNoteNext,!(nowNoteId==wordInSentenceId.size()-1));

    //Is it the only note?
    SetButtonStatus(ui->pushButtonNoteDelete,!(wordInSentenceId.size()==1));

    //Is it the first sentence?
    SetButtonStatus(ui->pushButtonSentLast,!(wordInSentenceId[nowNoteId]==0));

    //Is it the last sentence?
    SetButtonStatus(ui->pushButtonSentNext,!(wordInSentenceId[nowNoteId]==sentenceOrig.size()-1));
}

void DataInputConfigWord::on_pushButtonSentLast_clicked()
{
    wordMean[nowNoteId]=ui->lineEditMean->text();
    wordPos[nowNoteId]=QPair<int,int>(0,0);
    wordInSentenceId[nowNoteId]--;
    GenerateWord();
}

void DataInputConfigWord::on_pushButtonSentNext_clicked()
{
    wordMean[nowNoteId]=ui->lineEditMean->text();
    wordPos[nowNoteId]=QPair<int,int>(0,0);
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

void DataInputConfigWord::on_pushButtonNoteDelete_clicked()
{
    wordInSentenceId.removeAt(nowNoteId);
    wordPos.removeAt(nowNoteId);
    wordMean.removeAt(nowNoteId);
    nowNoteId=qMax(nowNoteId-1,0);
    GenerateWord();
}

void DataInputConfigWord::on_pushButtonDone_clicked()
{
    wordMean[nowNoteId]=ui->lineEditMean->text();
    emit(ConfigWordDone(wordInSentenceId,wordPos,wordMean));
}
