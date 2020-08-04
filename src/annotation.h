#ifndef ANNOTATION_H
#define ANNOTATION_H

#include <QWidget>
#include <QPainter>
#include <QString>
#include <QLabel>
#include <vector>

using namespace std;

namespace Ui {
class annotation;
}

class annotation : public QWidget
{
    Q_OBJECT

public:
    explicit annotation(QWidget *parent = 0);
    void setPenColor(const QColor color);
    QSize setAreaDraw(QSize size, QPixmap image);
    void generateColor();
    void setLabels(vector<string> tmpLabel);
    QStringList TransformLabels();
    void listLabel_doubleClicked(const QModelIndex &index);
    void yoloFormart(int index, double x, double y, double w, double h);
    string getResult();
    void setConfig(string imgName, string imgDir, string format=NULL, string defaultLabel=NULL);

private:
    Ui::annotation *ui;
    QLabel *label;
    QDialog *dialog;
    QPainter painter;
    QPixmap mPix;
    QColor myPenColor;
    QRect mRect;
    vector<string> labels;
    bool windowActive;
    bool mousePressed;
    bool drawStarted;
    string labelClass;
    string result;
    string imgDir;
    string imgName;
    string format;
    string defaultLabel;

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
};

#endif // ANNOTATION_H
