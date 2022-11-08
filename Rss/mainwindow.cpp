#include "mainwindow.h"

#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QToolBar* toolbar = addToolBar(tr("Open"));

    combo = new QComboBox;
    combo -> setEditable(true);
    combo -> setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    connect(combo, SIGNAL(activated(int)), SLOT(openRssFeed()));
    toolbar -> addWidget(combo);

    QAction *act = new QAction(tr("Open RSS Feed"), this);
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            SLOT(replyFinished(QNetworkReply*)));
}

MainWindow::~MainWindow()
{
}

void MainWindow::openRssFeed()
{
    manager -> get(QNetworkRequest(QUrl(combo -> currentText())));
}

void MainWindow::replyFinished(QNetworkReply* netReply)
{
    QString str(netReply -> readAll());
    qDebug("%s", qPrintable(str));
}
