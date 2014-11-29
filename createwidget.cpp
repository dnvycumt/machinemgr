#include "createwidget.h"
#include "ui_createwidget.h"

CreateWidget::CreateWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateWidget)
{
    ui->setupUi(this);
    m_strDbSelected = DEFAULT_DB;
    ui->m_radio_rf->setChecked(true);
    this->setWindowTitle(tr("新增产品表"));
    setFixedSize(this->width(), this->height());
    move((QApplication::desktop()->width()-this->width())/2, (QApplication::desktop()->height()-this->height())/2);

    QStringList horizontalHeader;
    horizontalHeader << tr("字段名") << tr("字段长度");
    ui->m_tbl_field->setHorizontalHeaderLabels(horizontalHeader);

    connect(ui->m_btn_save, SIGNAL(clicked()), this, SLOT(save_slot()));
    connect(ui->m_btn_add, SIGNAL(clicked()), this, SLOT(add_slot()));

    connect(ui->m_radio_rf, SIGNAL(toggled(bool)), this, SLOT(rf_slot()));
    connect(ui->m_radio_rx, SIGNAL(toggled(bool)), this, SLOT(rx_slot()));
    connect(ui->m_radio_mac, SIGNAL(toggled(bool)), this, SLOT(mac_slot()));
}

CreateWidget::~CreateWidget()
{
    delete ui;
}

void CreateWidget::save_slot()
{
    if(ui->m_edt_line->text().trimmed().isEmpty() || ui->m_edt_line->text().trimmed() == "")
    {
       QMessageBox::warning(0, tr("请注意"), tr("请填写表名！"), QMessageBox::Ok);
       return;
    }

    if(m_strDbSelected.trimmed().isEmpty())
    {
       QMessageBox::warning(0, tr("请注意"), tr("请选择数据库！"), QMessageBox::Ok);
       return;
    }

    if(!is_table_empty() || ui->m_tbl_field->rowCount() <= 0)
    {
        QMessageBox::warning(0, tr("请注意"), tr("字段名称或者字段长度不能为空！"), QMessageBox::Ok);
        return;
    }

    if(!create_table())
    {
        return;
    }
    emit back_sig(this);
}

void CreateWidget::add_slot()
{
    int iRowCount = ui->m_tbl_field->rowCount();
    ui->m_tbl_field->insertRow(iRowCount);
    ui->m_tbl_field->setItem(iRowCount, 1, new QTableWidgetItem("200"));
}

bool CreateWidget::is_table_empty()
{
    int iRowCount = ui->m_tbl_field->rowCount();
    int iColNum = ui->m_tbl_field->columnCount();

    for(int j = 0; j < iColNum; ++j)
    {
        for(int i = 0; i < iRowCount; ++i)
        {
            if(ui->m_tbl_field->item(i, j) == 0 || ui->m_tbl_field->item(i, j)->text().trimmed().isEmpty())
            {
                return false;
            }
        }
    }
    return true;
}


void CreateWidget::rf_slot()
{
    if (ui->m_radio_rf->isChecked())
    {
        m_strDbSelected = "rf";
    }
}

void CreateWidget::rx_slot()
{
    if (ui->m_radio_rx->isChecked())
    {
        m_strDbSelected = "rx";
    }
}

void CreateWidget::mac_slot()
{
    if (ui->m_radio_mac->isChecked())
    {
        m_strDbSelected = "mac";;
    }
}

void CreateWidget::data_init()
{
    ui->m_edt_line->clear();
    ui->m_tbl_field->setRowCount(0);

    m_strDbSelected = DEFAULT_DB;
    ui->m_radio_rf->setChecked(true);
}

bool CreateWidget::create_table()
{
    QString strSql = "create table ";
    strSql += ui->m_edt_line->text().trimmed() + "(";
    bool bRetCode = false;

    int iRowCount = ui->m_tbl_field->rowCount();

    for(int i = 0; i < iRowCount; ++i)
    {
        QString strFieldName = ui->m_tbl_field->item(i, 0)->text().trimmed();
        QString strFieldLen = ui->m_tbl_field->item(i, 1)->text().trimmed();
        strSql +=strFieldName + " varchar(";
        strSql += strFieldLen + ")";
        strSql += ",";
    }
    strSql += "insert_dt TIMESTAMP DEFAULT now());";
    qDebug() << tr("数据库：") << m_strDbSelected;
    qDebug() << strSql;
    bRetCode = DBCommon::get_instance()->get_connect(m_strDbSelected).exec(strSql);
    if(!bRetCode)
    {
        QMessageBox::critical(NULL,tr("create table failed"),
                     DBCommon::get_instance()->get_connect(m_strDbSelected).lastError().text());
    }
    else
    {
        QMessageBox::information(NULL,QObject::tr("create table success"),
                     tr((ui->m_edt_line->text().trimmed()+"创建成功").toStdString().c_str()),
                     QMessageBox::Ok);
    }
    return bRetCode;
}

void CreateWidget::on_m_btn_back_clicked()
{
    emit back_sig(this);
}
