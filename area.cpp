#include "area.h"
#include <QTimerEvent>
Area::Area(QWidget *parent):QWidget(parent)
{
    setFixedSize(QSize(300,200)); // Установка фиксированного размера области рисования.
    // Создание объектов фигур.
    // Параметры:
    // X, Y — координаты центра,
    // Halflen — половина длины фигуры.
    myline=new MyLine(80,100,50);
    myrect=new MyRect(220,100,50);
    alpha=0;
}
void Area::showEvent(QShowEvent *)
{
    myTimer=startTimer(50); // создать таймер
    // возвращает его идентификатор
    // Таймер будет генерировать событие timerEvent()
    // каждые 50 миллисекунд.
    //Потом Qt автоматически вызывает timerEvent(QTimerEvent *event)
}
void Area::paintEvent(QPaintEvent *)
{
    // paintEvent вызывается Qt автоматически,
    // когда необходимо перерисовать виджет.
    QPainter painter(this);
    painter.setPen(Qt::red);
    myline->move(alpha,&painter);
    myrect->move(alpha*(-0.5),&painter); // Прямоугольник вращается в противоположную сторону,
}
void Area::timerEvent(QTimerEvent *event)
{
    // timerEvent вызывается Qt автоматически
    // при срабатывании любого таймера.
    if (event->timerId() == myTimer) // если наш таймер
    {
        alpha=alpha+0.2;// Постепенное изменение угла поворота.
        update(); // обновить внешний вид
        // Qt автоматически вызовет paintEvent().
    }
    else
        QWidget::timerEvent(event); // иначе передать для стандартной
    // Передача обработки стандартному обработчику QWidget,
    // если событие относится не к нашему таймеру.
}
void Area::hideEvent(QHideEvent *)
{
    // Метод вызывается, когда виджет скрывается.
    killTimer(myTimer); // уничтожить таймер
}
Area::~Area()
{
    // Освобождение динамически выделенной памяти.
    delete myline;
    delete myrect;
}
