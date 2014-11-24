#include "importwidget.h"
#include "ui_importwidget.h"

ImportWidget::ImportWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImportWidget)
{
    ui->setupUi(this);
}

ImportWidget::~ImportWidget()
{
    delete ui;
}
