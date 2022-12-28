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
#include "qteditor.h"
#include <QApplication>
#include <QTextEdit>
#include <QMenuBar>
//예외처리 필요

#include <QMenu>
#include <QAction>
#include <QToolBar>
#include <QFontComboBox>
#include <QDoubleSpinBox>
#include <QStatusBar>
#include <QLabel>
#include <QDockWidget>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>
#include <QColorDialog>
#include <QFontDialog>
#include <QPrinter>
#include <QPrintDialog>
#include <QHash>
#include <QFile>
#include <QFileInfo>
#include <QKeyEvent>
#include <QDebug>

QtEditor::QtEditor(QWidget *parent)
    : QMainWindow(parent)
{
//MDI Area 생성
    mdiArea = new QMdiArea(this);
    setCentralWidget(mdiArea);

//메인메뉴바 생성
    QMenuBar* menubar = new QMenuBar(this);
    setMenuBar(menubar);

//'FILE'메뉴 및 액션 생성
    QMenu* fileMenu = menubar->addMenu("&File");
    QAction* newAct = makeAction("new.png", tr("&New"),tr("Ctrl+N"), tr("Make new file"), this, SLOT(newFile()));
    QAction* openAct = makeAction("open.png",tr("&Open"),tr("Ctrl+O"), tr("Open new file"), this, SLOT(openFile()));
    QAction* saveAct = makeAction("save.png", tr("&Save"), tr("Ctrl+S"), tr("Save this file"), this, SLOT(saveFile()));
    QAction* saveAsAct = makeAction("saveas.png", tr("&Save As"), QKeySequence::SaveAs, tr("Save this file"), this, SLOT(saveAsFile()));
    QAction* printAct = makeAction("print.png", tr("&Print"), tr("Ctrl+P"), tr("Print"), this, SLOT(printFile()));
    QAction* quitAct = makeAction("quit.png", tr("&Quit"),tr("Ctrl+Q"), tr("Quit this program"), qApp, SLOT(quit()));

//'FILE'메뉴 액션 추가
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addSeparator();
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsAct);
    fileMenu->addSeparator();
    fileMenu->addAction(printAct);
    fileMenu->addSeparator();
    fileMenu->addAction(quitAct);

//'FileToolBar'메뉴 및 툴바 생성
    QMenu* toolBarMenu = menubar->addMenu(tr("&ToolBar"));
    QToolBar* fileToolBar = addToolBar(tr("&File"));
    fileToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

//'FileToolBar'메뉴 액션 추가 (+토글액션)
    toolBarMenu->addAction(fileToolBar->toggleViewAction());
    fileToolBar->addAction(newAct);
    fileToolBar->addAction(openAct);
    fileToolBar->addSeparator();
    fileToolBar->addAction(saveAct);
    fileToolBar->addAction(saveAsAct);
    fileToolBar->addSeparator();
    fileToolBar->addAction(printAct);
    fileToolBar->addSeparator();
    fileToolBar->addAction(quitAct);

//QStatusBar 클래스
    QStatusBar* statusbar = statusBar();
    QLabel* statusLabel = new QLabel(tr("Qt Editor"), statusbar);
    statusLabel->setObjectName("Status Label");
    statusbar->addPermanentWidget(statusLabel);
    statusbar->showMessage("started",1500);

