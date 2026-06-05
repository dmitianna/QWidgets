#include "window.h"
#include <QLayout>
#include <QMessageBox>
Window::Window()
{
    this->setWindowTitle("Обработка событий");
    area = new Area(this);
    if (!area)
    {
        QMessageBox::critical(this,"Ошибка","Area - ошибка создания.");
        return;
    }
    btn = new QPushButton("Завершить",this);
    if (!btn)
    {
        QMessageBox::critical(this,"Ошибка","QPushButton btn - ошибка создания.");
        return;
    }
    // Создание вертикального layout.
    // Элементы будут располагаться сверху вниз.
    QVBoxLayout *layout = new QVBoxLayout(this);
    if (!layout)
    {
        QMessageBox::critical(this,"Ошибка","QVBoxLayout - ошибка создания.");
        return;
    }
    layout->addWidget(area);
    layout->addWidget(btn);
    connect(btn, &QPushButton::clicked,this,&QWidget::close);
};
