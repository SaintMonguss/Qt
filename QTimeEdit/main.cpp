#include "widget.h"

#include <QApplication>
#include <QTimeEdit>
#include <QDate>
#include <QDateEdit>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTimeEdit * timeEdit = new QTimeEdit(0);
    timeEdit -> setTime(QTime::currentTime());
    timeEdit -> show();

    QDateEdit* dateEdit = new QDateEdit(QDate::currentDate(), 0);
    dateEdit -> setCalendarPopup(true);
    dateEdit -> show();

    return a.exec();
}