//'Edit'메뉴 및 액션 생성
    QMenu* edit = menubar->addMenu(tr("&Edit"));
    QAction* clear= makeAction("clear.png",tr("&Clear"), tr("Ctrl+d"),
                               tr("UNDO!"), this, SLOT(clear()));
    QAction* undo = makeAction("undo.png",tr("&Undo"), tr("Ctrl+z"),
                               tr("UNDO!"), this, SLOT(undo()));
    QAction* redo = makeAction("redo.png",tr("&Redo"), QKeySequence::Redo,
                               tr("REDO!"), this, SLOT(redo()));
    QAction* copy = makeAction("",tr("&Copy"), QKeySequence::Copy,
                               tr("Copy"), this, SLOT(copy()));
    QAction* cut = makeAction("",tr("&Cut"), QKeySequence::Cut,
                              tr("Cut"), this, SLOT(cut()));
    QAction* paste = makeAction("",tr("&Paste"), QKeySequence::Paste,
                                tr("Paste"), this, SLOT(paste()));
    QAction* zoomIn = makeAction("",tr("&zoomIn"), QKeySequence::ZoomIn,
                                 tr("zoomIn"), this, SLOT(zoomIn()));
    QAction* zoomOut = makeAction("",tr("&zoomOut"), QKeySequence::ZoomOut,
                                  tr("zoomOut"), this, SLOT(zoomOut()));

//'Edit' 액션 추가
    edit->addAction(undo);
    edit->addAction(redo);
    edit->addSeparator();
    edit->addAction(copy);
    edit->addAction(cut);
    edit->addAction(paste);
    edit->addSeparator();
    edit->addAction(zoomIn);
    edit->addAction(zoomOut);
    edit->addSeparator();
    edit->addAction(clear);

//'EditToolBar'메뉴 및 툴바 생성
    addToolBarBreak();
    QToolBar* editToolBar = addToolBar(tr("&Edit"));
    fileToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

//'EditToolBar'메뉴 액션 추가 (+토글액션)
    toolBarMenu->addAction(editToolBar->toggleViewAction());
    editToolBar->addAction(undo);
    editToolBar->addAction(redo);
    editToolBar->addSeparator();
    editToolBar->addAction(copy);
    editToolBar->addAction(cut);
    editToolBar->addAction(paste);
    editToolBar->addSeparator();
    editToolBar->addAction(zoomIn);
    editToolBar->addAction(zoomOut);
    editToolBar->addSeparator();
    editToolBar->addAction(clear);

//format 메뉴
    QMenu* formatMenu = menubar->addMenu(tr("&Format"));
    QAction* color = new QAction(tr("&Color"), this);
    QAction* font = new QAction(tr("&font"), this);
    QMenu* alignMenu = new QMenu(tr("&Align"),this);
    QAction* center = new QAction(tr("&Center"), this);
    QAction* left = new QAction(tr("&Left"), this);
    QAction* right = new QAction(tr("&Right"), this);
    QAction* justify = new QAction(tr("&Justify"), this);
    formatMenu->addAction(color);
    formatMenu->addAction(font);
    formatMenu->addMenu(alignMenu);
    alignMenu->addAction(center);
    alignMenu->addAction(left);
    alignMenu->addAction(right);
    alignMenu->addAction(justify);

    connect(center, SIGNAL(triggered()), SLOT(alignText()));
    connect(left, SIGNAL(triggered()), SLOT(alignText()));
    connect(right, SIGNAL(triggered()), SLOT(alignText()));
    connect(justify, SIGNAL(triggered()), SLOT(alignText()));
    connect(color, SIGNAL(triggered()), SLOT(setColor()));
    connect(font, SIGNAL(triggered()), SLOT(setFont()));

//ToolBar에 위젯 추가
//    QFontComboBox* fontComboBox = new QFontComboBox(this);
//    connect(fontComboBox, SIGNAL(currentFontChanged(QFont)), textEdit, SLOT(setCurrentFont(QFont)));
//    QDoubleSpinBox* sizeSpinBox = new QDoubleSpinBox(this);
//    connect(sizeSpinBox, SIGNAL(valueChanged(double)), textEdit, SLOT(setFontPointSize(qreal)));

//    addToolBarBreak();        //툴바를 한 열 내리는 함수

//    QToolBar* formatToolbar = addToolBar("&Format");
//    formatToolbar->addSeparator();
//    formatToolbar->addWidget(fontComboBox);
//    formatToolbar->addWidget(sizeSpinBox);

