#include "clientmanagerform.h"
#include "ui_clientmanagerform.h"

ClientManagerForm::ClientManagerForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientManagerForm)
{
    ui->setupUi(this);
}

ClientManagerForm::~ClientManagerForm()
{
    delete ui;
}
