#ifndef DATAINPUTMENU_H
#define DATAINPUTMENU_H

#include <QFrame>
#include <QFileDialog>

#include <LiLibrary/LiEasyLayout.h>
#include <LiLibrary/LiFixedToLayout.h>
#include <LiLibrary/LiFileName.h>

namespace Ui
{
    class DataInputMenu;
}

class DataInputMenu : public QFrame
{
    Q_OBJECT

public:
    explicit DataInputMenu(QWidget *parent = nullptr);
    ~DataInputMenu();

    void Init();

protected:
    virtual void resizeEvent(QResizeEvent * event);

private slots:
    void on_pushButtonPath_clicked();

    void on_pushButtonCreate_clicked();

    void on_pushButtonExit_clicked();

private:
    Ui::DataInputMenu* ui;

    LiEasyLayout* l1;
    LiFixedToLayout* l2;

    QString path;
    QString name;

signals:
    void ShowDataInput(const QString& path,const QString& name);

    void ShowMenu();
};

#endif // DATAINPUTMENU_H
