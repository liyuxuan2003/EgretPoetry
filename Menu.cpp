#include "Menu.h"
#include "ui_Menu.h"

Menu::Menu(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);

    l1=new LiEasyLayout(0,width(),height(),LiEasyLayout::left,0.6f);

    l2=new LiFixedToLayout();

    l1->AddUnit(ui->labelTitle);
    l1->AddUnit(new QWidget*[2]{ui->pushButtonLearn,ui->pushButtonReciteSingle},2);
    l1->AddUnit(new QWidget*[2]{ui->pushButtonTransWord,ui->pushButtonReciteWhole},2);
    l1->AddUnit(new QWidget*[2]{ui->pushButtonTransSent,ui->pushButtonDataInput},2);
    l1->AddUnit(new QWidget*[2]{ui->labelExtraInfo1,ui->labelExtraInfo2},2);

    l1->LayoutConfigDone();

    l2->AddUnit(ui->labelIcon,width(),height(),LiFixedCorner::RightTop);
    l2->AddUnit(ui->pushButtonExit,width(),height(),LiFixedCorner::RightBottom);
    l2->AddUnit(ui->pushButtonAbout,width(),height(),LiFixedCorner::RightBottom);
}

Menu::~Menu()
{
    delete ui;
}

void Menu::resizeEvent(QResizeEvent *event)
{
    l1->ResizeWithEasyLayout(width(),height());
    l2->ResizeWithFixedToLayout(width(),height());
}

void Menu::on_pushButtonDataInput_clicked()
{
    emit(ShowDataInputMenu());
}

void Menu::on_pushButtonTransWord_clicked()
{
    emit(ShowTranWordMenu());
}

void Menu::on_pushButtonTransSent_clicked()
{
    emit(ShowTranSentMenu());
}

void Menu::on_pushButtonReciteWhole_clicked()
{
    emit(ShowReciteWholeMenu());
}
