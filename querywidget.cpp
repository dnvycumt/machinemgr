#include "querywidget.h"
#include "ui_querywidget.h"

QueryWidget::QueryWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QueryWidget)
{
    ui->setupUi(this);
}

QueryWidget::~QueryWidget()
{
    delete ui;
}
