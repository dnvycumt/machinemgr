#include "mainwidget.h"
#include "ui_mainwidget.h"


MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    setFixedSize(this->width(), this->height());
    move((QApplication::desktop()->width()-this->width())/2, (QApplication::desktop()->height()-this->height())/2);

    m_wgt_create = new CreateWidget;
    m_wgt_import = new ImportWidget;
    m_wgt_query = new QueryWidget;

    connect(ui->m_btn_import, SIGNAL(clicked()), this, SLOT(import_slot()));
    connect(ui->m_btn_query, SIGNAL(clicked()), this, SLOT(query_slot()));
    connect(ui->m_btn_create, SIGNAL(clicked()), this, SLOT(create_slot()));
    connect(m_wgt_create, SIGNAL(save_sig(QWidget*)), this, SLOT(back_slot(QWidget*)));
}


MainWidget::~MainWidget()
{
    DBCommon::get_instance()->uninit_database();
    delete m_wgt_create;
    delete m_wgt_import;
    delete m_wgt_query;
    delete ui;
}

void MainWidget::import_slot()
{

}

void MainWidget::query_slot()
{

}

void MainWidget::create_slot()
{
    this->close();
    m_wgt_create->data_init();
    m_wgt_create->show();
}

void MainWidget::back_slot(QWidget *w)
{
    w->close();
    this->show();
}
