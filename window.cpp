#include "window.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
Window::Window(QWidget *parent):QWidget(parent)
{
    this->setWindowTitle("Счетчик");
    label1 = new QLabel("Cчет по 1",this);
    if (!label1)
    {
        QMessageBox::critical(this,"Ошибка","QLabel label1 - ошибка создания.");
        return;
    }
    label2 = new QLabel("Cчет по 5",this);
    if (!label2)
    {
        QMessageBox::critical(this,"Ошибка","QLabel label2 - ошибка создания.");
        return;
    }
    edit1 = new Counter("0",this);
    if (!edit1)
    {
        QMessageBox::critical(this,"Ошибка","Counter edit1 - ошибка создания.");
        return;
    }
    edit1->setReadOnly(true);
    edit2 = new Counter("0",this);
    if (!edit2)
    {
        QMessageBox::critical(this,"Ошибка","Counter edit2 - ошибка создания.");
        return;
    }
    edit2->setReadOnly(true);
    calcbutton=new QPushButton("+1",this);
    if (!calcbutton)
    {
        QMessageBox::critical(this,"Ошибка","QPushButton calcbutton - ошибка создания.");
        return;
    }
    exitbutton=new QPushButton("Выход",this);
    if (!exitbutton)
    {
        QMessageBox::critical(this,"Ошибка","QPushButton exitbutton - ошибка создания.");
        return;
    }
    QHBoxLayout *layout1 = new QHBoxLayout();
    if (!layout1)
    {
        QMessageBox::critical(this,"Ошибка", "QHBoxLayout layout1 - ошибка создания.");
        return;
    }
    layout1->addWidget(label1);
    layout1->addWidget(label2);
    QHBoxLayout *layout2 = new QHBoxLayout();
    if (!layout2)
    {
        QMessageBox::critical(this,"Ошибка","QHBoxLayout layout2 - ошибка создания.");
        return;
    }
    layout2->addWidget(edit1);
    layout2->addWidget(edit2);

    QHBoxLayout *layout3 = new QHBoxLayout();
    if (!layout3)
    {
        QMessageBox::critical(this,"Ошибка","QHBoxLayout layout3 - ошибка создания.");
        return;
    }
    layout3->addWidget(calcbutton);
    layout3->addWidget(exitbutton);

    QVBoxLayout *layout4 = new QVBoxLayout(this);
    if (!layout4)
    {
        QMessageBox::critical(this,"Ошибка","QVBoxLayout layout4 - ошибка создания.");
        return;
    }
    layout4->addLayout(layout1);
    layout4->addLayout(layout2);
    layout4->addLayout(layout3);
    // связь сигнала нажатия кнопки и слота закрытия окна
    connect(calcbutton,&QPushButton::clicked,edit1,&Counter::add_one);
    connect(edit1,&Counter::tick_signal,edit2,&Counter::add_one);
    connect(exitbutton,&QPushButton::clicked,this,&QWidget::close);
}
