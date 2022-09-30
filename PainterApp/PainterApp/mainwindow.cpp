#include <QDoubleSpinBox>
#include <QStyle>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "scratchpad.h"
#include "memoalbum.h"
#include "imageslide.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_scratchPad = new ScratchPad(ui->tabWidget);
    ui->tabWidget->addTab(m_scratchPad, tr("Scratch Pad"));

    ui->actionSave->setIcon(style()->standardIcon(QStyle::SP_DialogSaveButton));
    ui->actionColor->setIcon(style()->standardIcon(QStyle::SP_DriveCDIcon));

    QDoubleSpinBox *spinBox = new QDoubleSpinBox(this);
    spinBox->setValue(1.0f);
    connect(spinBox, SIGNAL(valueChanged(double)), m_scratchPad, SLOT(setPaintSize(qreal)));
    ui->mainToolBar->addWidget(spinBox);

    m_memoAlbum = new MemoAlbum(ui->tabWidget);
    ui->tabWidget->addTab(m_memoAlbum, tr("Memo Album"));

    m_imageSlide = new ImageSlide(ui->tabWidget);
    ui->tabWidget->addTab(m_imageSlide, tr("Image Slide"));

    resize(1024, 800);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionSave_triggered()
{
    m_scratchPad->saveImage();
    m_memoAlbum->reloadImages();
    m_imageSlide->reloadImages();
}

void MainWindow::on_actionColor_triggered()
{
   m_scratchPad->setPaintColor();
}
