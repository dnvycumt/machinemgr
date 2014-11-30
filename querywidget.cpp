#include "querywidget.h"
#include "ui_querywidget.h"

QueryWidget::QueryWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QueryWidget)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("对比功能"));
    setFixedSize(this->width(), this->height());
    move((QApplication::desktop()->width()-this->width())/2, (QApplication::desktop()->height()-this->height())/2);
}

QueryWidget::~QueryWidget()
{
    delete ui;
}

void QueryWidget::data_init()
{
    ui->m_edt_input->clear();
    ui->m_lbl_result->clear();

    m_strDbSelected = DEFAULT_DB;
    ui->m_radio_rf->setChecked(true);
    get_tables();
    get_field();
}

void QueryWidget::on_m_btn_back_clicked()
{
    emit back_sig(this);
}

void QueryWidget::on_m_radio_rf_toggled(bool checked)
{
    if(checked)
    {
        m_strDbSelected = "rf";
        get_tables();
    }
}

void QueryWidget::on_m_radio_rx_clicked(bool checked)
{
    if(checked)
    {
        m_strDbSelected = "rx";
        get_tables();
    }
}

void QueryWidget::on_m_radio_mac_toggled(bool checked)
{
    if(checked)
    {
        m_strDbSelected = "mac";
        get_tables();
    }
}

void QueryWidget::get_tables()
{
    bool bRetCode = false;
    ui->m_cmb_table->clear();
    QString strSql = "show tables;";
    QSqlQuery query =  DBCommon::get_instance()->get_connect(m_strDbSelected);
    bRetCode =query.exec(strSql);
    if(!bRetCode)
    {
        QMessageBox::critical(NULL,tr("show tables failed"),
                     DBCommon::get_instance()->get_connect(m_strDbSelected).lastError().text());
        return;
    }

    QSqlQueryModel model;
    model.setQuery(query);
    int iRow = model.rowCount();

    for(int i = 0; i < iRow; ++i)
    {
        ui->m_cmb_table->addItem(model.index(i,0).data().toString());
    }
}

void QueryWidget::get_field()
{
    ui->m_cmb_field->clear();
    if(ui->m_cmb_table->currentText().isEmpty())
    {
        return;
    }
    bool bRetCode = false;
    QString strSql = " select column_name from information_schema.columns where TABLE_SCHEMA='";
    strSql += m_strDbSelected + "' and TABLE_NAME='";
    strSql += ui->m_cmb_table->currentText() + "';";
    qDebug()<<strSql;
    QSqlQuery query =  DBCommon::get_instance()->get_connect(m_strDbSelected);
    bRetCode =query.exec(strSql);
    if(!bRetCode)
    {
        QMessageBox::critical(NULL,tr("注意"),tr("获取表字段失败"));
        return;
    }

    QSqlQueryModel model;
    model.setQuery(query);
    int iRow = model.rowCount();
    for(int i = 0; i < iRow; ++i)
    {
        ui->m_cmb_field->addItem(model.index(i,0).data().toString());
    }
}

void QueryWidget::on_m_cmb_table_currentIndexChanged(int index)
{
    get_field();
}

void QueryWidget::on_m_btn_find_clicked()
{
    ui->m_lbl_result->clear();
    int iRetCode = is_find();
    QPalette palette;
    if(iRetCode == 0)
    {
        ui->m_lbl_result->setText(tr("NG"));
        palette.setColor(QPalette::WindowText, Qt::red);
    }
    else if(iRetCode > 0)
    {
        ui->m_lbl_result->setText(tr("OK"));
        palette.setColor(QPalette::WindowText, Qt::green);
    }
    else
    {
      return;
    }

    ui->m_lbl_result->setPalette(palette);
}

int QueryWidget::is_find()
{
    QString strInput = ui->m_edt_input->text().trimmed();
    QString strTable = ui->m_cmb_table->currentText();
    QString strField = ui->m_cmb_field->currentText();
    if(strInput.isEmpty())
    {
        QMessageBox::critical(NULL,tr("注意"),tr("请输入要查找的内容"), QMessageBox::Ok);
        return -1;
    }

    if(strTable.isEmpty())
    {
        QMessageBox::critical(NULL,tr("注意"),tr("没选则表"), QMessageBox::Ok);
        return -1;
    }

    if(strField.isEmpty())
    {
        QMessageBox::critical(NULL,tr("注意"),tr("没选中表中字段"), QMessageBox::Ok);
        return -1;
    }

    bool bRetCode = false;
    QString strSql = " select count(*) from ";
    strSql += strTable + " where ";
    strSql += strField + "='";
    strSql += tr(strInput.toStdString().c_str()) + "';";
    qDebug()<<strSql;
    QSqlQuery query =  DBCommon::get_instance()->get_connect(m_strDbSelected);
    bRetCode =query.exec(strSql);
    if(!bRetCode)
    {
        QMessageBox::critical(NULL,tr("注意"),tr("对比查询失败"));
        return -1;
    }

    QSqlQueryModel model;
    model.setQuery(query);
    return model.index(0,0).data().toInt();
}
