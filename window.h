#ifndef WINDOW_H
#define WINDOW_H
#include <QWidget>
#include <QPushButton>
#include "area.h"
class Window : public QWidget
{
    Q_OBJECT
protected:
    QTextCodec *codec;
    Area * area; // область отображения рисунка
    QPushButton * btn;
public:
    Window(QWidget *parent = nullptr);
};
#endif // WINDOW_H
