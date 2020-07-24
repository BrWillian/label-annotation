#ifndef ANNOTATION_H
#define ANNOTATION_H

#include <QWidget>
#include "QPainter"
#include "QString"
#include "QLabel"
#include "vector"

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
    QSize setAreaDraw(QSize size, QPixmap image);
    void GenerateColor();
    void setLabels(std::vector<std::string> tmpLabel);
    QStringList TransformLabels();

    void on_listlabel_doubleClicked(const QModelIndex &index);

private:
    Ui::annotation *ui;
    QPainter painter;
    QPixmap mPix;
    QPixmap mPixtemp;
    QRect mRect;
    QLabel *label;
    QDialog *dialog;
    bool windowActive = true;
    std::vector<std::string> labels;
    QColor myPenColor = QColor(Qt::blue);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);

};

#endif // ANNOTATION_H