//QDockWidget
    QLabel* label = new QLabel(tr("Dock Widget"),this);
    QDockWidget* dock = new QDockWidget(tr("Dock Widgettttt"),this);
    //붙일 수 있는 곳 선택 (왼쪽, 오른쪽)
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    //add(초기 위치 설정
    addDockWidget(Qt::RightDockWidgetArea,dock);
    dock->setWidget(label);     //여러 개의 위젯 붙이려면, 사용자 정의 위젯을 만들어서 한번에 올리기
    //formatToolbar->addAction(dock->toggleViewAction());

//QMessageBox 클래스
    QMenu* help = menubar->addMenu(tr("&Help"));
    QAction* about = help->addAction(tr("&About"));
    QAction* aboutqt = help->addAction(tr("&Aboutqqqqq"));
    connect(about, SIGNAL(triggered()), this, SLOT(aboutBox()));
    connect(aboutqt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

//Window메뉴
    window = menubar->addMenu(tr("&Window"));
    QAction* nextWindow = makeAction("", tr("&Next Window"),
                                     "Ctrl+]", tr("Next Window"), mdiArea, SLOT(activateNextSubWindow()));
    QAction* prevWindow = makeAction("", tr("&Prev Window"),
                                     "Ctrl+[", tr("Prev Window"), mdiArea, SLOT(activatePreviousSubWindow()));
    QAction* cascadeWindow = makeAction("", tr("&Cascade"),
                                     "", tr("Cascade"), mdiArea, SLOT(cascadeSubWindows()));
    QAction* closeActWindow = makeAction("", tr("&CloseAct"),
                                     "", tr("CloseAct"), mdiArea, SLOT(closeActiveSubWindow()));
    QAction* closeAllWindow = makeAction("", tr("&CloseAll"),
                                     "", tr("CloseAll"), mdiArea, SLOT(closeAllSubWindows()));
    QAction* tileWindow = makeAction("", tr("&CloseAct"),
                                     "", tr("CloseAct"), mdiArea, SLOT(tileSubWindows()));
    window->addAction(nextWindow);
    window->addAction(prevWindow);
    window->addSeparator();
    window->addAction(cascadeWindow);
    window->addAction(closeActWindow);
    window->addAction(closeAllWindow);
    window->addAction(tileWindow);
    window->addSeparator();

////초기 파일 생성
//#if 0
//    QTextEdit* textEdit = new QTextEdit(this);
//    mdiArea->addSubWindow(textEdit);
//#else
//    newFile();
//#endif
}

QtEditor::~QtEditor()
{
}

void QtEditor::newFile()
{
    qDebug("Make New File");
    QTextEdit* textedit = new QTextEdit;
    mdiArea->addSubWindow(textedit);
    QAction* windowAct = new QAction(tr("New File"), this);
    window->addAction(windowAct);
    windowHash[windowAct] = textedit;
    connect(windowAct, SIGNAL(triggered()), SLOT(selectWindow()));
    connect(textedit, SIGNAL(destroyed(QObject*)), windowAct, SLOT(deleteLater()));
    connect(textedit, SIGNAL(destroyed(QObject*)), SLOT(closeWindow()));
    textedit->installEventFilter(this);
    textedit->show();
}

void QtEditor::openFile()
{
    qDebug("open File");
    QString filename = QFileDialog::getOpenFileName(this, tr("Select file to open"),
                                             ".","Text File(*.txt *.html *.c *.cpp *.h)");
    qDebug() << filename;

    QFileInfo fileInfo(filename);
    if(fileInfo.isReadable()){
        QFile* file = new QFile(filename);
        file->open(QIODevice::ReadOnly);
        QByteArray msg = file->readAll();
        file->close();
        delete file;
        QTextEdit* textedit = new QTextEdit(this);
        textedit->setWindowTitle(filename);

        if(fileInfo.suffix() == "htm" || fileInfo.suffix() == "html")
            textedit->setHtml(msg);
        else
            textedit->setPlainText(msg);

        mdiArea->addSubWindow(textedit);
        textedit->show();

        QAction* windowAct = new QAction(filename, this);
        window->addAction(windowAct);
        windowHash[windowAct] = textedit;
        connect(windowAct, SIGNAL(triggered()), SLOT(selectWindow()));
        connect(textedit, SIGNAL(destroyed(QObject*)), windowAct, SLOT(deleteLater()));
        connect(textedit, SIGNAL(destroyed(QObject*)), SLOT(closeWindow()));

    } else{
        QMessageBox::warning(this, tr("Error"), tr("Can't Read this file"),
                             QMessageBox::Ok);
    }
}

