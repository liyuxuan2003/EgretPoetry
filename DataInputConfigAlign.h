#ifndef DATAINPUTCONFIGALIGN_H
#define DATAINPUTCONFIGALIGN_H

#include <QFrame>

#include <LiLibrary/LiEasyLayout.h>
#include <LiLibrary/LiFixedToLayout.h>

namespace Ui
{
    class DataInputConfigAlign;
}

class DataInputConfigAlign : public QFrame
{
    Q_OBJECT

public:
    explicit DataInputConfigAlign(QWidget *parent = nullptr);
    ~DataInputConfigAlign();

    void Init(const QString& textOrig,const QString& textTran,const QList<QPair<int,int>>& partOrig,const QList<QPair<int,int>>& partTran,const QList<QPair<int,int>>& align);

protected:
    virtual void resizeEvent(QResizeEvent * event);

private:
    Ui::DataInputConfigAlign *ui;

    LiEasyLayout* l1;
};

#endif // DATAINPUTCONFIGALIGN_H
