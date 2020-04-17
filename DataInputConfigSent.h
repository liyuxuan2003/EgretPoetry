#ifndef DATAINPUTCONFIGSENT_H
#define DATAINPUTCONFIGSENT_H

#include <QFrame>
#include <QPushButton>

#include <LiLibrary/LiEasyLayout.h>
#include <LiLibrary/LiFixedToLayout.h>

namespace Ui
{
    class DataInputConfigSent;
}

class DataInputConfigSent : public QFrame
{
    Q_OBJECT

public:
    explicit DataInputConfigSent(QWidget *parent = nullptr);
    ~DataInputConfigSent();

protected:
    virtual void resizeEvent(QResizeEvent * event);

private:
    Ui::DataInputConfigSent *ui;

    LiEasyLayout* l1;
};

#endif // DATAINPUTCONFIGSENT_H
