#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "scratchpad.h"
#include <QDoubleSpinBox>
86
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_scratchPad = new ScratchPad(ui -> tabWidget);
    ui -> tabWidget -> addTab(m_scratchPad, tr("Scratch Pad"));

    QDoubleSpinBox *sizeSpinBox = new QDoubleSpinBox(this);
    connect(sizeSpinBox, SIGNAL(valueChanged(double)), m_scratchPad, SLOT(setPaintSize(qreal)));
    connect(ui->actionColor, SIGNAL(triggered(bool)), m_scratchPad, SLOT(setPaintColor()));
    ui -> toolBar -> setToolButtonStyle(Qt::ToolButtonIconOnly);
    ui -> toolBar -> addAction(ui -> actionSave);
    ui -> toolBar -> addAction(ui -> actionColor);
    ui -> toolBar -> addWidget(sizeSpinBox);


    resize(1024, 800);
}

MainWindow::~MainWindow()
{
    delete ui;
}

