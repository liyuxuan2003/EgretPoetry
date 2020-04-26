#ifndef TRANWORDREVIEW_H
#define TRANWORDREVIEW_H

#include <QDialog>

namespace Ui
{
    class TranWordReview;
}

class TranWordReview : public QDialog
{
    Q_OBJECT

public:
    explicit TranWordReview(QWidget *parent = nullptr);
    ~TranWordReview();

    void Init(int total,int right,int wrong);
    bool IsReview();

private slots:
    void on_pushButtonYes_clicked();

    void on_pushButtonNo_clicked();

private:
    Ui::TranWordReview *ui;

    bool isReview;
};

#endif // TRANWORDREVIEW_H
