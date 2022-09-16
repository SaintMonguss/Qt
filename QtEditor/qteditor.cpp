#include "qteditor.h"
#include <QTextEdit>
#include <QMenuBar>
#include <QApplication>
#include <QToolBar>
#include <QFontComboBox>
#include <QDoubleSpinBox>
#include <QStatusBar>
#include <QLabel>



QtEditor::QtEditor(QWidget *parent)
    : QMainWindow(parent)
{
    textedit = new QTextEdit(this);
    setCentralWidget(textedit);

    QMenuBar *menubar = new QMenuBar(this);
    setMenuBar(menubar);

    // File 메뉴
    QMenu *fileMenu = menubar -> addMenu("&File");
    QAction *newAct = makeAction("new.png","&New","Ctrl+N","make new file",this, SLOT(newFile()));
    fileMenu -> addAction(newAct);
    QAction *openAct = makeAction("open.png","&Open","Ctrl+O", "open file", this, SLOT(openFile()));
    fileMenu -> addAction(openAct);
    QAction *saveAct = makeAction("save.png","&Save","Ctrl+S","save this documents",this, SLOT(saveFile()));
    fileMenu -> addAction(saveAct);
    fileMenu -> addSeparator();
    QAction *quitAct = makeAction("quit.png","&Quit","Ctrl+Q","bye bye",qApp, SLOT(quit()));
    fileMenu -> addAction(quitAct);

    //Edit 메뉴
    QMenu *editMenu = menubar -> addMenu("&Edit");
    QAction *undoAct = makeAction("undo.jpg", "&Undo", "Ctrl+z", "실행 취소", textedit, SLOT(undo()));
    editMenu -> addAction(undoAct);
    QAction *redoAct = makeAction("redo.jpg", "&Redo", "Ctrl+Shift+z", "실행 취소를 취소", textedit, SLOT(redo()));
    editMenu -> addAction(redoAct);
    editMenu -> addSeparator();
    QAction *copyAct = makeAction("copy.jpg", "&Copy", "Ctrl+c", "복사", textedit, SLOT(copy()));
    editMenu -> addAction(copyAct);
    QAction *cutAct = makeAction("cut.jpg", "&Cut", "Ctrl+x", "잘라내기", textedit, SLOT(cut()));
    editMenu -> addAction(cutAct);
    QAction *pasteAct = makeAction("paste.jpg", "&Paste", "Ctrl+v", "부쳐빼기", textedit, SLOT(paste()));
    editMenu -> addAction(pasteAct);
    editMenu -> addSeparator();
    QAction *zoomInAct = makeAction("zoomIn.jpg", "&zoomIn", "Ctrl+]", "줌 인", textedit, SLOT(zoomIn()));
    editMenu -> addAction(zoomInAct);
    QAction *zoomOutAct = makeAction("zoomOut.jpg", "&zoomOut", "Ctrl+[", "줌 아웃", textedit, SLOT(zoomOut()));
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

    //글꼴 크기, 글꼴 설정
    QFontComboBox* fontComboBox = new QFontComboBox(this);
    connect(fontComboBox, SIGNAL(currentFontChanged(QFont)), textedit, SLOT(setCurrentFont(QFont)));
    QDoubleSpinBox* sizeSpinBox = new QDoubleSpinBox(this);
    connect(sizeSpinBox, SIGNAL(valueChanged(double)),textedit, SLOT(setFontPointSize(qreal)));

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
    QAction *action =qobject_cast<QAction*>
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
