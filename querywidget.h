#ifndef QUERYWIDGET_H
#define QUERYWIDGET_H

#include <QWidget>
#include "waitwidgiet.h"
#include "dbcommon.h"

namespace Ui {
    class QueryWidget;
}

class QueryWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QueryWidget(QWidget *parent = 0);
    ~QueryWidget();
    void data_init();

signals:
    void back_sig(QWidget *);

private slots:
    void on_m_btn_back_clicked();
    void on_m_radio_rf_toggled(bool checked);
    void on_m_radio_rx_clicked(bool checked);
    void on_m_radio_mac_toggled(bool checked);
    void on_m_cmb_table_currentIndexChanged(int index);

    void on_m_btn_find_clicked();

private:
    Ui::QueryWidget *ui;
    QString m_strDbSelected;

    void get_tables();
    void get_field();
    int is_find();
};

#endif // QUERYWIDGET_H
