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
    label = new QLabel(this);
    std::srand(42);
}
QSize annotation::setAreaDraw(QSize size, QPixmap image)
{

    mPix = image.scaled(size.width()-30,size.height()-50, Qt::KeepAspectRatio);

    label->setMaximumSize(size.width()-30,size.height()-50);
    label->setPixmap(mPix);

    return mPix.size();
}
void annotation::mousePressEvent(QMouseEvent* event)
{
    if(windowActive)
    {
        mousePressed = true;
        GenerateColor();
        mRect.setTopLeft(event->pos());
        mRect.setBottomRight(event->pos());
    }
}
void annotation::mouseMoveEvent(QMouseEvent *event)
{
    if(event->type() == QEvent::MouseMove  && windowActive)
    {
        mRect.setBottomRight(event->pos());
    }
    update();
}
void annotation::mouseReleaseEvent(QMouseEvent *event)
{
    if(windowActive)
    {
        mousePressed = false;
        dialog = new QDialog(this, Qt::WindowTitleHint | Qt::CustomizeWindowHint);
        dialog->setWindowTitle("Select Class");
        dialog->setFixedSize(134,134);
        dialog->move(event->globalPos());
        QListView* listlabel = new QListView(dialog);

        listlabel->setGeometry(2,2,130,130);
        listlabel->updateGeometry();
        listlabel->setEditTriggers(QAbstractItemView::NoEditTriggers);
        listlabel->setModel(new QStringListModel(TransformLabels()));
        connect(listlabel, &QListView::doubleClicked, this, &annotation::on_listlabel_doubleClicked);
        dialog->show();
        windowActive = false;
    }
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
}
void annotation::on_listlabel_doubleClicked(const QModelIndex &index)
{
    windowActive = true;
    QString strtemp = index.data().toString();
    std::cout<<strtemp.toStdString()<<index.row();
    //std::cout<<mRect.x()<<" "<<mRect.y()<<" "<<mRect.width()<<" "<<mRect.height();
    dialog->close();
}
