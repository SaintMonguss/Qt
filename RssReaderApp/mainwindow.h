#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include <QNetworkReply>
#include <QListView>
#include <QProgressBar>
#include <QWebEngineView>
#include <QStandardItemModel>

/* ~ 중간 표시 생략 ~ */

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void openRssFeed( );
    void replyFinished(QNetworkReply*);
    void listViewDoubleClicked(const QModelIndex & index);
    void downloadProgress(qint64 bytes, qint64 bytesTotal);

private:
    QComboBox *combo;
    QNetworkAccessManager *manager;
    QWebEngineView* wv;
    QListView* tv;
    QStandardItemModel* model;
    QProgressBar* progress;
};

class ListView : public QListView {
    Q_OBJECT

protected:
    void keyPressEvent(QKeyEvent *event) override;
};

#endif // MAINWINDOW_H
