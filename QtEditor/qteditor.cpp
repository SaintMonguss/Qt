#include "qteditor.h"
#include <QTextEdit>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QMenuBar>
#include <QApplication>
#include <QToolBar>
#include <QFontComboBox>
#include <QDoubleSpinBox>
#include <QStatusBar>
#include <QLabel>
#include <QDockWidget>
#include <QMdiSubWindow>



QtEditor::QtEditor(QWidget *parent)
    : QMainWindow(parent)
{
    mdiArea = new QMdiArea(this);
    setCentralWidget(mdiArea);

#if 1
    QTextEdit *textedit = new QTextEdit(this);
    mdiArea->addSubWindow(textedit);
#else
    newFile();
#endif
    //독위젯
    QLabel* label = new QLabel("Dock Widget", this);
    QDockWidget *dock = new QDockWidget("Dock Widget", this);
    dock -> setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    addDockWidget(Qt::RightDockWidgetArea, dock);
    dock -> setWidget(label);

    QMenuBar *menubar = new QMenuBar(this);
    setMenuBar(menubar);

    // File 메뉴
    QMenu *fileMenu = menubar -> addMenu("&File");
    QAction *newAct = makeAction(":/images/new.png","&New","Ctrl+N","make new file",this, SLOT(newFile()));
    fileMenu -> addAction(newAct);
    QAction *openAct = makeAction(":/images/open.png","&Open","Ctrl+O", "open file", this, SLOT(openFile()));
    fileMenu -> addAction(openAct);
    QAction *saveAct = makeAction(":/images/save.png","&Save","Ctrl+S","save this documents",this, SLOT(saveFile()));
    fileMenu -> addAction(saveAct);
    fileMenu -> addSeparator();
    QAction *quitAct = makeAction(":/images/quit.png","&Quit","Ctrl+Q","bye bye",qApp, SLOT(quit()));
    fileMenu -> addAction(quitAct);

    //Edit 메뉴
    QMenu *editMenu = menubar -> addMenu("&Edit");
    QAction *undoAct = makeAction(":/images/undo.jpg", "&Undo", "Ctrl+z", "실행 취소", this , SLOT(editAction()));
    editMenu -> addAction(undoAct);
    QAction *redoAct = makeAction(":/images/redo.jpg", "&Redo", "Ctrl+Shift+z", "실행 취소를 취소", this, SLOT(editAction()));
    editMenu -> addAction(redoAct);
    editMenu -> addSeparator();
    QAction *copyAct = makeAction(":/images/copy.jpg", "&Copy", "Ctrl+c", "복사", this, SLOT(editAction()));
    editMenu -> addAction(copyAct);
    QAction *cutAct = makeAction(":/images/cut.jpg", "&Cut", "Ctrl+x", "잘라내기", this, SLOT(editAction(tr())));
    editMenu -> addAction(cutAct);
    QAction *pasteAct = makeAction(":/images/paste.jpg", "&Paste", "Ctrl+v", "부쳐빼기", this , SLOT(editAction()));
    editMenu -> addAction(pasteAct);
    editMenu -> addSeparator();
    QAction *zoomInAct = makeAction(":/images/zoomIn.jpg", "&zoomIn", "Ctrl+]", "줌 인", this , SLOT(editAction()));
    editMenu -> addAction(zoomInAct);
    QAction *zoomOutAct = makeAction(":/images/zoomOut.jpg", "&zoomOut", "Ctrl+[", "줌 아웃", this , SLOT(editAction()));
    editMenu -> addAction(zoomOutAct);

    //format 메뉴
    QMenu *formatMenu = menubar -> addMenu("&Format");
    // ->정렬메뉴
    QMenu *alignMenu = formatMenu -> addMenu("&align");
    QAction *alignLeft = alignMenu-> addAction("&Left");
    QAction *alignCenter = alignMenu-> addAction("&Center");
    QAction *alignRight = alignMenu-> addAction("&Right");


    //툴바
    QToolBar *fileToolBar = addToolBar("&File");
    fileToolBar -> setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    fileToolBar -> addAction(newAct);
    fileToolBar -> addSeparator();
    fileToolBar -> addAction(quitAct);

    //윈도우 메뉴
    QMenu *windowMenu = menubar -> addMenu("&Window");
    windowMenu -> addAction(fileToolBar -> toggleViewAction());
    windowMenu -> addAction(dock-> toggleViewAction());
    windowMenu -> addSeparator();
    QAction *nextAction = makeAction(":/images/next.png", "&Next", "Ctrl+=",
                                        "next", mdiArea, SLOT(activateNextSubWindow()));
    windowMenu -> addAction(nextAction);
    QAction *preivAction = makeAction(":/images/preiv.png", "&Preiv", "Ctrl+-",
                                        "preiv", mdiArea, SLOT(activatePreviousSubWindow()));
    windowMenu -> addAction(preivAction);
    QAction *cascadeAction = makeAction(":/images/cascade.png", "&Cascade", "Ctrl+5",
                                        "cascade", mdiArea, SLOT(cascadeSubWindows()));
    windowMenu -> addAction(cascadeAction);
    QAction *tileAction = makeAction(":/images/tile.png", "&Tile", "Ctrl+4",
                                        "tile", mdiArea, SLOT(tileSubWindows()));
    windowMenu -> addAction(tileAction);

    //글꼴 크기, 글꼴 설정
    QFontComboBox* fontComboBox = new QFontComboBox(this);
    connect(fontComboBox, SIGNAL(currentFontChanged(QFont)), SLOT(setTextFont(QFont)));
    QDoubleSpinBox* sizeSpinBox = new QDoubleSpinBox(this);
    connect(sizeSpinBox, SIGNAL(valueChanged(double)), SLOT(setTextSize(qreal)));

    addToolBarBreak();
    QToolBar *formatToolbar = addToolBar("&Format");

    formatToolbar -> addSeparator();
    formatToolbar -> addWidget(fontComboBox);
    formatToolbar -> addWidget(sizeSpinBox);

    //상태 바
    QStatusBar* statusbar = statusBar();
    QLabel* statusLabel = new QLabel("Qt Editor", statusbar);
    statusLabel-> setObjectName("StatusLabel");
    statusbar-> addPermanentWidget(statusLabel);
    statusbar -> showMessage("started", 1500);
}

