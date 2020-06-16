#include "LearnSplit.h"
#include "ui_LearnSplit.h"

LearnSplit::LearnSplit(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::LearnSplit)
{
    ui->setupUi(this);

    l1=new LiEasyLayout(0,width(),height(),LiEasyLayout::left,0.6f,0.1f);
    l2=new LiFixedToLayout();

    l1->AddUnit(ui->labelTitle);
    l1->AddUnit(ui->labelAuthor);

    l1->AddUnit(new QWidget*[2]{ui->labelOne,ui->labelOneText},2);
    l1->AddUnit(new QWidget*[2]{ui->labelTwo,ui->labelTwoText},2);

    l1->AddUnit(new QWidget*[4]{ui->pushButtonLast,ui->pushButtonNext,ui->pushButtonRead,ui->labelLocation},4);

    l1->AddUnit(ui->labelRef);
    l1->AddUnit(new QWidget*[2]{ui->comboBoxMode,ui->textBrowserRef},2);

    l1->LayoutConfigDone();

    l2->AddUnit(ui->pushButtonExit,width(),height(),LiFixedCorner::RightBottom);
    l2->AddUnit(ui->pushButtonHelp,width(),height(),LiFixedCorner::RightTop);

    tts=new QTextToSpeech(this);
    tts->setLocale(QLocale::Chinese);
    tts->setRate(0.0);
    tts->setPitch(1.0);
    tts->setVolume(1.0);

    help=new Help();
    help->hide();
}

LearnSplit::~LearnSplit()
{
    delete ui;
}

void LearnSplit::resizeEvent(QResizeEvent *event)
{
    l1->ResizeWithEasyLayout(width(),height());
    l2->ResizeWithFixedToLayout(width(),height());
}

void LearnSplit::keyPressEvent(QKeyEvent *ev)
{
    switch (ev->key())
    {
        case Qt::Key_Left:
        {
            ui->pushButtonLast->click();
            break;
        }
        case Qt::Key_Right:
        {
            ui->pushButtonNext->click();
            break;
        }
        case Qt::Key_3:
        {
            ui->pushButtonRead->click();
            break;
        }
    }
}

void LearnSplit::AddFontString(QString& source,int begin,int end,QString beginString,QString endString)
{
    QString targetString=source.mid(begin,end-begin+1);
    source.remove(begin,end-begin+1);

    targetString.prepend(beginString);
    targetString.append(endString);
    source.insert(begin,targetString);
}

void LearnSplit::Init(const QString& sourcePath,int mode)
{
    rpd=new ReadPoetryData(sourcePath);
    this->mode=mode;

    lastMode=0;

    nowId=0;
    switch(mode)
    {
    case 0:
        totalNum=rpd->GetSentenceOrig().size();
        ui->labelOne->setText("原文分句：");
        ui->labelTwo->setText("译文分句：");
        ui->pushButtonLast->setText("上一个分句");
        ui->pushButtonNext->setText("下一个分句");
        ui->pushButtonRead->setText("朗读分句");
        break;
    case 1:
        totalNum=rpd->GetWordInSentenceId().size();
        ui->labelOne->setText("加点字出处：");
        ui->labelTwo->setText("加点字翻译：");
        ui->pushButtonLast->setText("上一个加点字");
        ui->pushButtonNext->setText("下一个加点字");
        ui->pushButtonRead->setText("朗读加点字");
        break;
    case 2:
        totalNum=rpd->GetSentenceId().size();
        ui->labelOne->setText("重点句出处：");
        ui->labelTwo->setText("重点句翻译：");
        ui->pushButtonLast->setText("上一个重点句");
        ui->pushButtonNext->setText("下一个重点句");
        ui->pushButtonRead->setText("朗读重点句");
        break;
    }

    GeneratePage();

    ui->comboBoxMode->setCurrentIndex(0);
    ui->textBrowserRef->verticalScrollBar()->setValue(0);
}

