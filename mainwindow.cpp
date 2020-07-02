#include <ui_mainwindow.h>
#include <mainwindow.h>
#include <QFileDialog>
#include <iostream>
#include <thread>
#include <filesystem.h>
#include <vector>
#include <QStringListModel>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionopen_triggered()
{
    QString path = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    filesystem *file = new filesystem;

    std::thread t1(&filesystem::List_dir, file, path.toStdString());
    t1.join();

    auto imgs = file->GetImgs();

    QStringList list;

    for(auto it = imgs.begin(); it != imgs.end(); it++)
    {
        list << QString::fromStdString(*it);
    }

    ui->listView->setModel(new QStringListModel(list));

}

void MainWindow::on_listView_doubleClicked(const QModelIndex &index)
{
    QGraphicsScene scene;

}

void MainWindow::on_pushButton_2_clicked()
{
    QGraphicsScene scene;
    QPixmap pixmap("image.jpeg");
    scene.addPixmap(pixmap);
    //ui->viewer->setScene(&scene);

    // add here
    ui->graphicsView->setScene(&scene);
    ui->graphicsView->show();
}
