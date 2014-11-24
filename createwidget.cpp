#include "createwidget.h"
#include "ui_createwidget.h"

CreateWidget::CreateWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateWidget)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("新增产品表"));
    setFixedSize(this->width(), this->height());
    move((QApplication::desktop()->width()-this->width())/2, (QApplication::desktop()->height()-this->height())/2);

    connect(ui->m_btn_save, SIGNAL(clicked()), this, SLOT(save_slot()));
}

CreateWidget::~CreateWidget()
{
    delete ui;
}

void CreateWidget::save_slot()
{

    emit save_sig(this);
}
