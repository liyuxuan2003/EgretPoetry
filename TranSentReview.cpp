#include "TranSentReview.h"
#include "ui_TranSentReview.h"

TranSentReview::TranSentReview(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TranSentReview)
{
    ui->setupUi(this);
}

TranSentReview::~TranSentReview()
{
    delete ui;
}

void TranSentReview::Init(int total,int right,int wrong)
{
    ui->labelRight->setText("正确："+QString::number(right));
    ui->labelWrong->setText("错误："+QString::number(wrong));
    ui->labelTotal->setText("总计："+QString::number(total));
    isReview=false;

    if(right==total)
    {
        ui->labelReview->setText("关闭窗口返回首页！");
        ui->pushButtonYes->hide();
        ui->pushButtonNo->hide();
    }
    else
    {
        ui->labelReview->setText("是否进入复习模式？");
        ui->pushButtonYes->show();
        ui->pushButtonNo->show();
    }
}

bool TranSentReview::IsReview()
{
    return isReview;
}

void TranSentReview::on_pushButtonYes_clicked()
{
    isReview=true;
    this->close();
}

void TranSentReview::on_pushButtonNo_clicked()
{
    isReview=false;
    this->close();
}

