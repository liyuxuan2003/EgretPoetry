#ifndef DATAINPUT_H
#define DATAINPUT_H

#include <QFrame>

#include <LiLibrary/LiEasyLayout.h>
#include <LiLibrary/LiFixedToLayout.h>

namespace Ui
{
    class DataInput;
}

class DataInput : public QFrame
{
    Q_OBJECT

public:
    explicit DataInput(QWidget *parent = nullptr);
    ~DataInput();

    void Init(const QString& path,const QString& name);

    void WrtieInfo(const QString& title,const QString& author,const QString& type);

    void WriteSource(const QString& original,const QString& translate);

protected:
    virtual void resizeEvent(QResizeEvent * event);

private slots:
    void on_pushButtonExit_clicked();

    void on_pushButtonInfo_clicked();

    void on_pushButtonSource_clicked();

private:
    Ui::DataInput *ui;

    LiEasyLayout* l1;
    LiFixedToLayout* l2;

    QString path;
    QString name;

    QString title;
    QString author;
    QString type;

    QString original;
    QString translate;

signals:
    void ShowMenu();

    void ShowDataInputConfigInfo(const QString& title,const QString& author,const QString& type);

    void ShowDataInputConfigSource(const QString& original,const QString& translate);

};

#endif // DATAINPUT_H
