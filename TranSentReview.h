#ifndef TRANSENTREVIEW_H
#define TRANSENTREVIEW_H

#include <QDialog>

namespace Ui
{
    class TranSentReview;
}

class TranSentReview : public QDialog
{
    Q_OBJECT

public:
    explicit TranSentReview(QWidget *parent = nullptr);
    ~TranSentReview();

    void Init(int total,int right,int wrong);
    bool IsReview();

private slots:
    void on_pushButtonYes_clicked();

    void on_pushButtonNo_clicked();

private:
    Ui::TranSentReview *ui;

    bool isReview;
};

#endif // TRANSENTREVIEW_H
