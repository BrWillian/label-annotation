#include <QStringListModel>
#include <annotation.h>
#include <QMouseEvent>
#include <QListView>
#include <QPainter>
#include <stdlib.h>
#include <QDialog>
#include <QSize>
#include <filesys.h>
#include <iostream>

using namespace std;

annotation::annotation(QWidget *parent) :
    QWidget(parent)
   // ui(new Ui::annotation)
{
    //ui->setupUi(this);
    mousePressed = false;
    drawStarted = false;
    windowActive = true;
    label = new QLabel(this);
    srand(42);
}
QSize annotation::setAreaDraw(QSize size, QPixmap image)
{
    this->imgName = imgName;
    this->imgDir = imgDir;

    mPix = image.scaled(size.width()-30,size.height()-50, Qt::KeepAspectRatio);

    label->setMaximumSize(size.width()-30,size.height()-50);
    label->setPixmap(mPix);

    return mPix.size();
}
void annotation::setConfig(string imgName, string imgDir, string format, string defaultLabel)
{
    this->imgName = imgName;
    this->imgDir = imgDir;
    this->format = format;
    this->defaultLabel = defaultLabel;
}
void annotation::mousePressEvent(QMouseEvent* event)
{
    if(windowActive)
    {
        mousePressed = true;
        generateColor();
        mRect.setTopLeft(event->pos());
        mRect.setBottomRight(event->pos());
    }
}
void annotation::mouseMoveEvent(QMouseEvent *event)
{
    if(event->type() == QEvent::MouseMove && windowActive || event->type() == QEvent::MouseMove && defaultLabel != "")
    {
        mRect.setBottomRight(event->pos());
    }
    update();
}
void annotation::mouseReleaseEvent(QMouseEvent *event)
{
    if(windowActive && defaultLabel == "")
    {
        mousePressed = false;
        dialog = new QDialog(this, Qt::WindowTitleHint | Qt::CustomizeWindowHint);
        dialog->setWindowTitle("Select Class");
        dialog->setFixedSize(134,134);
        dialog->move(event->globalPos());
        QListView* listLabel = new QListView(dialog);

        listLabel->setGeometry(2,2,130,130);
        listLabel->updateGeometry();
        listLabel->setEditTriggers(QAbstractItemView::NoEditTriggers);
        listLabel->setModel(new QStringListModel(TransformLabels()));
        connect(listLabel, &QListView::doubleClicked, this, &annotation::listLabel_doubleClicked);
        dialog->show();
        windowActive = false;
    }else
    {
        mousePressed = false;
        int n;
        vector<string>::iterator it;
        it=std::find(labels.begin(),labels.end(), defaultLabel);
        if(it != labels.end())
        {
            n = it-labels.begin();
        }
        yoloFormart(n, mRect.x(), mRect.y(), mRect.width(), mRect.height());

        filesys *file = new filesys;
        file->writeAnnotation(imgDir, imgName, result);
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
void annotation::generateColor()
{
    unsigned char r, g, b;
    r = rand() % 255;
    g = rand() % 255;
    b = rand() % 255;

    myPenColor = QColor(r,g,b);
}
void annotation::setLabels(vector<string> tmpLabels)
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
void annotation::listLabel_doubleClicked(const QModelIndex &index)
{
    windowActive = true;
    dialog->close();

    yoloFormart(index.row(), mRect.x(), mRect.y(), mRect.width(), mRect.height());

    filesys *file = new filesys;
    file->writeAnnotation(imgDir, imgName, result);
}
void annotation::yoloFormart(int index, double x, double y, double w, double h)
{
    int width = mPix.width();
    int height = mPix.height();

    this->result = to_string(index) + " " + to_string(x/width) \
            + " " + to_string(y/height) + " " + to_string(w/width) \
                                   + " " + to_string(h/height) + "\n";

    replace(result.begin(), result.end(), ',', '.');
}
