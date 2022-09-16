#ifndef QTEDITOR_H
#define QTEDITOR_H

#include <QMainWindow>
#include <QMenu>
#include <QAction>
#include <QTextEdit>


class QtEditor : public QMainWindow
{
    Q_OBJECT
private:
    QAction *makeAction(QString icon, QString name, QString shortCut,\
                        QString toolTip, QObject* recv, const char* slot);
    QTextEdit *textedit;


public:
    QtEditor(QWidget *parent = nullptr);
    ~QtEditor();

public slots:
    void newFile();
    void openFile();
    void saveFile();
    void alignText();
};
#endif // QTEDITOR_H
