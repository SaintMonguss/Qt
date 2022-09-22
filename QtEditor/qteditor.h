#ifndef QTEDITOR_H
#define QTEDITOR_H

#include <QMainWindow>
#include <QMenu>
#include <QAction>
#include <QTextEdit>
#include <QMdiArea>
#include <QLabel>
#include <QHash>



class QtEditor : public QMainWindow
{
    Q_OBJECT
private:
    QAction *makeAction(QString icon, QString name, QString shortCut,\
                        QString toolTip, QObject* recv, const char* slot);
    QLabel *statusLabel;
    QMdiArea* mdiArea;
    QMenu *windowMenu;
    QHash<QAction*, QWidget*> windowHash;
    bool eventFilter(QObject*, QEvent*);


public:
    QtEditor(QWidget *parent = nullptr);
    ~QtEditor();


public slots:
    void newFile();
    void openFile();
    void saveFile();
    void saveAsFile();
    void printFile();

    void alignText();
    void editAction();

    void setTextFont(QFont);
    void setTextSize(qreal);
    void setColor();
    void setFont();
    void selectWindow();
};
#endif // QTEDITOR_H
