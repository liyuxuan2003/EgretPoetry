#include "TranSent.h"
#include "ui_TranSent.h"

TranSent::TranSent(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::TranSent)
{
    ui->setupUi(this);

    l1=new LiEasyLayout(0,width(),height(),LiEasyLayout::left,0.6f,0.1f);
    l2=new LiFixedToLayout();

    l1->AddUnit(ui->labelTitle);

    l1->AddUnit(ui->labelLocation);

    l1->AddUnit(ui->labelSentTitle);
    l1->AddUnit(ui->labelSent);

    l1->AddUnit(new QWidget*[3]{ui->labelUserAns,ui->lineEditUserAns,ui->pushButtonCheck},3);
    l1->AddUnit(new QWidget*[4]{ui->labelRightAns,ui->lineEditRightAns,ui->pushButtonAnsR,ui->pushButtonAnsW},4);

    l1->AddUnit(ui->labelReference);
    l1->AddUnit(ui->textBrowserReference);

    l1->LayoutConfigDone();

    l2->AddUnit(ui->pushButtonExit,width(),height(),LiFixedCorner::RightBottom);
    l2->AddUnit(ui->pushButtonHelp,width(),height(),LiFixedCorner::RightTop);

    tranSentReview=new TranSentReview();
    tranSentReview->hide();

    help=new Help();
    help->hide();
}

TranSent::~TranSent()
{
    delete ui;
}

void TranSent::resizeEvent(QResizeEvent *event)
{
    l1->ResizeWithEasyLayout(width(),height());
    l2->ResizeWithFixedToLayout(width(),height());
}

void TranSent::keyPressEvent(QKeyEvent *ev)
{
    if(ev->key()==Qt::Key_Space)
    {
        if(ui->pushButtonAnsR->isVisible()==false)
            ui->pushButtonCheck->click();
        else
            ui->pushButtonAnsR->click();
    }
    else if(ev->key()==Qt::Key_1)
        ui->pushButtonAnsR->click();
    else if(ev->key()==Qt::Key_2)
        ui->pushButtonAnsW->click();
}

void TranSent::Init(const QStringList& sourcePath,bool isRandom,QList<QPair<int,int>> needTest)
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

void TranSent::GeneratePage()
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
        tranSentReview->Init(totalNum,rightNum,wrongNum);
        tranSentReview->exec();
        if(tranSentReview->IsReview()==true)
            Init(sourcePath,isRandom,toReview);
        else
            emit(ShowMenu());
        return;
    }

    ui->labelLocation->setText("当前重点句："+QString::number(nowId+1)+"/"+QString::number(order.size()));

    int nowSection=needTest[order[nowId]].first;
    int nowInsideId=needTest[order[nowId]].second;
    ReadPoetryData*& nowRpd=rpd[nowSection];

    QPair<int,int> nowSentId=nowRpd->GetSentenceId()[nowInsideId];
    QString nowSentMean=nowRpd->GetSentenceMean()[nowInsideId];

    ui->labelSent->clear();
    for(int i=nowSentId.first;i<=nowSentId.second;i++)
        ui->labelSent->setText(ui->labelSent->text()+nowRpd->GetSentenceOrig()[i]);

    ui->lineEditUserAns->clear();
    ui->lineEditRightAns->clear();

    int splitCounter=0;
    QString nowOrigText="";
    for(int i=0;i<nowRpd->GetSentenceOrig().size();i++)
    {
        QString toBeAppend=nowRpd->GetSentenceOrig()[i];
        if(i>=nowSentId.first && i<=nowSentId.second)
        {
            toBeAppend.prepend("<b><font color=\"#FF645A\">");
            toBeAppend.append("</font></b>");
        }

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

void TranSent::on_pushButtonCheck_clicked()
{
    int nowSection=needTest[order[nowId]].first;
    int nowInsideId=needTest[order[nowId]].second;
    ReadPoetryData*& nowRpd=rpd[nowSection];

    ui->lineEditRightAns->setText(nowRpd->GetSentenceMean()[nowInsideId]);

    ui->pushButtonAnsR->show();
    ui->pushButtonAnsW->show();
}

void TranSent::on_pushButtonAnsR_clicked()
{
    userRecord.append(0);
    nowId++;
    GeneratePage();
}

void TranSent::on_pushButtonAnsW_clicked()
{
    userRecord.append(1);
    nowId++;
    GeneratePage();
}

void TranSent::on_pushButtonExit_clicked()
{
    emit(ShowMenu());
}

void TranSent::on_pushButtonHelp_clicked()
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
