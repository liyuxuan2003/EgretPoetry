#ifndef DATAINPUTCONFIGSOURCE_H
#define DATAINPUTCONFIGSOURCE_H

#include <QFrame>

#include <LiLibrary/LiEasyLayout.h>
#include <LiLibrary/LiFixedToLayout.h>

namespace Ui
{
    class DataInputConfigSource;
}

class DataInputConfigSource : public QFrame
{
    Q_OBJECT

public:
    explicit DataInputConfigSource(QWidget *parent = nullptr);
    ~DataInputConfigSource();

    void Init(const QString& original,const QString& translate);

protected:
    virtual void resizeEvent(QResizeEvent * event);

private slots:
    void on_pushButtonDone_clicked();

private:
    Ui::DataInputConfigSource *ui;

    LiEasyLayout* l1;

    QString original;
    QString translate;

signals:
    void ConfigSourceDone(const QString& original,const QString& translate);
};

#endif // DATAINPUTCONFIGSOURCE_H
