#include "importwidget.h"
#include "ui_importwidget.h"

ImportWidget::ImportWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImportWidget)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("导入EXCEL"));
}

ImportWidget::~ImportWidget()
{
    delete ui;
}

void ImportWidget::on_m_tbtn_browse_clicked()
{
    QString fileName=QFileDialog::getOpenFileName(this,tr("选择要导入的Excel"),QDir::currentPath(),"allfiles(*.*)");
    ui->m_edt_path->setText(fileName);
}

void ImportWidget::data_init()
{
    ui->m_edt_path->clear();

    m_strDbSelected = DEFAULT_DB;
    ui->m_radio_rf->setChecked(true);

    ui->m_cmb_table->addItem(tr("请选择要导入的表"));
    get_tables();
}

void ImportWidget::on_m_btn_back_clicked()
{
    emit back_sig(this);
}

void ImportWidget::on_m_radio_rf_toggled(bool checked)
{
    if(checked)
    {
        m_strDbSelected = "rf";
        get_tables();
    }
}

void ImportWidget::on_m_radio_rx_clicked(bool checked)
{
    if(checked)
    {
        m_strDbSelected = "rx";
        get_tables();
    }
}

void ImportWidget::on_m_radio_mac_toggled(bool checked)
{
    if(checked)
    {
        m_strDbSelected = "mac";
        get_tables();
    }
}

void ImportWidget::get_tables()
{
    bool bRetCode = false;
    QString strSql = "show tables;";
    QSqlQuery query =  DBCommon::get_instance()->get_connect(m_strDbSelected);
    bRetCode =query.exec(strSql);
    if(!bRetCode)
    {
        QMessageBox::critical(NULL,tr("show tables failed"),
                     DBCommon::get_instance()->get_connect(m_strDbSelected).lastError().text());
    }

    QSqlQueryModel model;
    model.setQuery(query);
    int iRow = model.rowCount();
     ui->m_cmb_table->clear();
    for(int i = 0; i < iRow; ++i)
    {
        ui->m_cmb_table->addItem(model.index(i,0).data().toString());
    }
}

void ImportWidget::on_m_btn_import_clicked()
{

}
