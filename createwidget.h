#ifndef CREATEWIDGET_H
#define CREATEWIDGET_H

#include <QWidget>
#include <QApplication>
#include <QDesktopWidget>
#include "dbcommon.h"
#include <QMutex>

namespace Ui {
    class CreateWidget;
}


class CreateWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CreateWidget(QWidget *parent = 0);
    ~CreateWidget();
    void data_init();

private:
    Ui::CreateWidget *ui;

    bool is_table_empty();
    bool create_table();
    QString m_strDbSelected;


signals:
    void back_sig(QWidget *);

private slots:
    void save_slot();
    void add_slot();
    void rf_slot();
    void rx_slot();
    void mac_slot();
    void on_m_btn_back_clicked();
};

#endif // CREATEWIDGET_H
