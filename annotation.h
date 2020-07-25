#ifndef ANNOTATION_H
#define ANNOTATION_H

#include <QWidget>
#include <QPainter>
#include <QString>
#include <QLabel>
#include <vector>

namespace Ui {
class annotation;
}

class annotation : public QWidget
{
    Q_OBJECT

public:
    explicit annotation(QWidget *parent = 0);
    void setPenColor(const QColor color);
    QSize setAreaDraw(QSize size, QPixmap image, std::string imgName, std::string imgDir);
    void generateColor();
    void setLabels(std::vector<std::string> tmpLabel);
    QStringList TransformLabels();
    void listLabel_doubleClicked(const QModelIndex &index);
    void yoloFormart(int index, double x, double y, double w, double h);
    std::string getResult();

private:
    Ui::annotation *ui;
    QLabel *label;
    QDialog *dialog;
    QPainter painter;
    QPixmap mPix;
    QColor myPenColor;
    QRect mRect;
    std::vector<std::string> labels;
    bool windowActive;
    bool mousePressed;
    bool drawStarted;
    std::string labelClass;
    std::string result;
    std::string imgDir;
    std::string imgName;

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
};

#endif // ANNOTATION_H
