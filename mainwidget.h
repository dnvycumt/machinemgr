#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include "createwidget.h"
#include "querywidget.h"
#include "importwidget.h"
#include "dbcommon.h"

namespace Ui {
    class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

private:
    Ui::MainWidget *ui;
    CreateWidget *m_wgt_create;
    ImportWidget *m_wgt_import;
    QueryWidget *m_wgt_query;

private slots:
    void import_slot();
    void query_slot();
    void create_slot();

    void back_slot(QWidget *w);
};

#endif // MAINWIDGET_H
