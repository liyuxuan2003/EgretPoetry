#include "LearnNormal.h"
#include "ui_LearnNormal.h"

LearnNormal::LearnNormal(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::LearnNormal)
{
    ui->setupUi(this);

    l1=new LiEasyLayout(0,width(),height(),LiEasyLayout::left,0.6f,0.1f);
    l2=new LiFixedToLayout();

    l1->AddUnit(ui->labelTitle);
    l1->AddUnit(ui->labelAuthor);

    l1->AddUnit(ui->labelOrig);
    l1->AddUnit(ui->textBrowserOrig);
    l1->AddUnit(ui->labelTran);
    l1->AddUnit(ui->textBrowserTran);
    l1->AddUnit(new QWidget*[3]{ui->labelRead,ui->comboBoxRead,ui->pushButtonRead},3);

    l1->LayoutConfigDone();

    l2->AddUnit(ui->pushButtonExit,width(),height(),LiFixedCorner::RightBottom);

    tts=new QTextToSpeech(this);
    tts->setLocale(QLocale::Chinese);
    tts->setRate(0.0);
    tts->setPitch(1.0);
    tts->setVolume(1.0);
}

LearnNormal::~LearnNormal()
{
    delete ui;
}

void LearnNormal::resizeEvent(QResizeEvent *event)
{
    l1->ResizeWithEasyLayout(width(),height());
    l2->ResizeWithFixedToLayout(width(),height());
}

void LearnNormal::Init(const QString& sourcePath)
{
    rpd=new ReadPoetryData(sourcePath);
    ui->labelTitle->setText(rpd->GetTitle());
    ui->labelAuthor->setText("作者："+rpd->GetAuthor());

    QString textOrig="";
    for(int i=0;i<rpd->GetPartOrig().size();i++)
    {
        for(int j=rpd->GetPartOrig()[i].first;j<=rpd->GetPartOrig()[i].second;j++)
            textOrig+=rpd->GetSentenceOrig()[j];
        if(rpd->GetSplitMode()==SplitMode::LineBreak)
            textOrig+="<br>";
        if(rpd->GetSplitMode()==SplitMode::Section)
            textOrig+="<br><br>";
    }
    ui->textBrowserOrig->setText(textOrig);

    QString textTran="";
    for(int i=0;i<rpd->GetPartTran().size();i++)
    {
        for(int j=rpd->GetPartTran()[i].first;j<=rpd->GetPartTran()[i].second;j++)
            textTran+=rpd->GetSentenceTran()[j];
        if(rpd->GetSplitMode()==SplitMode::LineBreak)
            textTran+="<br>";
        if(rpd->GetSplitMode()==SplitMode::Section)
            textTran+="<br><br>";
    }
    ui->textBrowserTran->setText(textTran);

    toReadWholeText=textOrig;
    toReadParagraph.clear();
    for(int i=0;i<rpd->GetPartOrig().size();i++)
    {
        toReadParagraph.append("");
        for(int j=rpd->GetPartOrig()[i].first;j<=rpd->GetPartOrig()[i].second;j++)
        {
            toReadParagraph[i].append(rpd->GetSentenceOrig()[j]);
        }
    }

    while(ui->comboBoxRead->count()!=0)
        ui->comboBoxRead->removeItem(0);

    ui->comboBoxRead->addItem("全文");
    for(int i=0;i<rpd->GetPartOrig().size();i++)
    {
        if(rpd->GetSplitMode()==SplitMode::Section)
            ui->comboBoxRead->addItem("第"+QString::number(i+1)+"段");
        if(rpd->GetSplitMode()==SplitMode::LineBreak)
            ui->comboBoxRead->addItem("第"+QString::number(i+1)+"句");
    }
}

void LearnNormal::on_pushButtonRead_clicked()
{
    if(ui->comboBoxRead->currentIndex()==0)
        tts->say(toReadWholeText);
    else
        tts->say(toReadParagraph[ui->comboBoxRead->currentIndex()-1]);
}

void LearnNormal::on_pushButtonExit_clicked()
{
    tts->stop();
    emit(ShowLearn());
}
