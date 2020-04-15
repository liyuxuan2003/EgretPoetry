#ifndef DATAINPUTCONFIGINFO_H
#define DATAINPUTCONFIGINFO_H

#include <QFrame>

#include <LiLibrary/LiEasyLayout.h>
#include <LiLibrary/LiFixedToLayout.h>

namespace Ui
{
    class DataInputConfigInfo;
}

class DataInputConfigInfo : public QFrame
{
    Q_OBJECT

public:
    explicit DataInputConfigInfo(QWidget *parent = nullptr);
    ~DataInputConfigInfo();

    void Init(const QString& title,const QString& author,const QString& type);

protected:
    virtual void resizeEvent(QResizeEvent * event);

private slots:
    void on_pushButtonDone_clicked();

private:
    Ui::DataInputConfigInfo *ui;

    LiEasyLayout* l1;

signals:
    void ConfigInfoDone(const QString& title,const QString& author,const QString& type);
};

#endif // DATAINPUTCONFIGINFO_H
