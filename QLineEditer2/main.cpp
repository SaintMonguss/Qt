#include "widget.h"

#include <QApplication>
#include <QLineEdit>
#include <QCompleter>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QLineEdit *lineEdit = new QLineEdit();

    QStringList CompletionList;
    CompletionList << "Bryan" << "Bart" << "Kelvin" << "Beth" << "Bard" << "Kelly";
    QCompleter *StringCompleter = new QCompleter(CompletionList, w);
    StringCompleter -> setCaseSensitivity(Qt::CaseInsensitive);

    //lineEdit -> setEchoMode(QLineEdit::Password);
    lineEdit-> setInputMask("099");
    lineEdit -> setPlaceholderText("input the number");
    lineEdit -> show();

    return a.exec();
}