void QtEditor::saveFile()
{
    qDebug("save File");
    QTextEdit* textedit = (QTextEdit*)mdiArea->currentSubWindow()->widget();
    QString filename = textedit->windowTitle();
    if(!filename.length()){
        filename = QFileDialog::getSaveFileName(this, tr("Select file to save"),
                                                ".","Text File(*.txt *.html *.c *.cpp *.h)");
        textedit->setWindowTitle(filename);
        windowHash.key(textedit)->setText(filename);
    }

    QFile* file = new QFile(filename);
    file->open(QIODevice::WriteOnly | QIODevice::Text);
    QFileInfo fileInfo(filename);
    if(fileInfo.isWritable()){
        QByteArray msg;
        msg.append(textedit->toHtml().toUtf8());
        file->write(msg);
    } else{
        QMessageBox::warning(this, "Error", "Can't Save this File!",
                             QMessageBox::Ok);
    }

    file->close();
    delete file;
}

void QtEditor::saveAsFile()
{
    qDebug("saveAs File");
    QTextEdit* textedit = (QTextEdit*)mdiArea->currentSubWindow()->widget();
    QString filename = QFileDialog::getSaveFileName(this, "Select file to save as",
                                             ".","Text File(*.txt *.html *.c *.cpp *.h)");
    textedit->setWindowTitle(filename);
    QFile* file = new QFile(filename);
    file->open(QIODevice::WriteOnly | QIODevice::Text);
    QFileInfo fileInfo(filename);
    if(fileInfo.isWritable()){
        QByteArray msg;
        msg.append(textedit->toHtml().toUtf8());
        file->write(msg);
    } else{
        QMessageBox::warning(this, "Error", "Can't Save this File!",
                             QMessageBox::Ok);
    }

    textedit->setWindowTitle(filename);
    windowHash.key(textedit)->setText(filename);
    windowHash.key(textedit)->setStatusTip(filename);

    file->close();
    delete file;
}

void QtEditor::printFile()
{
    QPrinter printer(QPrinter::HighResolution);
    printer.setFullPage(true);
    QPrintDialog printDialog(&printer, this);
    if(printDialog.exec() == QDialog::Accepted){
        QTextEdit* textedit = (QTextEdit*)mdiArea->currentSubWindow()->widget();
        textedit->print(&printer);
    }
}

//Action 생성 함수
template <typename T, typename Functor>
QAction* QtEditor::makeAction(QString icon, QString text, T shortCut,
                              QString toolTip, Functor lambda)
{
    QAction *act = new QAction(text, this);
    if(icon.length( ))
    {
        icon = ":/images/" + icon;      //리소스 시스템 경로 설정
         act->setIcon(QIcon(icon));
    }
    QKeySequence keySequence(shortCut);
    act->setShortcut(keySequence);
    act->setStatusTip(toolTip);
    act->setToolTip(toolTip);
    connect(act, &QAction::triggered, this, lambda);
    return act;
}

template <typename T>
QAction *QtEditor::makeAction(QString icon, QString text, \
                              T shortCut, QString toolTip, \
                              QObject* recv, const char* slot)
{
    QAction *act = new QAction(text, this);
    icon = ":/images/" + icon;
    if(icon.length( ))
        act->setIcon(QIcon(icon));
    QKeySequence keySequence(shortCut);
    act->setShortcut(keySequence);
    act->setStatusTip(toolTip);
    connect(act, SIGNAL(triggered()), recv, slot);
    return act;
}

