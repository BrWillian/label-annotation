#ifndef ANNOTATION_H
#define ANNOTATION_H

#include <QWidget>
#include "QPainter"
#include "QString"
#include "QLabel"

namespace Ui {
class annotation;
}

class annotation : public QWidget
{
    Q_OBJECT

public:
    explicit annotation(QWidget *parent = 0);
    bool mousePressed;
    bool drawStarted;
    void setPenColor(const QColor color);
    void setAreaDraw(QSize size);
    void setImage(QString image);
    ~annotation();

private:
    Ui::annotation *ui;
    QPainter painter;
    QPixmap mPix;
    QRect mRect;
    QLabel *label = new QLabel(this);

    QColor myPenColor;

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);

};

#endif // ANNOTATION_H
