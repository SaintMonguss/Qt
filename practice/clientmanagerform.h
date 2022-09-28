#ifndef CLIENTMANAGERFORM_H
#define CLIENTMANAGERFORM_H

#include <QWidget>

namespace Ui {
class ClientManagerForm;
}

class ClientManagerForm : public QWidget
{
    Q_OBJECT

public:
    explicit ClientManagerForm(QWidget *parent = nullptr);
    ~ClientManagerForm();

private:
    Ui::ClientManagerForm *ui;
};

#endif // CLIENTMANAGERFORM_H
