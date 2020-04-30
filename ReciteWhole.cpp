#include "ReciteWhole.h"
#include "ui_ReciteWhole.h"

ReciteWhole::ReciteWhole(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::ReciteWhole)
{
    ui->setupUi(this);

    l1=new LiEasyLayout(0,width(),height(),LiEasyLayout::left,0.6f,0.1f);
    l2=new LiFixedToLayout();

    l1->AddUnit(ui->labelTitle);
    l1->AddUnit(ui->labelLocation);
    l1->AddUnit(new QWidget*[3]{ui->labelUserAnsTitle,ui->lineEditUserAns,ui->pushButtonNext},3);
    l1->AddUnit(new QWidget*[3]{ui->labelCover,ui->labelRightAnsTitle,ui->labelRightAns},3);

    l1->AddUnit();
    l1->AddElementInUnit(ui->pushButtonOne);
    l1->AddElementInUnit(ui->pushButtonTwo);
    l1->AddElementInUnit(ui->pushButtonRead);
    l1->AddElementInUnit(ui->pushButtonAll);
    l1->AddElementInUnit(ui->pushButtonPunctuation);

    l1->AddUnit(ui->labelTips);

    l1->AddUnit(ui->labelReference);
    l1->AddUnit(ui->textBrowserReference);

    l1->LayoutConfigDone();

    l2->AddUnit(ui->pushButtonExit,width(),height(),LiFixedCorner::RightBottom);

    reciteWholeReview=new ReciteWholeReview();
    reciteWholeReview->hide();

    tts = new QTextToSpeech(this);
    tts->setLocale(QLocale::Chinese);
    tts->setRate(0.0);
    tts->setPitch(1.0);
    tts->setVolume(1.0);
}

ReciteWhole::~ReciteWhole()
{
    delete ui;
}

void ReciteWhole::resizeEvent(QResizeEvent *event)
{
    l1->ResizeWithEasyLayout(width(),height());
    l2->ResizeWithFixedToLayout(width(),height());
}

void ReciteWhole::Init(QString sourcePath,bool isManual)
{
    this->sourcePath=sourcePath;
    this->isManual=isManual;

    nowId=0;
    rpd=new ReadPoetryData(sourcePath);

    userRecord.clear();

    needTest.clear();
    for(int i=0;i<rpd->GetSentenceOrig().size();i++)
        needTest.append(i);

    SetButtonStatus(ui->pushButtonPunctuation,isManual);

    GeneratePage();
}

void ReciteWhole::Init(QString sourcePath,bool isManual,const QList<int>& needTest)
{
    this->sourcePath=sourcePath;
    this->isManual=isManual;
    this->needTest=needTest;

    nowId=0;
    rpd=new ReadPoetryData(sourcePath);

    userRecord.clear();

    SetButtonStatus(ui->pushButtonPunctuation,isManual);

    GeneratePage();
}

void ReciteWhole::GeneratePage()
{
    ui->lineEditUserAns->clear();
    ui->labelRightAns->clear();

    userRecord.append(0);

    ui->labelLocation->setText("当前分句："+QString::number(nowId+1)+"/"+QString::number(needTest.size()));

    int len=rpd->GetSentenceOrig()[needTest[nowId]].length();
    QString rightAnsText="";
    for(int i=0;i<len-1;i++)
        rightAnsText+="＊";
    if(isManual==true)
        rightAnsText+=("<font color=\"#FFDE5A\">＊</font>");
    ui->labelRightAns->setText(rightAnsText);

    QString refText="";
    int splitCounter=0;
    for(int i=0;i<needTest[nowId];i++)
    {
        refText.append(rpd->GetSentenceOrig()[i]);

        if(rpd->GetPartOrig()[splitCounter].second==i && splitCounter!=rpd->GetPartOrig().size())
        {
            splitCounter++;
            if(rpd->GetSplitMode()==SplitMode::LineBreak)
                refText+="<br>";
            if(rpd->GetSplitMode()==SplitMode::Section)
                refText+="<br><br>";
        }
    }
    ui->textBrowserReference->setText(refText);

    if(isManual==true)
        ui->lineEditUserAns->setMaxLength(rpd->GetSentenceOrig()[needTest[nowId]].length());
    if(isManual==false)
        ui->lineEditUserAns->setMaxLength(rpd->GetSentenceOrig()[needTest[nowId]].length()-1);

    ui->pushButtonNext->hide();

    ui->labelTips->setText("答案提示：");
}