void LearnSplit::GeneratePage()
{
    this->setFocus();
    SetButtonStatus(ui->pushButtonLast,!(nowId==0));
    SetButtonStatus(ui->pushButtonNext,!(nowId==totalNum-1));
    switch(mode)
    {
    case 0:
        GenerateSplitRead();
        break;
    case 1:
        GenerateWord();
        break;
    case 2:
        GenerateTran();
        break;
    }
}

void LearnSplit::GenerateSplitRead()
{
    ui->labelLocation->setText("当前分句位置："+QString::number(nowId+1)+"/"+QString::number(totalNum));
    ui->labelOneText->clear();
    ui->labelTwoText->clear();
    ui->labelOneText->setText(rpd->GetSentenceOrig()[nowId]);
    textToRead=rpd->GetSentenceOrig()[nowId]+"        "+rpd->GetSentenceTran()[nowId];
    for(int i=rpd->GetAlign()[nowId].first;i<=rpd->GetAlign()[nowId].second;i++)
        ui->labelTwoText->setText(ui->labelTwoText->text()+rpd->GetSentenceTran()[i]);

    QString refText="";

    if(ui->comboBoxMode->currentIndex()==0)
    {
        refText+="原文：<br>";
        refText+="------------------------------------------------<br>";
        for(int i=0;i<rpd->GetPartOrig().size();i++)
        {
            for(int j=rpd->GetPartOrig()[i].first;j<=rpd->GetPartOrig()[i].second;j++)
            {
                QString tempText=rpd->GetSentenceOrig()[j];
                if(j==nowId)
                    AddFontString(tempText,0,tempText.length(),"<b><font color=\"#FF645A\">","</font></b>");
                refText+=tempText;
            }
            if(i!=rpd->GetPartOrig().size()-1)
            {
                if(rpd->GetSplitMode()==SplitMode::LineBreak)
                    refText+="<br>";
                if(rpd->GetSplitMode()==SplitMode::Section)
                    refText+="<br><br>";
            }
        }
        refText+="<br><br><br>";

        refText+="译文：<br>";
        refText+="------------------------------------------------<br>";
        for(int i=0;i<rpd->GetPartTran().size();i++)
        {
            for(int j=rpd->GetPartTran()[i].first;j<=rpd->GetPartTran()[i].second;j++)
            {
                QString tempText=rpd->GetSentenceTran()[j];
                if(j>=rpd->GetAlign()[nowId].first && j<=rpd->GetAlign()[nowId].second)
                    AddFontString(tempText,0,tempText.length(),"<b><font color=\"#FF645A\">","</font></b>");
                refText+=tempText;
            }
            if(i!=rpd->GetPartTran().size()-1)
            {
                if(rpd->GetSplitMode()==SplitMode::LineBreak)
                    refText+="<br>";
                if(rpd->GetSplitMode()==SplitMode::Section)
                    refText+="<br><br>";
            }
        }
        refText+="<br><br><br>";
    }

    if(ui->comboBoxMode->currentIndex()==1)
    {
        refText+="------------------------------------------------";
        refText+="<br><br>";
        for(int i=0;i<rpd->GetPartOrig().size();i++)
        {
            for(int j=rpd->GetPartOrig()[i].first;j<=rpd->GetPartOrig()[i].second;j++)
            {
                QString tempText=rpd->GetSentenceOrig()[j];
                if(j==nowId)
                    AddFontString(tempText,0,tempText.length(),"<b><font color=\"#FF645A\">","</font></b>");
                refText+=tempText;
            }
            refText+="<br><br>";
            for(int j=rpd->GetPartTran()[i].first;j<=rpd->GetPartTran()[i].second;j++)
            {
                QString tempText=rpd->GetSentenceTran()[j];
                if(j>=rpd->GetAlign()[nowId].first && j<=rpd->GetAlign()[nowId].second)
                    AddFontString(tempText,0,tempText.length(),"<b><font color=\"#FF645A\">","</font></b>");
                refText+=tempText;
            }
            refText+="<br><br>";
            refText+="------------------------------------------------";
            refText+="<br><br>";
        }
    }

    if(ui->comboBoxMode->currentIndex()==2)
    {
        for(int i=0;i<rpd->GetSentenceOrig().size();i++)
        {
            QString tempText1=rpd->GetSentenceOrig()[i];
            if(i==nowId)
                AddFontString(tempText1,0,tempText1.length(),"<b><font color=\"#FF645A\">","</font></b>");
            refText+=tempText1;
            refText+="<br>";

            QString tempText2="";
            for(int j=rpd->GetAlign()[i].first;j<=rpd->GetAlign()[i].second;j++)
                tempText2+=rpd->GetSentenceTran()[j];
            if(i==nowId)
                AddFontString(tempText2,0,tempText2.length(),"<b><font color=\"#FF645A\">","</font></b>");
            refText+=tempText2;
            refText+="<br><br>";
        }
    }

    int nowLocation=ui->textBrowserRef->verticalScrollBar()->value();
    ui->textBrowserRef->setText(refText);
    if(lastMode==ui->comboBoxMode->currentIndex())
        ui->textBrowserRef->verticalScrollBar()->setValue(nowLocation);
    else
        ui->textBrowserRef->verticalScrollBar()->setValue(0);
}

