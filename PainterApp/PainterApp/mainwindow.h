#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class ScratchPad;
class MemoAlbum;
class ImageSlide;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionSave_triggered();
    void on_actionColor_triggered();

private:
    Ui::MainWindow *ui;

    ScratchPad* m_scratchPad;
    MemoAlbum* m_memoAlbum;
    ImageSlide* m_imageSlide;
};

#endif // MAINWINDOW_H