void ReciteWhole::on_lineEditUserAns_textChanged(const QString &arg1)
{
    QString userText=arg1;
    QString rightText=rpd->GetSentenceOrig()[needTest[nowId]];
    if(isManual==false)
        rightText.chop(1);

    if(userText.length()>rightText.length())
    {
        ui->pushButtonNext->click();
        return;
    }

    if(userText!=rightText)
    {
        QString setText;

        for(int i=0;i<userText.length();i++)
        {
            if(userText[i]==rightText[i])
                setText.append(userText[i]);
            else
                setText.append("<font color=\"#FF645A\">"+userText[i]+"</font>");
        }

        for(int i=0;i<rightText.length()-userText.length()-1;i++)
            setText.append("＊");
        if(isManual==true && userText.length()!=rightText.length())
            setText.append("<font color=\"#FFDE5A\">＊</font>");
        ui->labelRightAns->setText(setText);

        if(isManual==true)
            ui->lineEditUserAns->setMaxLength(rpd->GetSentenceOrig()[needTest[nowId]].length());
        if(isManual==false)
            ui->lineEditUserAns->setMaxLength(rpd->GetSentenceOrig()[needTest[nowId]].length()-1);
    }
    else
    {
        ui->labelRightAns->setText("<font color=\"#FFFFFF\">"+rightText+"</font>");
        ui->lineEditUserAns->setMaxLength(32767);
        ui->pushButtonNext->show();
    }
}

void ReciteWhole::on_pushButtonNext_clicked()
{
    nowId++;
    if(nowId<needTest.size())
        GeneratePage();
    else
    {
        int right=0;
        int punctuation=0;
        int one=0;
        int two=0;
        int read=0;
        int all=0;
        for(int i=0;i<userRecord.size();i++)
        {
            switch(userRecord[i])
            {
            case 0:
                right++;
                break;
            case 1:
                punctuation++;
                break;
            case 2:
                one++;
                break;
            case 3:
                two++;
                break;
            case 4:
                read++;
                break;
            case 5:
                all++;
                break;
            }
        }
        reciteWholeReview->Init(userRecord.size(),right,punctuation,one,two,read,all);
        reciteWholeReview->exec();

        if(reciteWholeReview->IsReview()==0)
            emit(ShowMenu());
        else
        {
            QList<int> toReview;
            for(int i=0;i<userRecord.size();i++)
            {
                if(reciteWholeReview->IsReview()==1 && userRecord[i]>=2)
                    toReview.append(needTest[i]);
                if(reciteWholeReview->IsReview()==2 && userRecord[i]>=1)
                    toReview.append(needTest[i]);
            }

            if(toReview.isEmpty()==true)
                emit(ShowMenu());
            if(toReview.isEmpty()==false)
                Init(sourcePath,isManual,toReview);
        }
    }
}

void ReciteWhole::on_pushButtonExit_clicked()
{
    emit(ShowMenu());
}

void ReciteWhole::on_pushButtonOne_clicked()
{
    ui->labelTips->setText("答案提示："+rpd->GetSentenceOrig()[needTest[nowId]].left(1));
    userRecord[nowId]=qMax(userRecord[nowId],2);
}

void ReciteWhole::on_pushButtonTwo_clicked()
{
    ui->labelTips->setText("答案提示："+rpd->GetSentenceOrig()[needTest[nowId]].left(2));
    userRecord[nowId]=qMax(userRecord[nowId],3);
}

void ReciteWhole::on_pushButtonRead_clicked()
{
    tts->say(rpd->GetSentenceOrig()[needTest[nowId]]);
    userRecord[nowId]=qMax(userRecord[nowId],4);
}

void ReciteWhole::on_pushButtonAll_clicked()
{
    ui->labelTips->setText("答案提示："+rpd->GetSentenceOrig()[needTest[nowId]]);
    userRecord[nowId]=qMax(userRecord[nowId],5);
}

void ReciteWhole::on_pushButtonPunctuation_clicked()
{
    const QString symbol[6]={"。","，","？","！","；","："};
    QString punctuation=rpd->GetSentenceOrig()[needTest[nowId]].right(1);
    if(punctuation=="。")
        ui->labelTips->setText("答案提示：句号（。）");
    if(punctuation=="，")
        ui->labelTips->setText("答案提示：逗号（，）");
    if(punctuation=="？")
        ui->labelTips->setText("答案提示：问号（？）");
    if(punctuation=="！")
        ui->labelTips->setText("答案提示：感叹号（！）");
    if(punctuation=="；")
        ui->labelTips->setText("答案提示：分号（；）");
    if(punctuation=="：")
        ui->labelTips->setText("答案提示：冒号（：）");
    userRecord[nowId]=qMax(userRecord[nowId],1);
}
