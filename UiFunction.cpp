#include "UiFunction.h"

void SetButtonStatus(QPushButton* button,bool status)
{
    button->setEnabled(status);
    if(status==true)
        button->setStyleSheet("background-color:rgb(117,133,67); color:rgb(255,255,255)");
    if(status==false)
        button->setStyleSheet("background-color:rgb(106,106,106); color:rgb(255,255,255);");
}
