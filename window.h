#ifndef WINDOW_H
#define WINDOW_H
#include <QWidget>
#include <QPushButton>
#include "area.h"
class Window : public QWidget
{
    Q_OBJECT
protected:
    Area* area = nullptr;; // область отображения рисунка
    QPushButton* btn = nullptr;;
public:
    Window();
};
#endif // WINDOW_H
