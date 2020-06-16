#include "Help.h"
#include "ui_Help.h"

Help::Help(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Help)
{
    ui->setupUi(this);
}

Help::~Help()
{
    delete ui;
}

void Help::Init(const QString& modeName,const QStringList& text)
{
    ui->label->setText(modeName+"-帮助");
    ui->textBrowser->clear();
    ui->textBrowser->append("以下是"+modeName+"中可用的快捷键：");
    ui->textBrowser->append("<br>");
    for(int i=0;i<text.size();i++)
    {
        ui->textBrowser->append(text[i]);
        ui->textBrowser->append("<br>");
    }
    ui->textBrowser->moveCursor(QTextCursor::Start);
}