QtEditor::~QtEditor()
{
}

void QtEditor::newFile()
{
    qDebug("새파일이 뽕 생김");
    QTextEdit *textedit = new QTextEdit;
    mdiArea ->addSubWindow(textedit);
    textedit -> show();
}

void QtEditor::openFile()
{
    qDebug("파일을 샥 열음");
}
void QtEditor::saveFile()
{
    qDebug("파일을 사각사각 저장함");
}

void QtEditor::alignText()
{

}

// 메뉴 추가 함수
QAction *QtEditor::makeAction(QString icon, QString name, QString shortCut,\
                    QString toolTip, QObject* recv, const char* slot)
{
    QAction *act = new QAction(name, this);
    if(icon.length())
        act->setIcon(QIcon(icon));
    act->setShortcut(shortCut);
    act->setStatusTip(toolTip);
    connect(act,SIGNAL(triggered()), recv, slot);
    return act;
}

void QtEditor::editAction()
{
    QMdiSubWindow *subWindow = mdiArea->currentSubWindow();
    QTextEdit *textedit = dynamic_cast<QTextEdit*>(subWindow->widget());
    QAction *action = dynamic_cast<QAction*> (sender());
    if(action ->text() == tr("&Undo")) textedit -> undo();
    else if (action ->text() == tr("&Redo")) textedit -> redo();
    else if(action ->text() == tr("&Copy")) textedit -> copy();
    else if(action ->text() == tr("&Cut")) textedit -> cut();
    else if(action ->text() == tr("&Paste")) textedit -> paste();
    else if(action ->text() == tr("&zoomIn")) textedit -> zoomIn();
    else if(action ->text() == tr("&zoomOut")) textedit -> zoomOut();
}

void QtEditor::setTextFont(QFont font)
{
    QTextEdit *textedit = (QTextEdit*)mdiArea->currentSubWindow()->widget();
    textedit -> setCurrentFont(font);
}

void QtEditor::setTextSize(qreal size)
{
    QTextEdit *textedit = (QTextEdit*)mdiArea->currentSubWindow()->widget();
    textedit ->setFontPointSize(size);
}
