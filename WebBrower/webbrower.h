#ifndef WEBBROWER_H
#define WEBBROWER_H

#include <QMainWindow>
#include <QWebEngineView>

class QLineEdit;

class WebBrower : public QMainWindow
{
    Q_OBJECT

public:
    WebBrower(QWidget *parent = nullptr);
    ~WebBrower();

private:
    QLineEdit *lineEditURL;
    QWebEngineView *webEngineView;

public slots:
    void goSlot();
    void goBackwardSlot();
    void goForwardSlot();
    void goHomeSlot();
};
#endif // WEBBROWER_H
