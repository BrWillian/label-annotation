#include "annotation.h"
#include "QMouseEvent"
#include <QPainter>
#include "QSize"
#include <iostream>
#include <stdlib.h>
#include "QDialog"
#include "QListView"
#include "QStringListModel"

annotation::annotation(QWidget *parent) :
    QWidget(parent)//,
   // ui(new Ui::annotation)
{
    //ui->setupUi(this);
    mousePressed = false;
    drawStarted = false;

    std::srand(42);
}
QSize annotation::setAreaDraw(QSize size, QPixmap image)
{

    mPix = image.scaled(size.width()-30,size.height()-50, Qt::KeepAspectRatio);

    label->setMaximumSize(size.width()-30,size.height()-50);
    label->setPixmap(mPix);

    return mPix.size();
}
void annotation::setText(QString text)
{
    this->labelText = text;
}
void annotation::mousePressEvent(QMouseEvent* event)
{
    mousePressed = true;
    GenerateColor();
    mRect.setTopLeft(event->pos());
    mRect.setBottomRight(event->pos());
}
void annotation::mouseMoveEvent(QMouseEvent *event)
{
    if(event->type() == QEvent::MouseMove )
    {
        mRect.setBottomRight(event->pos());
    }
    update();

}
void annotation::mouseReleaseEvent(QMouseEvent *event)
{
    mousePressed = false;
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("Select Class");
    dialog->resize(125,125);
    dialog->move(event->globalPos());
    QListView* listlabel = new QListView(dialog);
    listlabel->resize(100,100);
    listlabel->setGeometry(0,25,125,100);
    listlabel->updateGeometry();
    listlabel->setEditTriggers(QAbstractItemView::NoEditTriggers);
    listlabel->setModel(new QStringListModel(TransformLabels()));
    dialog->show();
    update();
}
void annotation::paintEvent(QPaintEvent *event)
{
    painter.begin(this);

    painter.setPen(QPen(myPenColor, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

    if(mousePressed)
    {
        label->clear();
        painter.drawPixmap(0,0,mPix);
        painter.drawRect(mRect);
        drawStarted = true;
    }else if(drawStarted)
    {
        QPainter tempPainter(&mPix);
        tempPainter.setPen(QPen(myPenColor, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        tempPainter.drawRect(mRect);
        painter.drawPixmap(0,0, mPix);
    }if(!mousePressed)
    {
        int x = mRect.x();
        int y = mRect.y();
        //painter.drawText(x-2,y,labelText);
    }
    painter.end();
}
void annotation::GenerateColor()
{
    unsigned char r, g, b;
    r = std::rand() % 255;
    g = std::rand() % 255;
    b = std::rand() % 255;

    myPenColor = QColor(r,g,b);
}
void annotation::setLabels(std::vector<std::string> tmpLabels)
{
    labels = tmpLabels;
}
QStringList annotation::TransformLabels()
{
    QStringList tmpList;

    for(auto it = labels.begin(); it != labels.end(); it++)
    {
        tmpList << QString::fromStdString(*it);
    }

    return tmpList;
    //ui->listView->setModel(new QStringListModel(list));
}
