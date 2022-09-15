#ifndef LCD_H
#define LCD_H

#include <QMainWindow>

class LCD : public QMainWindow
{
    Q_OBJECT

public:
    LCD(QWidget *parent = nullptr);
    ~LCD();
};
#endif // LCD_H
