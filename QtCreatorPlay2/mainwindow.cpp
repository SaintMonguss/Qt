#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

#include <QTextEdit>
void MainWindow::on_actionNew_triggered()
{
    QTextEdit *textedit = new QTextEdit(this);
//    ui - > mdiArea
}

