#ifndef QTEDITOR_H
#define QTEDITOR_H

#include <QMainWindow>
#include <QMenu>
#include <QAction>
#include <QTextEdit>
#include <QMdiArea>
#include <QLabel>


class QtEditor : public QMainWindow
{
    Q_OBJECT
private:
    QAction *makeAction(QString icon, QString name, QString shortCut,\
                        QString toolTip, QObject* recv, const char* slot);
    QLabel *statusLabel;
    QMdiArea* mdiArea;


public:
    QtEditor(QWidget *parent = nullptr);
    ~QtEditor();

public slots:
    void newFile();
    void openFile();

    void saveFile();
    void alignText();
    void editAction();

    void setTextFont(QFont);
    void setTextSize(qreal);
};
#endif // QTEDITOR_H
