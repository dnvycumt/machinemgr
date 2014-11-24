#ifndef QUERYWIDGET_H
#define QUERYWIDGET_H

#include <QWidget>

namespace Ui {
    class QueryWidget;
}

class QueryWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QueryWidget(QWidget *parent = 0);
    ~QueryWidget();

private:
    Ui::QueryWidget *ui;
};

#endif // QUERYWIDGET_H
