#include "annotation.h"
#include "ui_annotation.h"
#include "QMouseEvent"
#include <QPainter>
#include "QSize"
#include <QString>
#include "QLabel"

annotation::annotation(QWidget *parent) :
    QWidget(parent)//,
   // ui(new Ui::annotation)
{
    //ui->setupUi(this);

    mousePressed = false;
    drawStarted = false;

    myPenColor = Qt::blue;
}

annotation::~annotation()
{
    //delete ui;
}
void annotation::setAreaDraw(QSize size)
{
    mPix = QPixmap(size);
    mPix.fill(Qt::transparent);
}
void annotation::setImage(QString image)
{
    mPix = QPixmap(QWidget::size());
    mPix.load(image);
    label->setPixmap(image);
}
void annotation::mousePressEvent(QMouseEvent* event)
{
    mousePressed = true;
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
        label->setText(" ");
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
