#include "window.h"
#include <float.h>
#include <math.h>
#include <QVBoxLayout>
#include <QMessageBox>
Window::Window(QWidget *parent):QWidget(parent)
{
    m_maxAbsInputValue = sqrt(FLT_MAX);
    setWindowTitle("Возведение в квадрат");// Установка заголовка окна

    frame = new QFrame(this); // Создание рамки для группировки элементов интерфейса
    if (!frame)
    {
        QMessageBox::critical(this,"Ошибка","Не удалось создать QFrame.");
        return;
    }
    frame->setFrameShadow(QFrame::Raised);
    frame->setFrameShape(QFrame::Panel);

    inputLabel = new QLabel("Введите число:",this);// Создание текстовой метки для поля ввода
    if (!inputLabel)
    {
        QMessageBox::critical(this,"Ошибка","Не удалось создать метку ввода.");
        return;
    }
    inputEdit = new QLineEdit(this); // Создание поля ввода числа
    if (!inputEdit)
    {
        QMessageBox::critical(this,"Ошибка","Не удалось создать поле ввода.");
        return;
    }
    // Установка валидатора
    QDoubleValidator *validator = new QDoubleValidator(this);
    if (!validator)
    {
        QMessageBox::critical(this,"Ошибка","Не удалось создать валидатор.");
        return;
    }
    inputEdit->setValidator(validator);
    outputLabel = new QLabel("Результат:",this);// Создание метки результата
    if (!outputLabel)
    {
        QMessageBox::critical(this,"Ошибка","Не удалось создать метку ввода.");
        return;
    }
    outputEdit = new QLineEdit(this); // Создание поля вывода результата
    if (!outputEdit)
    {
        QMessageBox::critical(this,"Ошибка","Не удалось создать поле результата.");
        return;
    }
    // Поле только для чтения
    outputEdit->setReadOnly(true); // пользователь не может изменить результат вручную

    nextButton = new QPushButton("Следующее",this);// Создание кнопки перехода к следующему вычислению
    if (!nextButton)
    {
        QMessageBox::critical(this,"Ошибка","Не удалось создать кнопку Следующее.");
        return;
    }
    exitButton = new QPushButton("Выход",this);// Создание кнопки выхода из программы
    if (!exitButton)
    {
        QMessageBox::critical(this,"Ошибка","Не удалось создать кнопку Выход.");
        return;
    }
    // компоновка приложения выполняется согласно рисунку 2
    QVBoxLayout *vLayout1 = new QVBoxLayout(frame); // Вертикальный layout внутри рамки
    if (!vLayout1)
    {
        QMessageBox::critical(this,"Ошибка","Не удалось создать компоновщик vLayout1.");
        return;
    }
    // содержит поля ввода и вывода
    vLayout1->addWidget(inputLabel);
    vLayout1->addWidget(inputEdit);
    vLayout1->addWidget(outputLabel);
    vLayout1->addWidget(outputEdit);
    vLayout1->addStretch(); // Добавление растягивающегося пространства
    // прижимает элементы к верхней части окна
    // Вертикальный layout для кнопок
    QVBoxLayout *vLayout2 = new QVBoxLayout();
    if (!vLayout2)
    {
        QMessageBox::critical(this,"Ошибка","Не удалось создать компоновщик vLayout2.");
        return;
    }
    // Добавление кнопок
    vLayout2->addWidget(nextButton);
    vLayout2->addWidget(exitButton);
    vLayout2->addStretch();
    // Главный горизонтальный layout окна
    QHBoxLayout *hLayout = new QHBoxLayout(this);
    if (!hLayout)
    {
        QMessageBox::critical(this,"Ошибка","Не удалось создать главный компоновщик.");
        return;
    }
    hLayout->addWidget(frame);// Добавление рамки с полями
    hLayout->addLayout(vLayout2); // Добавление layout с кнопками
    begin(); // Выполнение начальной настройки интерфейса
    connect(exitButton,&QPushButton::clicked,this,&QWidget::close);
    connect(nextButton,&QPushButton::clicked,this,&Window::begin);
    connect(inputEdit,&QLineEdit::returnPressed,this,&Window::calc);
}

void Window::begin()
{
    inputEdit->clear(); // Очистка поля ввода
    nextButton->setEnabled(false); // "Следующее" недоступна
    nextButton->setDefault(false); //кнопка, которая нажимается автоматически при нажатии клавиши Enter
    inputEdit->setEnabled(true); // Разрешение ввода нового значения
    outputLabel->setVisible(false); // Скрытие элементов результата
    outputEdit->setVisible(false); // Скрытие элементов результата
    outputEdit->setEnabled(false);  // Блокировка редактирования поля результата
    inputEdit->setFocus(); // Установка фокуса ввода на поле inputEdit
}

void Window::calc()
{
    bool Ok=false; // Флаг успешности преобразования строки в число
    double r;
    QString str=inputEdit->text();
    double a=str.toDouble(&Ok);
    if (Ok)
    {
        if(abs(a) > m_maxAbsInputValue) {
            QMessageBox msgBox(QMessageBox::Information,"Возведение в квадрат",
                               "Введено слишком большое число",QMessageBox::Ok);
            msgBox.exec();
            return;
        }
        r=a*a;
        str.setNum(r);
        outputEdit->setText(str); // Вывод результата в поле outputEdit
        inputEdit->setEnabled(false);// Блокировка повторного ввода
        // Отображение элементов результата
        outputLabel->setVisible(true);
        outputEdit->setVisible(true);
        // Кнопка "Следующее" становится активной
        nextButton->setDefault(true);
        nextButton->setEnabled(true);
        nextButton->setFocus();// Передача фокуса кнопке
    }
    else
    {
        if (!str.isEmpty())
        {
            QMessageBox msgBox(QMessageBox::Information,"Возведение в квадрат.",
                               "Введено неверное значение.",QMessageBox::Ok);
            msgBox.exec();
        }
    }
}