//Format 함수
//정렬 함수
void QtEditor::alignText()
{
    QMdiSubWindow* subWindow = mdiArea->currentSubWindow();
    QTextEdit* textEdit = dynamic_cast<QTextEdit*>(subWindow->widget());
    QAction* action = qobject_cast<QAction*>(sender());

    if(action->text().contains("center",Qt::CaseInsensitive))
        textEdit->setAlignment(Qt::AlignCenter);
    else if (action->text().contains("left",Qt::CaseInsensitive))
        textEdit->setAlignment(Qt::AlignLeft);
    else if (action->text().contains("right",Qt::CaseInsensitive))
        textEdit->setAlignment(Qt::AlignRight);
    else if (action->text().contains("justify",Qt::CaseInsensitive))
        textEdit->setAlignment(Qt::AlignJustify);
}

//Format 함수
//폰트 색상변경 함수
void QtEditor::setColor()
{
    QTextEdit* textedit = (QTextEdit*)mdiArea->currentSubWindow()->widget();
    QColor color = QColorDialog::getColor(textedit->textColor(),this);
    if(color.isValid())
        textedit->setTextColor(color);
}

//Format 함수
//폰트 변경 함수
void QtEditor::setFont()
{
    bool ok;
    QTextEdit* textedit = (QTextEdit*)mdiArea->currentSubWindow()->widget();
    QFont font = QFontDialog::getFont(&ok, textedit->currentFont(), this);
    if(ok)
        textedit->setCurrentFont(font);
}

//Edit 함수
void QtEditor::undo()
{
    QMdiSubWindow* subWindow = mdiArea->currentSubWindow();
    if(!(subWindow == nullptr)){
        QTextEdit* textedit = (QTextEdit*)subWindow->widget();
        textedit->undo();
    }
}
void QtEditor::redo()
{
    QTextEdit* textedit = (QTextEdit*)mdiArea->currentSubWindow()->widget();
    textedit->redo();
}
void QtEditor::copy()
{
    QTextEdit* textedit = (QTextEdit*)mdiArea->currentSubWindow()->widget();
    textedit->copy();
}
void QtEditor::cut()
{
    QTextEdit* textedit = (QTextEdit*)mdiArea->currentSubWindow()->widget();
    textedit->cut();
}
void QtEditor::paste()
{
    QTextEdit* textedit = (QTextEdit*)mdiArea->currentSubWindow()->widget();
    textedit->paste();
}
void QtEditor::zoomIn()
{
    QTextEdit* textedit = (QTextEdit*)mdiArea->currentSubWindow()->widget();
    textedit->zoomIn();
}
void QtEditor::zoomOut()
{
    QTextEdit* textedit = (QTextEdit*)mdiArea->currentSubWindow()->widget();
    textedit->zoomOut();
}
void QtEditor::clear()
{
    QTextEdit* textedit = (QTextEdit*)mdiArea->currentSubWindow()->widget();
    textedit->clear();
}

//메세지 박스
void QtEditor::aboutBox()
{
    QMessageBox::information(this, "Information",
                 "infomation contents", QMessageBox::Yes |
                 QMessageBox::No | QMessageBox::Cancel);
}

//윈도우 관리
void QtEditor::selectWindow()
{
    QTextEdit* textedit = (QTextEdit*)windowHash[(QAction*)sender()];
    if(textedit)
        textedit->setFocus();
}

void QtEditor::closeWindow()
{
    QTextEdit* textedit = (QTextEdit*)sender();
    window->removeAction(windowHash.key(textedit));
    delete windowHash.key(textedit);
}

//이벤트 필터
bool QtEditor::eventFilter(QObject* obj, QEvent* event)
{
    if(event->type() == QEvent::KeyPress){
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
        qDebug("Key Press %d", keyEvent->key());
        return true;
    } else {
        return QObject::eventFilter(obj, event);
    }
}
