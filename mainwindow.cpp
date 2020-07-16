#include <ui_mainwindow.h>
#include <mainwindow.h>
#include <QFileDialog>
#include <iostream>
#include <thread>
#include <vector>
#include <QStringListModel>
#include <filesystem.h>
#include <annotation.h>
#include "QtWidgets"

//Defines
#define Null    ""

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    file->loadLabels();
    auto labels = file->getLabels();

    QString arr;

    for(auto it=labels.begin(); it!=labels.end(); it++)
    {
        arr.append(QString::fromStdString(*it) + "\n");
    }

    ui->textEdit->setText(arr);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionopen_triggered()
{
    QString path = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if(!(path.toStdString() == Null))
    {
        std::thread t1(&filesystem::listDir, file, path.toStdString());
        t1.join();

        auto imgs = file->getImgs();

        QStringList list;

        for(auto it = imgs.begin(); it != imgs.end(); it++)
        {
            list << QString::fromStdString(*it);
        }
        ui->listView->setModel(new QStringListModel(list));
    }
}

void MainWindow::on_listView_doubleClicked(const QModelIndex &index)
{
    QString str = index.data().toString();
    ui->mdiArea->closeAllSubWindows();
    customWidget = new annotation();
    ui->mdiArea->addSubWindow(customWidget, Qt::Window | Qt::FramelessWindowHint);
    customWidget->parentWidget()->resize(ui->mdiArea->size());
    customWidget->parentWidget()->updateGeometry();
    customWidget->setImage(index.data().toString());
    //customWidget->setAreaDraw(ui->mdiArea->size());
    //customWidget->setFixedSize(ui->mdiArea->size());
    customWidget->show();



    //img = QPixmap(index.data().toString());
    //ui->mdiArea->setBackground(img.scaled(ui->mdiArea->size(), Qt::KeepAspectRatio));
    //ui->label_3->setPixmap(img.scaled(ui->label_3->size(), Qt::KeepAspectRatio));
    //ui->label_3->setAlignment(Qt::AlignCenter);
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
    if(!img.isNull())
    {
        img_s = img.scaled(ui->mdiArea->size(), Qt::KeepAspectRatio);
        //ui->mdiArea->setBackground(img_s);
        //ui->label_3->setPixmap(img_s);
        //ui->label_3->setAlignment(Qt::AlignCenter);
        QWidget::resizeEvent(event);
    }
}
void MainWindow::on_pushButton_clicked()
{
    QString labels = ui->textEdit->toPlainText();
    if(!labels.isEmpty())
    {
        file->makeLabels(labels.toStdString());
        ui->radioButton->setChecked(false);
        ui->comboBox->clear();
    }
    ui->textEdit->append(QString::number(img_s.size().width()));
    ui->textEdit->append(QString::number(img_s.size().height()));
}
void MainWindow::on_radioButton_clicked(bool checked)
{
    if(checked)
    {
        ui->comboBox->setEnabled(true);
        ui->comboBox->clear();

        file->loadLabels();

        auto labels = file->getLabels();

        for(auto it=labels.begin(); it!=labels.end(); it++)
        {
            ui->comboBox->addItem(QString::fromStdString(*it));
        }
    }
    else{
        ui->comboBox->setEnabled(false);
        ui->comboBox->clear();
    }
}
