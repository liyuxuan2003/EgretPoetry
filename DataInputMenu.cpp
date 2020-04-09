#include "DataInputMenu.h"
#include "ui_DataInputMenu.h"

DataInputMenu::DataInputMenu(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::DataInputMenu)
{
    ui->setupUi(this);
}

DataInputMenu::~DataInputMenu()
{
    delete ui;
}
