#ifndef CREATEWIDGET_H
#define CREATEWIDGET_H

#include <QWidget>
#include <QApplication>
#include <QDesktopWidget>

namespace Ui {
    class CreateWidget;
}

class CreateWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CreateWidget(QWidget *parent = 0);
    ~CreateWidget();

private:
    Ui::CreateWidget *ui;

signals:
    void save_sig(QWidget *);

private slots:
    void save_slot();
};

#endif // CREATEWIDGET_H
