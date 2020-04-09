#include "DataInput.h"
#include "ui_DataInput.h"

DataInput::DataInput(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::DataInput)
{
    ui->setupUi(this);
}

DataInput::~DataInput()
{
    delete ui;
}
