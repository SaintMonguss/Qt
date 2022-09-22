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
#include <QFileDialog>
#include <QDebug>
#include <QColorDialog>
#include <QFontDialog>
#include <QPrinter>
#include <QPrintDialog>
#include <QKeyEvent>



QtEditor::QtEditor(QWidget *parent)
    : QMainWindow(parent)
{
    mdiArea = new QMdiArea(this);
    setCentralWidget(mdiArea);


//    QTextEdit *textedit = new QTextEdit(this);
//    mdiArea->addSubWindow(textedit);


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
    QAction *saveAsAct = makeAction(":/images/saveas.png","&SaveAs","Ctrl+a","save this documents another name",this, SLOT(saveAsFile()));
    fileMenu -> addAction(saveAsAct);
    QAction *printAction = makeAction(":/images/print.png","&Print","Ctrl+p","printing this documents", this, SLOT(printFile()));
    fileMenu -> addAction(printAction);
    fileMenu -> addSeparator();
    QAction *quitAct = makeAction(":/images/quit.png","&Quit","Ctrl+Q","bye bye",qApp, SLOT(quit()));
    fileMenu -> addAction(quitAct);

    //Edit 메뉴
    QMenu *editMenu = menubar -> addMenu("&Edit");
    QAction *undoAct = makeAction(":/images/undo.png", "&Undo", "Ctrl+z", "실행 취소", this , SLOT(editAction()));
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
    QAction *colorAction = makeAction(":/images/color.png", "&color", "Ctrl+t", "색상 선택", this, SLOT(setColor()));
    formatMenu-> addAction(colorAction);
    QAction *fontAction = makeAction(":/images/font.png", "&font", "Ctrl+o", "폰트 선택", this, SLOT(setFont()));
    formatMenu-> addAction(fontAction);

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
    fileToolBar -> addSeparator();
    fileToolBar -> addAction(printAction);

    //윈도우 메뉴
    windowMenu = menubar -> addMenu("&Window");
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
    //툴바를 다음줄로 내려줌
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

    // 첫 edit 화면 생성
    newFile();
}

QtEditor::~QtEditor()
{
}

void QtEditor::newFile()
{
    qDebug("새파일이 뽕 생김");
    QAction* windowAct = new QAction("New File",this);
    windowMenu -> addAction(windowAct);
    QTextEdit *textedit = new QTextEdit;
    connect(textedit, SIGNAL(destroyed(QObject*)), windowAct, SLOT(deleteLater()));
    connect(textedit, SIGNAL(cursorPositionChanged()),SLOT(setFontWidget()));
    mdiArea ->addSubWindow(textedit);
    windowHash[windowAct] = textedit;
    connect(windowAct, SIGNAL(triggered()),SLOT(selectWindow()));
    textedit -> show();
    textedit -> installEventFilter(this);
}

void QtEditor::openFile()
{
    QString filename = QFileDialog::getOpenFileName(this, "Select file to open",
                                                    ".", "Text File (*.txt *.html *.c *.cpp *.h");
    qDebug() << filename;
}
void QtEditor::saveFile()
{
    QString filename = QFileDialog::getSaveFileName(this, "Select file to save",
                                                    ".", "Text File (*.txt *.html *.c *.cpp *.h");
    qDebug() << filename;
}

void QtEditor::saveAsFile()
{
    QString filename = QFileDialog::getSaveFileName(this, "Select file to save as",
                                                    ".", "Text File (*.txt *.html *.c *.cpp *.h");
    qDebug() << filename;
}

void QtEditor::alignText()
{

}

void QtEditor::setColor()
{
    QTextEdit *textedit = (QTextEdit*)mdiArea ->currentSubWindow() -> widget();
    QColor color = QColorDialog::getColor(textedit->textColor(), this);
    if(color.isValid()) textedit -> setTextColor(color);
}

void QtEditor::setFont()
{
    bool ok;
    QTextEdit *textedit = (QTextEdit*)mdiArea -> currentSubWindow() ->widget();
    QFont font = QFontDialog::getFont(&ok, textedit -> currentFont(), this);
    if(ok) textedit -> setCurrentFont(font);
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

void QtEditor::printFile()
{
    QPrinter printer(QPrinter::HighResolution);
    printer.setFullPage(true);
    QPrintDialog printDialog(&printer, this);
    if(printDialog.exec() == QDialog::Accepted)
    {
        QTextEdit* textedit = (QTextEdit*) mdiArea -> currentSubWindow() -> widget();
        textedit -> print(&printer);
    }
}

void QtEditor::selectWindow()
{
    QTextEdit* textedit = (QTextEdit*)windowHash[(QAction*)sender()];
    textedit -> setFocus();
}

bool QtEditor::eventFilter(QObject *obj, QEvent *event)
{
    if(event -> type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        qDebug("key press %d", keyEvent -> key());
        return true;
    }
    else
        return QObject::eventFilter(obj, event);
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
