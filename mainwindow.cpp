#include <ui_mainwindow.h>
#include <mainwindow.h>
#include <QFileDialog>
#include <thread>
#include <QStringListModel>
#include <filesys.h>
#include <annotation.h>
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->radioButton_2->setChecked(true);
    ui->radioButton_3->setEnabled(false);
    ui->radioButton->setEnabled(false);
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

        ui->radioButton->setEnabled(true);

        npos = 0;
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
    npos = index.row();
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
    QMessageBox::information(this, "Label Annotation", "Labels successfully added!");
    QString strtmp = QString::fromStdString(imgs.at(npos));
    displayImage(strtmp);
}
void MainWindow::on_radioButton_clicked(bool checked)
{
    QString strtmp = QString::fromStdString(imgs.at(npos));
    displayImage(strtmp);

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
        ui->comboBox->showPopup();
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

    QSize size = customWidget->setAreaDraw(ui->groupBox_2->size(), img);

    string stem = file->returnStem(location.toStdString());
    file->removeFile(path.toStdString()+"/"+stem+".txt");
    string pathtemp = path.toStdString();

    if(ui->radioButton->isChecked())
    {
        customWidget->setConfig(stem, pathtemp, format, ui->comboBox->currentText().toStdString());
    }else
    {
        customWidget->setConfig(stem, pathtemp, format, "");
    }

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
                displayImage(QString::fromStdString(strtmp));
            }catch(const std::out_of_range& oor){
                npos = imgs.size()-1;
                strtmp = imgs.at(npos);
                QMessageBox::information(this, "Label Annotation", "You finished all images!");
            }
        }

        if(event->key() == Qt::Key_A)
        {
            if(npos >= 0)
                npos = npos-1;
            try{
                strtmp = imgs.at(npos);
                displayImage(QString::fromStdString(strtmp));
            }catch(const std::out_of_range& oor){
                npos = 0;
                strtmp = imgs.at(npos);
            }
        }

        QModelIndex ind = ui->listView->model()->index(npos, 0);
        ui->listView->setCurrentIndex(ind);
        ui->listView->selectionModel()->select(ind, QItemSelectionModel::Select);
    }
}

void MainWindow::on_radioButton_2_clicked()
{
    format = "yolo";
}

void MainWindow::on_radioButton_3_clicked()
{
    format = "pascalvoc";
}

void MainWindow::on_comboBox_activated(const QString &arg1)
{
    ui->comboBox->setEnabled(false);
    QString strtmp = QString::fromStdString(imgs.at(npos));
    displayImage(strtmp);
}
