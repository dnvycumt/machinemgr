#ifndef IMPORTWIDGET_H
#define IMPORTWIDGET_H

#include <QWidget>
#include <QFileDialog>
#include "dbcommon.h"

namespace Ui {
    class ImportWidget;
}

class ImportWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ImportWidget(QWidget *parent = 0);
    void data_init();
    ~ImportWidget();

signals:
    void back_sig(QWidget *);

private slots:
    void on_m_tbtn_browse_clicked();

    void on_m_btn_back_clicked();

    void on_m_radio_rf_toggled(bool checked);

    void on_m_radio_rx_clicked(bool checked);

    void on_m_radio_mac_toggled(bool checked);

    void on_m_btn_import_clicked();

private:
    Ui::ImportWidget *ui;

    QString m_strDbSelected;

    void get_tables();
    int get_field_count();
};

#endif // IMPORTWIDGET_H
