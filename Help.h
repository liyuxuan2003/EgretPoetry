#ifndef HELP_H
#define HELP_H

#include <QDialog>
#include <QScrollBar>

namespace Ui
{
    class Help;
}

class Help : public QDialog
{
    Q_OBJECT

public:
    explicit Help(QWidget *parent = nullptr);
    ~Help();

    void Init(const QString& modeName,const QStringList& text);

private:
    Ui::Help *ui;
};

#endif // HELP_H
