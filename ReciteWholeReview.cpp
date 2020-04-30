#include "ReciteWholeReview.h"
#include "ui_ReciteWholeReview.h"

ReciteWholeReview::ReciteWholeReview(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReciteWholeReview)
{
    ui->setupUi(this);
}

ReciteWholeReview::~ReciteWholeReview()
{
    delete ui;
}

void ReciteWholeReview::Init(int total,int right,int punctuation,int one,int two,int read,int all)
{
    ui->labelRight->setText("答案正确："+QString::number(right));
    ui->labelPunctuation->setText("提示标点："+QString::number(punctuation));
    ui->labelOne->setText("提示一字："+QString::number(one));
    ui->labelTwo->setText("提示两字："+QString::number(two));
    ui->labelRead->setText("提示语音："+QString::number(read));
    ui->labelAll->setText("提示全句："+QString::number(all));
    ui->labelTotal->setText("句数总计："+QString::number(total));
    isReview=0;

    if(right==total)
    {
        ui->labelReview->setText("关闭窗口返回首页！");
        ui->pushButtonYesT->hide();
        ui->pushButtonYesF->hide();
        ui->pushButtonNo->hide();
    }
    else
    {
        ui->labelReview->setText("是否进入复习模式？");
        ui->pushButtonYesT->show();
        ui->pushButtonYesF->show();
        ui->pushButtonNo->show();
    }
}

int ReciteWholeReview::IsReview()
{
    return isReview;
}

void ReciteWholeReview::on_pushButtonYesT_clicked()
{
    isReview=2;
    this->close();
}

void ReciteWholeReview::on_pushButtonYesF_clicked()
{
    isReview=1;
    this->close();
}

void ReciteWholeReview::on_pushButtonNo_clicked()
{
    isReview=0;
    this->close();
}
