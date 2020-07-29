#include <ui_mainwindow.h>
#include <mainwindow.h>
#include <QFileDialog>
#include <thread>
#include <QStringListModel>
#include <filesys.h>
#include <annotation.h>
#include <QtWidgets>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->radioButton_2->setChecked(true);
    customWidget = NULL;

    file = new filesys;
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
    path = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if(!(path.toStdString() == ""))
    {
        std::thread t1(&filesys::listDir, file, path.toStdString());
        t1.join();

        imgs = file->getImgs();

        QStringList list;

        for(auto it = imgs.begin(); it != imgs.end(); it++)
        {
            list << QString::fromStdString(*it);
        }
        ui->listView->setModel(new QStringListModel(list));

        QString strtmp = QString::fromStdString(imgs.at(npos));
        displayImage(strtmp);
        QModelIndex ind = ui->listView->model()->index(npos, 0);
        ui->listView->setCurrentIndex(ind);
        ui->listView->selectionModel()->select(ind, QItemSelectionModel::Select);
    }
}

void MainWindow::on_listView_doubleClicked(const QModelIndex &index)
{
    displayImage(index.data().toString());
}
void MainWindow::on_pushButton_clicked()
{
    QString labels = ui->textEdit->toPlainText();
    if(!labels.isEmpty())
    {
        file->makeLabels(labels.toStdString());
        ui->radioButton->setAutoExclusive(false);
        ui->radioButton->setChecked(false);
        ui->comboBox->clear();
    }
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
void MainWindow::displayImage(QString location)
{
    ui->mdiArea->closeAllSubWindows();

    QPixmap img(location);
    customWidget = new annotation();
    ui->mdiArea->addSubWindow(customWidget, Qt::Window | Qt::FramelessWindowHint);

    string stem = file->returnStem(location.toStdString());
    //file->removeFile(path.toStdString()+"/"+stem+".txt");
    string pathtemp = path.toStdString();
    QSize size = customWidget->setAreaDraw(ui->groupBox_2->size(), img, stem, pathtemp);
    customWidget->parentWidget()->resize(size);
    customWidget->parentWidget()->updateGeometry();

    file->loadLabels();
    auto labels = file->getLabels();
    customWidget->setLabels(labels);

    ui->mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    customWidget->show();

    ui->mdiArea->setMaximumSize(size);
}
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(!imgs.empty())
    {
        std::string strtmp;

        if(event->key() == Qt::Key_D)
        {
            npos = npos+1;
            try{
                strtmp = imgs.at(npos);
            }catch(const std::out_of_range& oor){
                npos = imgs.size()-1;
                strtmp = imgs.at(npos);
            }
            displayImage(QString::fromStdString(strtmp));
        }

        if(event->key() == Qt::Key_A)
        {
            if(npos >= 0)
                npos = npos-1;
            try{
                strtmp = imgs.at(npos);
            }catch(const std::out_of_range& oor){
                npos = 0;
                strtmp = imgs.at(npos);
            }
            displayImage(QString::fromStdString(strtmp));
        }

        QModelIndex ind = ui->listView->model()->index(npos, 0);
        ui->listView->setCurrentIndex(ind);
        ui->listView->selectionModel()->select(ind, QItemSelectionModel::Select);
    }
}
