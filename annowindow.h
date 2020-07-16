#ifndef ANNOWINDOW_H
#define ANNOWINDOW_H

#include <QWidget>

namespace Ui {
class annowindow;
}

class annowindow : public QWidget
{
    Q_OBJECT

public:
    explicit annowindow(QWidget *parent = 0);
    ~annowindow();

private:
    Ui::annowindow *ui;
};

#endif // ANNOWINDOW_H
