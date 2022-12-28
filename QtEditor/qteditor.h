#ifndef QTEDITOR_H
#define QTEDITOR_H

#include <QMainWindow>

class QLabel;
class QAction;
class QMdiArea;
class QMdiSubWindow;
class QTextEdit;
class QMenu;

class QtEditor : public QMainWindow
{
    Q_OBJECT

public:
    QtEditor(QWidget *parent = nullptr);
    ~QtEditor();

public slots:

//QFileDialog
    void newFile();
    void openFile();
    void saveFile();
    void saveAsFile();
    void printFile();

//Edit Menu
    void undo();
    void redo();
    void copy();
    void cut();
    void paste();
    void zoomIn();
    void zoomOut();
    void clear();

//Format 메뉴
    void alignText();           //정렬 함수
    void setColor();            //색상 셋팅
    void setFont();             //폰트 셋팅

//메세지 박스
    void aboutBox();            //메세지 박스 출력

//윈도우 관리
    void selectWindow();
    void closeWindow();

private:
    QLabel* statusLabel;
    QMdiArea* mdiArea;
    QMenu* window;
    QHash<QAction*, QTextEdit*> windowHash;

    template <typename T>
    QAction* makeAction(QString icon, QString text, T shortCut,
                        QString toolTip, QObject* recv, const char* slot);

    template <typename T, typename Functor>
    QAction* makeAction(QString icon, QString text, T shortCut,
                        QString toolTip, Functor lambda);

    bool eventFilter(QObject*, QEvent*);
};
#endif // QTEDITOR_H
