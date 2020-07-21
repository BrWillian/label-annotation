#include "annotation.h"
#include "QMouseEvent"
#include <QPainter>
#include "QSize"
#include <iostream>
#include <stdlib.h>

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
        painter.drawText(x-2,y,labelText);
    }
    painter.end();
}
void annotation::GenerateColor()
{
    int r, g, b;
    r = std::rand() % 255;
    g = std::rand() % 255;
    b = std::rand() % 255;

    myPenColor = QColor(r,g,b);
}
