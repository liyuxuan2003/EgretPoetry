#ifndef RECITEWHOLEREVIEW_H
#define RECITEWHOLEREVIEW_H

#include <QDialog>

namespace Ui
{
    class ReciteWholeReview;
}

class ReciteWholeReview : public QDialog
{
    Q_OBJECT

public:
    explicit ReciteWholeReview(QWidget *parent = nullptr);
    ~ReciteWholeReview();

    void Init(int total,int right,int punctuation,int one,int two,int read,int all);
    int IsReview();

private slots:
    void on_pushButtonYesT_clicked();

    void on_pushButtonYesF_clicked();

    void on_pushButtonNo_clicked();

private:
    Ui::ReciteWholeReview *ui;

    int isReview;
};

#endif // RECITEWHOLEREVIEW_H
