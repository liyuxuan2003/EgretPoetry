#include "TranSentMenu.h"
#include "ui_TranSentMenu.h"

TranSentMenu::TranSentMenu(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::TranSentMenu)
{
    ui->setupUi(this);

    l1=new LiEasyLayout(0,width(),height(),LiEasyLayout::left,0.6f,0.1f);
    l2=new LiFixedToLayout();

    l1->AddUnit(ui->labelTitle);
    l1->AddUnit(new QWidget*[3]{ui->labelTest,ui->pushButtonTest,ui->labelTestInfo},3);
    l1->AddUnit(new QWidget*[5]{ui->labelOrder,ui->radioButtonOrdered,ui->radioButtonRandom,ui->radioButtonSelect,ui->spinBoxSelect},5);
    l1->AddUnit(ui->pushButtonStart);
    l1->AddUnit(ui->labelFailed);

    l1->LayoutConfigDone();

    l2->AddUnit(ui->pushButtonExit,width(),height(),LiFixedCorner::RightBottom);
}

TranSentMenu::~TranSentMenu()
{
    delete ui;
}

void TranSentMenu::resizeEvent(QResizeEvent *event)
{
    l1->ResizeWithEasyLayout(width(),height());
    l2->ResizeWithFixedToLayout(width(),height());
}

void TranSentMenu::Init()
{
    ui->radioButtonOrdered->click();
    ui->spinBoxSelect->setValue(10);
    ui->spinBoxSelect->hide();
    ui->labelTestInfo->setText("未选择测试诗文库！");
    ui->labelFailed->hide();
    sourcePath.clear();
}

void TranSentMenu::on_radioButtonOrdered_clicked()
{
    ui->spinBoxSelect->hide();
}

void TranSentMenu::on_radioButtonRandom_clicked()
{
    ui->spinBoxSelect->hide();
}

void TranSentMenu::on_radioButtonSelect_clicked()
{
    ui->spinBoxSelect->show();
}

void TranSentMenu::on_pushButtonTest_clicked()
{
    QStringList files=QFileDialog::getOpenFileNames(this,"请选择测试诗文库","D:/","JSON File (*.json)");
    if(files.length()==0)
        return;
    sourcePath=files;
    ui->labelTestInfo->setText("已选择测试诗文库："+QString::number(sourcePath.length())+"个");
}

void TranSentMenu::on_pushButtonStart_clicked()
{
    if(sourcePath.size()==0)
    {
        ui->labelFailed->setText("请选择测试诗文库！");
        ui->labelFailed->show();
        return;
    }

    int totalNum=0;
    QList<int> sectionNum;
    for(int i=0;i<sourcePath.size();i++)
    {
        ReadPoetryData rpd(sourcePath[0]);
        if(rpd.IsError()==true)
        {
            ui->labelFailed->setText("选中的诗文库中存在损坏文件！");
            ui->labelFailed->show();
            return;
        }
        totalNum+=rpd.GetSentenceId().size();
        sectionNum.append(rpd.GetSentenceId().size());
    }

    bool isRandom=false;
    int selectNum=-1;

    if(ui->radioButtonOrdered->isChecked()==true)
    {
        isRandom=false;
        selectNum=totalNum;
    }
    else if(ui->radioButtonRandom->isChecked()==true)
    {
        isRandom=true;
        selectNum=totalNum;
    }
    else if(ui->radioButtonSelect->isChecked()==true)
    {
        isRandom=true;
        selectNum=qMin(totalNum,ui->spinBoxSelect->value());
    }

    QList<QPair<int,int>> needTest=RandomSelect(totalNum,selectNum,sectionNum);

    emit(ShowTranSent(sourcePath,isRandom,needTest));
}

void TranSentMenu::on_pushButtonExit_clicked()
{
    emit(ShowMenu());
}