void LearnSplit::GenerateWord()
{
    ui->labelLocation->setText("当前加点字位置："+QString::number(nowId+1)+"/"+QString::number(totalNum));
    ui->labelOneText->clear();
    ui->labelTwoText->clear();

    QString labelOneText=rpd->GetSentenceOrig()[rpd->GetWordInSentenceId()[nowId]];
    AddFontString(labelOneText,rpd->GetWordPos()[nowId].first,rpd->GetWordPos()[nowId].second,"<b><font color=\"#FF645A\">","</font></b>");

    ui->labelOneText->setText(labelOneText);
    ui->labelTwoText->setText(rpd->GetWordMean()[nowId]);

    textToRead.clear();
    textToRead.append(rpd->GetSentenceOrig()[rpd->GetWordInSentenceId()[nowId]]);
    textToRead.append("    ");
    textToRead.append(rpd->GetSentenceOrig()[rpd->GetWordInSentenceId()[nowId]].mid(rpd->GetWordPos()[nowId].first,rpd->GetWordPos()[nowId].second-rpd->GetWordPos()[nowId].first+1)+"。");
    textToRead.append("    ");
    textToRead.append(rpd->GetWordMean()[nowId]);

    QString refText="";

    if(ui->comboBoxMode->currentIndex()==0)
    {
        refText+="原文：<br>";
        refText+="------------------------------------------------<br>";
        for(int i=0;i<rpd->GetPartOrig().size();i++)
        {
            for(int j=rpd->GetPartOrig()[i].first;j<=rpd->GetPartOrig()[i].second;j++)
            {
                QString tempText=rpd->GetSentenceOrig()[j];
                if(j==rpd->GetWordInSentenceId()[nowId])
                    AddFontString(tempText,rpd->GetWordPos()[nowId].first,rpd->GetWordPos()[nowId].second,"<b><font color=\"#FF645A\">","</font></b>");
                refText+=tempText;
            }
            if(i!=rpd->GetPartOrig().size()-1)
            {
                if(rpd->GetSplitMode()==SplitMode::LineBreak)
                    refText+="<br>";
                if(rpd->GetSplitMode()==SplitMode::Section)
                    refText+="<br><br>";
            }
        }
        refText+="<br><br><br>";

        refText+="译文：<br>";
        refText+="------------------------------------------------<br>";
        for(int i=0;i<rpd->GetPartTran().size();i++)
        {
            for(int j=rpd->GetPartTran()[i].first;j<=rpd->GetPartTran()[i].second;j++)
            {
                QString tempText=rpd->GetSentenceTran()[j];
                refText+=tempText;
            }
            if(i!=rpd->GetPartTran().size()-1)
            {
                if(rpd->GetSplitMode()==SplitMode::LineBreak)
                    refText+="<br>";
                if(rpd->GetSplitMode()==SplitMode::Section)
                    refText+="<br><br>";
            }
        }
        refText+="<br><br><br>";
    }

    if(ui->comboBoxMode->currentIndex()==1)
    {
        refText+="------------------------------------------------";
        refText+="<br><br>";
        for(int i=0;i<rpd->GetPartOrig().size();i++)
        {
            for(int j=rpd->GetPartOrig()[i].first;j<=rpd->GetPartOrig()[i].second;j++)
            {
                QString tempText=rpd->GetSentenceOrig()[j];
                if(j==rpd->GetWordInSentenceId()[nowId])
                    AddFontString(tempText,rpd->GetWordPos()[nowId].first,rpd->GetWordPos()[nowId].second,"<b><font color=\"#FF645A\">","</font></b>");
                refText+=tempText;
            }
            refText+="<br><br>";
            for(int j=rpd->GetPartTran()[i].first;j<=rpd->GetPartTran()[i].second;j++)
            {
                QString tempText=rpd->GetSentenceTran()[j];
                refText+=tempText;
            }
            refText+="<br><br>";
            refText+="------------------------------------------------";
            refText+="<br><br>";
        }
    }

    if(ui->comboBoxMode->currentIndex()==2)
    {
        for(int i=0;i<rpd->GetSentenceOrig().size();i++)
        {
            QString tempText1=rpd->GetSentenceOrig()[i];
            if(i==rpd->GetWordInSentenceId()[nowId])
                AddFontString(tempText1,rpd->GetWordPos()[nowId].first,rpd->GetWordPos()[nowId].second,"<b><font color=\"#FF645A\">","</font></b>");
            refText+=tempText1;
            refText+="<br>";

            QString tempText2="";
            for(int j=rpd->GetAlign()[i].first;j<=rpd->GetAlign()[i].second;j++)
                tempText2+=rpd->GetSentenceTran()[j];
            refText+=tempText2;
            refText+="<br><br>";
        }
    }

    int nowLocation=ui->textBrowserRef->verticalScrollBar()->value();
    ui->textBrowserRef->setText(refText);
    if(lastMode==ui->comboBoxMode->currentIndex())
        ui->textBrowserRef->verticalScrollBar()->setValue(nowLocation);
    else
        ui->textBrowserRef->verticalScrollBar()->setValue(0);
}

