#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <filesystem.h>
#include <annotation.h>
#include <QMainWindow>
#include <QMouseEvent>
#include <QPainter>
#include "QMdiSubWindow"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    annotation *customWidget;
    ~MainWindow();

private slots:
    void resizeEvent(QResizeEvent* event);

    void on_actionopen_triggered();

    void on_listView_doubleClicked(const QModelIndex &index);

    void on_pushButton_clicked();

    void on_radioButton_clicked(bool checked);

private:
    Ui::MainWindow *ui;
    filesystem *file = new filesystem;
    QPixmap img;
    QPixmap img_s;
};

#endif // MAINWINDOW_H
