#include "window.h"
#include <QVBoxLayout>
#include <QMessageBox>
Window::Window(QWidget *parent):QWidget(parent)
{
    setWindowTitle("Возведение в квадрат");// Установка заголовка окна

    frame = new QFrame(this); // Создание рамки для группировки элементов интерфейса
    frame->setFrameShadow(QFrame::Raised);
    frame->setFrameShape(QFrame::Panel);

    inputLabel = new QLabel("Введите число:",this);// Создание текстовой метки для поля ввода

    inputEdit = new QLineEdit(this); // Создание поля ввода числа
    // Установка валидатора
    inputEdit->setValidator(new QDoubleValidator(this)); // разрешается ввод только вещественных чисел

    outputLabel = new QLabel("Результат:",this);// Создание метки результата
    outputEdit = new QLineEdit(this); // Создание поля вывода результата
    // Поле только для чтения
    outputEdit->setReadOnly(true); // пользователь не может изменить результат вручную

    nextButton = new QPushButton("Следующее",this);// Создание кнопки перехода к следующему вычислению
    exitButton = new QPushButton("Выход",this);// Создание кнопки выхода из программы
    // компоновка приложения выполняется согласно рисунку 2
    QVBoxLayout *vLayout1 = new QVBoxLayout(frame); // Вертикальный layout внутри рамки
    // содержит поля ввода и вывода
    vLayout1->addWidget(inputLabel);
    vLayout1->addWidget(inputEdit);
    vLayout1->addWidget(outputLabel);
    vLayout1->addWidget(outputEdit);
    vLayout1->addStretch(); // Добавление растягивающегося пространства
    // прижимает элементы к верхней части окна
    // Вертикальный layout для кнопок
    QVBoxLayout *vLayout2 = new QVBoxLayout();
    // Добавление кнопок
    vLayout2->addWidget(nextButton);
    vLayout2->addWidget(exitButton);
    vLayout2->addStretch();
    // Главный горизонтальный layout окна
    QHBoxLayout *hLayout = new QHBoxLayout(this);
    hLayout->addWidget(frame);// Добавление рамки с полями
    hLayout->addLayout(vLayout2); // Добавление layout с кнопками
    begin(); // Выполнение начальной настройки интерфейса
    connect(exitButton,&QPushButton::clicked,
            this,&QWidget::close);
    connect(nextButton,&QPushButton::clicked,
            this,&Window::begin);
    connect(inputEdit,&QLineEdit::returnPressed,
            this,&Window::calc);
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
            QMessageBox msgBox(QMessageBox::Information,
                               "Возведение в квадрат.",
                               "Введено неверное значение.",
                               QMessageBox::Ok);
            msgBox.exec();
        }
    }
}
