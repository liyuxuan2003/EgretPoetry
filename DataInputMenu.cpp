#include "DataInputMenu.h"
#include "ui_DataInputMenu.h"

DataInputMenu::DataInputMenu(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::DataInputMenu)
{
    ui->setupUi(this);

    l1=new LiEasyLayout(0,width(),height(),LiEasyLayout::left,0.6f,0.1f);
    l2=new LiFixedToLayout();

    l1->AddUnit(ui->labelTitle);
    l1->AddUnit(new QWidget*[2]{ui->labelName,ui->lineEditName},2);
    l1->AddUnit(new QWidget*[3]{ui->labelPath,ui->pushButtonPath,ui->labelPathSet},3);
    l1->AddUnit(new QWidget*[2]{ui->pushButtonCreate,ui->pushButtonOpen},2);
    l1->AddUnit(ui->labelFailed);

    l1->LayoutConfigDone();

    l2->AddUnit(ui->pushButtonExit,width(),height(),LiFixedCorner::RightBottom);
}

DataInputMenu::~DataInputMenu()
{
    delete ui;
}

void DataInputMenu::resizeEvent(QResizeEvent *event)
{
    l1->ResizeWithEasyLayout(width(),height());
    l2->ResizeWithFixedToLayout(width(),height());
}

void DataInputMenu::Init()
{
    path="D:/";
    ui->labelPathSet->setText(path);
    ui->lineEditName->setText("");
    ui->labelFailed->hide();
}

void DataInputMenu::on_pushButtonPath_clicked()
{
    QString dir=QFileDialog::getExistingDirectory(this,"选择文件夹",path,QFileDialog::ShowDirsOnly);
    if(dir=="")
        return;
    path=DirAddSlash(dir);
    ui->labelPathSet->setText(path);
}

void DataInputMenu::on_pushButtonCreate_clicked()
{
    name=ui->lineEditName->text();
    if(!QFile::exists(path+name+".json"))
    {
        QFile file(path+name+".json");
        file.open(QIODevice::WriteOnly);
        file.close();
        ui->labelFailed->hide();
        emit(ShowDataInput(path,name));
    }
    else
        ui->labelFailed->show();
}

void DataInputMenu::on_pushButtonOpen_clicked()
{
    QString file=QFileDialog::getOpenFileName(this,"选择需要打开的诗文库","D:/","JSON File (*.json)");
    if(file=="")
        return;
    emit(ShowDataInput(GetDirByPath(file),GetNameByPath(file)));
}

void DataInputMenu::on_pushButtonExit_clicked()
{
    emit(ShowMenu());
}
