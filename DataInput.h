#ifndef DATAINPUT_H
#define DATAINPUT_H

#include <QFrame>

namespace Ui {
class DataInput;
}

class DataInput : public QFrame
{
    Q_OBJECT

public:
    explicit DataInput(QWidget *parent = nullptr);
    ~DataInput();

private:
    Ui::DataInput *ui;
};

#endif // DATAINPUT_H
