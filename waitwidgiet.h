#ifndef WAITWIDGIET_H
#define WAITWIDGIET_H

#include <QWidget>
#include <QApplication>
#include <QDesktopWidget>

namespace Ui {
class WaitWidgiet;
}

class WaitWidgiet : public QWidget
{
    Q_OBJECT

public:
    explicit WaitWidgiet(QWidget *parent = 0);
    void setContent(QString str);
    ~WaitWidgiet();

private:
    Ui::WaitWidgiet *ui;
};

#endif // WAITWIDGIET_H
