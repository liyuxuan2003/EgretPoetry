#include "TranWord.h"
#include "ui_TranWord.h"

TranWord::TranWord(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::TranWord)
{
    ui->setupUi(this);

    l1=new LiEasyLayout(0,width(),height(),LiEasyLayout::left,0.6f,0.1f);
    l2=new LiFixedToLayout();

    l1->AddUnit(ui->labelTitle);

    l1->AddUnit(ui->labelLocation);

    l1->AddUnit(ui->labelWordTitle);
    l1->AddUnit(ui->labelWord);

    l1->AddUnit(new QWidget*[3]{ui->labelUserAns,ui->lineEditUserAns,ui->pushButtonCheck},3);
    l1->AddUnit(new QWidget*[4]{ui->labelRightAns,ui->lineEditRightAns,ui->pushButtonAnsR,ui->pushButtonAnsW},4);

    l1->AddUnit(ui->labelReference);
    l1->AddUnit(ui->textBrowserReference);

    l1->LayoutConfigDone();

    l2->AddUnit(ui->pushButtonExit,width(),height(),LiFixedCorner::RightBottom);
    l2->AddUnit(ui->pushButtonHelp,width(),height(),LiFixedCorner::RightTop);

    tranWordReview=new TranWordReview();
    tranWordReview->hide();

    help=new Help();
    help->hide();
}

TranWord::~TranWord()
{
    delete ui;
}

void TranWord::resizeEvent(QResizeEvent *event)
{
    l1->ResizeWithEasyLayout(width(),height());
    l2->ResizeWithFixedToLayout(width(),height());
}

void TranWord::keyPressEvent(QKeyEvent *ev)
{
    if(ev->key()==Qt::Key_Space)
    {
        if(ui->pushButtonAnsR->isVisible()==false)
            ui->pushButtonCheck->click();
        else
            ui->pushButtonAnsR->click();
    }
    else if(ev->key()==Qt::Key_1 && ui->pushButtonAnsR->isVisible()==true)
        ui->pushButtonAnsR->click();
    else if(ev->key()==Qt::Key_2 && ui->pushButtonAnsW->isVisible()==true)
        ui->pushButtonAnsW->click();
}

void TranWord::Init(const QStringList& sourcePath,bool isRandom,QList<QPair<int,int>> needTest)
{
    this->sourcePath=sourcePath;
    this->isRandom=isRandom;
    this->needTest=needTest;

    rpd.clear();
    order.clear();

    for(int i=0;i<sourcePath.size();i++)
        rpd.append(new ReadPoetryData(sourcePath[i]));

    order=RandomOrder(needTest.size(),isRandom);

    nowId=0;
    userRecord.clear();

    GeneratePage();
}

void TranWord::GeneratePage()
{
    ui->lineEditUserAns->setFocus();

    if(nowId>=order.size())
    {
        int totalNum=userRecord.size();
        int rightNum=0;
        int wrongNum=0;
        QList<QPair<int,int>> toReview;
        for(int i=0;i<userRecord.size();i++)
        {
            if(userRecord[i]==0)
                rightNum++;
            if(userRecord[i]==1)
            {
                wrongNum++;
                toReview.append(needTest[i]);
            }
        }
        tranWordReview->Init(totalNum,rightNum,wrongNum);
        tranWordReview->exec();
        if(tranWordReview->IsReview()==true)
            Init(sourcePath,isRandom,toReview);
        else
            emit(ShowMenu());
        return;
    }

    ui->labelLocation->setText("当前加点字："+QString::number(nowId+1)+"/"+QString::number(order.size()));

    int nowSection=needTest[order[nowId]].first;
    int nowInsideId=needTest[order[nowId]].second;
    ReadPoetryData*& nowRpd=rpd[nowSection];

    int nowWordSentId=nowRpd->GetWordInSentenceId()[nowInsideId];
    QString nowWordSent=nowRpd->GetSentenceOrig()[nowWordSentId];
    QPair<int,int> nowWordLocation=nowRpd->GetWordPos()[nowInsideId];

    AddFontString(nowWordSent,nowWordLocation.first,nowWordLocation.second,"<b><font color=\"#FF645A\">","</font></b>");

    ui->labelWord->setText(nowWordSent);
    ui->lineEditUserAns->clear();
    ui->lineEditRightAns->clear();

    int splitCounter=0;
    QString nowOrigText="";
    for(int i=0;i<nowRpd->GetSentenceOrig().size();i++)
    {
        QString toBeAppend=nowRpd->GetSentenceOrig()[i];
        if(i==nowWordSentId)
            AddFontString(toBeAppend,nowWordLocation.first,nowWordLocation.second,"<b><font color=\"#FF645A\">","</font></b>");

        nowOrigText.append(toBeAppend);

        if(nowRpd->GetPartOrig()[splitCounter].second==i && splitCounter!=nowRpd->GetPartOrig().size())
        {
            splitCounter++;
            if(nowRpd->GetSplitMode()==SplitMode::LineBreak)
                nowOrigText+="<br>";
            if(nowRpd->GetSplitMode()==SplitMode::Section)
                nowOrigText+="<br><br>";
        }
    }

    int nowLocation=ui->textBrowserReference->verticalScrollBar()->value();
    ui->textBrowserReference->setText(nowOrigText);
    ui->textBrowserReference->verticalScrollBar()->setValue(nowLocation);

    ui->pushButtonAnsR->hide();
    ui->pushButtonAnsW->hide();
}

void TranWord::AddFontString(QString& source,int begin,int end,QString beginString,QString endString)
{
    QString targetString=source.mid(begin,end-begin+1);
    source.remove(begin,end-begin+1);

    targetString.prepend(beginString);
    targetString.append(endString);
    source.insert(begin,targetString);
}

void TranWord::on_pushButtonCheck_clicked()
{
    int nowSection=needTest[order[nowId]].first;
    int nowInsideId=needTest[order[nowId]].second;
    ReadPoetryData*& nowRpd=rpd[nowSection];

    ui->lineEditRightAns->setText(nowRpd->GetWordMean()[nowInsideId]);

    ui->pushButtonAnsR->show();
    ui->pushButtonAnsW->show();
}

void TranWord::on_pushButtonAnsR_clicked()
{
    userRecord.append(0);
    nowId++;
    GeneratePage();
}

void TranWord::on_pushButtonAnsW_clicked()
{
    userRecord.append(1);
    nowId++;
    GeneratePage();
}

void TranWord::on_pushButtonExit_clicked()
{
    emit(ShowMenu());
}

void TranWord::on_pushButtonHelp_clicked()
{
    QString modeName="重点句翻译练习";
    QStringList text;
    text.append("空格键：显示答案/正确");
    text.append("数字键1：正确");
    text.append("数字键2：错误");
    text.append("Tab键：在快捷键和输入框间切换");

    help->Init(modeName,text);
    help->exec();
}
