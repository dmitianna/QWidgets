#include "window.h"
#include <QLayout>

Window::Window()
{
    this->setWindowTitle("Обработка событий");
    area = new Area(this);
    btn = new QPushButton("Завершить",this);
    // Создание вертикального layout.
    // Элементы будут располагаться сверху вниз.
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(area);
    layout->addWidget(btn);
    connect(btn, &QPushButton::clicked,this,&QWidget::close);
};
