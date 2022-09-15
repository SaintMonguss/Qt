#ifndef CALCULATORWIDGET_H
#define CALCULATORWIDGET_H

#include <QMainWindow>
#include <QLabel>

class CalculatorWidget : public QMainWindow
{
    Q_OBJECT
private:
    QLabel* answer;
public:
    CalculatorWidget(QWidget *parent = nullptr);
    ~CalculatorWidget();

signals:


public slots:
    void num1();
    void num2();
    void num3();
    void num4();
    void num5();
    void num6();
    void num7();
    void num8();
    void num9();
    void num0();
    void add_button();
    void divide_button();
    void multiple_button();
    void monguss();



};
#endif // CALCULATORWIDGET_H
