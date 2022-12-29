#include "webbrower.h"
#include <QUrl>
#include <QMenu>
#include <QToolBar>
#include <QAction>
#include <QLineEdit>
#include <QWebEngineHistory>
#include <QApplication>
#include <QStatusBar>
#include "webbrower.h"

WebBrower::WebBrower(QWidget *parent)
    : QMainWindow(parent)
{
    resize(800, 600);
    webEngineView = new QWebEngineView(this);
    webEngineView -> setUrl(QUrl("about:blank"));
    lineEditURL = new QLineEdit(this);

    connect(lineEditURL, SIGNAL(returnPressed()), SLOT(goSlot()));
    QAction* actionOpen = new QAction("Open", this);
    connect(actionOpen, SIGNAL(triggered()), SLOT(quit()));
    QAction* actionQuit = new QAction("quit", this);
    connect(actionQuit, SIGNAL(triggered()), SLOT(goSlot()));

    QAction* actionGo = new QAction("해", this);
    connect(actionGo, SIGNAL(triggered()), SLOT(goSlot()));

    QAction* actionBackward = new QAction("뒤", this);
    connect(actionBackward, SIGNAL(triggered()), SLOT(goBackwardSlot()));
    QAction* actionForward = new QAction("앞", this);
    connect(actionForward, SIGNAL(triggered()), SLOT(goForwardSlot()));


    QAction* actionHome = new QAction("집가", this);
    connect(actionHome, SIGNAL(triggered()), SLOT(Home()));

    QAction* actionReload = new QAction("새로고쳐", this);
    connect(actionReload, SIGNAL(triggered()),webEngineView, SLOT(reload()));
    QAction* actionStop = new QAction("멈춰!", this);
    connect(actionStop, SIGNAL(triggered()), webEngineView, SLOT(stop()));

    QAction * actionAbout = new QAction("About", this);
    connect(actionAbout, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

    QMenuBar* menubar = menuBar();

    QMenu* menuFile = new QMenu("&File", menubar);





}

WebBrower::~WebBrower()
{
}

