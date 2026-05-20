#ifndef COUNTER_H
#define COUNTER_H
#include <QWidget>
#include <QLineEdit>
class Counter: public QLineEdit
{
    Q_OBJECT
public:
    Counter(const QString & contents, QWidget *parent=0): QLineEdit(contents,parent){}
signals:
    void tick_signal();
public slots:
    void add_one()
    {
        QString str=text();
        int r=str.toInt();
        if (r!=0 && r%5 ==0) emit tick_signal();
        r++;
        str.setNum(r);
        setText(str);
    }
};

#endif // COUNTER_H