void LearnSplit::GenerateTran()
{
    ui->labelLocation->setText("当前分句位置："+QString::number(nowId+1)+"/"+QString::number(totalNum));
    ui->labelOneText->clear();
    ui->labelTwoText->setText(rpd->GetSentenceMean()[nowId]);

    for(int i=rpd->GetSentenceId()[nowId].first;i<=rpd->GetSentenceId()[nowId].second;i++)
        ui->labelOneText->setText(ui->labelOneText->text()+rpd->GetSentenceOrig()[i]);

    textToRead.clear();
    textToRead.append(ui->labelOneText->text());
    textToRead.append("    ");
    textToRead.append(ui->labelTwoText->text());

    QString refText="";

    if(ui->comboBoxMode->currentIndex()==0)
    {
        refText+="原文：<br>";
        refText+="------------------------------------------------<br>";
        for(int i=0;i<rpd->GetPartOrig().size();i++)
        {
            for(int j=rpd->GetPartOrig()[i].first;j<=rpd->GetPartOrig()[i].second;j++)
            {
                QString tempText=rpd->GetSentenceOrig()[j];
                if(j>=rpd->GetSentenceId()[nowId].first && j<=rpd->GetSentenceId()[nowId].second)
                    AddFontString(tempText,0,tempText.length(),"<b><font color=\"#FF645A\">","</font></b>");
                refText+=tempText;
            }
            if(i!=rpd->GetPartOrig().size()-1)
            {
                if(rpd->GetSplitMode()==SplitMode::LineBreak)
                    refText+="<br>";
                if(rpd->GetSplitMode()==SplitMode::Section)
                    refText+="<br><br>";
            }
        }
        refText+="<br><br><br>";

        refText+="译文：<br>";
        refText+="------------------------------------------------<br>";
        for(int i=0;i<rpd->GetPartTran().size();i++)
        {
            for(int j=rpd->GetPartTran()[i].first;j<=rpd->GetPartTran()[i].second;j++)
            {
                QString tempText=rpd->GetSentenceTran()[j];
                refText+=tempText;
            }
            if(i!=rpd->GetPartTran().size()-1)
            {
                if(rpd->GetSplitMode()==SplitMode::LineBreak)
                    refText+="<br>";
                if(rpd->GetSplitMode()==SplitMode::Section)
                    refText+="<br><br>";
            }
        }
        refText+="<br><br><br>";
    }

    if(ui->comboBoxMode->currentIndex()==1)
    {
        refText+="------------------------------------------------";
        refText+="<br><br>";
        for(int i=0;i<rpd->GetPartOrig().size();i++)
        {
            for(int j=rpd->GetPartOrig()[i].first;j<=rpd->GetPartOrig()[i].second;j++)
            {
                QString tempText=rpd->GetSentenceOrig()[j];
                if(j>=rpd->GetSentenceId()[nowId].first && j<=rpd->GetSentenceId()[nowId].second)
                    AddFontString(tempText,0,tempText.length(),"<b><font color=\"#FF645A\">","</font></b>");
                refText+=tempText;
            }
            refText+="<br><br>";
            for(int j=rpd->GetPartTran()[i].first;j<=rpd->GetPartTran()[i].second;j++)
            {
                QString tempText=rpd->GetSentenceTran()[j];
                refText+=tempText;
            }
            refText+="<br><br>";
            refText+="------------------------------------------------";
            refText+="<br><br>";
        }
    }

    if(ui->comboBoxMode->currentIndex()==2)
    {
        for(int i=0;i<rpd->GetSentenceOrig().size();i++)
        {
            QString tempText1=rpd->GetSentenceOrig()[i];
            if(i>=rpd->GetSentenceId()[nowId].first && i<=rpd->GetSentenceId()[nowId].second)
                AddFontString(tempText1,0,tempText1.length(),"<b><font color=\"#FF645A\">","</font></b>");
            refText+=tempText1;
            refText+="<br>";

            QString tempText2="";
            for(int j=rpd->GetAlign()[i].first;j<=rpd->GetAlign()[i].second;j++)
                tempText2+=rpd->GetSentenceTran()[j];
            refText+=tempText2;
            refText+="<br><br>";
        }
    }

    int nowLocation=ui->textBrowserRef->verticalScrollBar()->value();
    ui->textBrowserRef->setText(refText);
    if(lastMode==ui->comboBoxMode->currentIndex())
        ui->textBrowserRef->verticalScrollBar()->setValue(nowLocation);
    else
        ui->textBrowserRef->verticalScrollBar()->setValue(0);
}

void LearnSplit::on_pushButtonLast_clicked()
{
    nowId--;
    GeneratePage();
}

void LearnSplit::on_pushButtonNext_clicked()
{
    nowId++;
    GeneratePage();
}

void LearnSplit::on_comboBoxMode_currentIndexChanged(int index)
{
    GeneratePage();
    lastMode=index;
}

void LearnSplit::on_pushButtonExit_clicked()
{
    emit(ShowLearn());
}

void LearnSplit::on_pushButtonRead_clicked()
{
    tts->say(textToRead);
}

void LearnSplit::on_pushButtonHelp_clicked()
{
    QString modeName="自主学习模式";
    QStringList text;
    text.append("方向键左："+ui->pushButtonLast->text());
    text.append("方向键右："+ui->pushButtonNext->text());
    text.append("数字键3："+ui->pushButtonRead->text());
    help->Init(modeName,text);
    help->exec();
}
