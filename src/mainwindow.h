#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <filesys.h>
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
    void on_actionopen_triggered();
    void on_listView_doubleClicked(const QModelIndex &index);
    void on_pushButton_clicked();
    void on_radioButton_clicked(bool checked);
    void displayImage(QString location);
    void keyPressEvent(QKeyEvent *event);
    void on_radioButton_2_clicked();
    void on_radioButton_3_clicked();
    void on_comboBox_activated(const QString &arg1);

private:
    Ui::MainWindow *ui;
    filesys *file;
    QString path;
    string format;
    std::vector<std::string> imgs;
    int npos;
};

#endif // MAINWINDOW_H
