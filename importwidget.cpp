#include "importwidget.h"
#include "ui_importwidget.h"
#include "qexcel.h"

ImportWidget::ImportWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImportWidget)
{
    ui->setupUi(this);
    m_wgt_wait = new WaitWidgiet;
    this->setWindowTitle(tr("导入EXCEL"));

    move((QApplication::desktop()->width()-this->width())/2, (QApplication::desktop()->height()-this->height())/2);
}

ImportWidget::~ImportWidget()
{
    delete m_wgt_wait;
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
    ui->m_lbl_status->clear();

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

int ImportWidget::get_field_count()
{
    bool bRetCode = false;
    QString strSql = " select count(*) from information_schema.columns where TABLE_SCHEMA='";
    strSql += m_strDbSelected + "' and TABLE_NAME='";
    strSql += ui->m_cmb_table->currentText() + "';";
    qDebug()<<strSql;
    QSqlQuery query =  DBCommon::get_instance()->get_connect(m_strDbSelected);
    bRetCode =query.exec(strSql);
    if(!bRetCode)
    {
        QMessageBox::critical(NULL,tr("获取表字段数失败"),
                     DBCommon::get_instance()->get_connect(m_strDbSelected).lastError().text());
    }

    QSqlQueryModel model;
    model.setQuery(query);

    return model.index(0,0).data().toInt();
}

void ImportWidget::on_m_btn_import_clicked()
{
    ui->m_lbl_status->setText(tr("正在努力导入中，请稍等..."));
    m_wgt_wait->setContent(tr("正在努力导入中，请稍等..."));
    QString strExcel = ui->m_edt_path->text().trimmed();
    if(strExcel.isEmpty())
    {
        m_wgt_wait->close();
        QMessageBox::critical(NULL,tr("注意"), tr("请选择要倒入的excel文件"), QMessageBox::Ok);
        m_wgt_wait->show();
    }

    //打开文件，取得工作簿
    QExcel excel(strExcel);
    excel.selectSheet(1);
    excel.getSheetName();
    qDebug()<<"SheetName 1="<<excel.getSheetName(1);

    int topLeftRow=0, topLeftColumn=0, bottomRightRow=0, bottomRightColumn=0;
    excel.getUsedRange(&topLeftRow, &topLeftColumn, &bottomRightRow, &bottomRightColumn);
    qDebug()<<"top:"<<topLeftRow<<" "<<topLeftColumn;
    qDebug()<<"bottom:"<<bottomRightRow<<" "<<bottomRightColumn;

    //获取表的字段数
    int iFieldCnt = get_field_count();
    if(iFieldCnt <= 0)
    {
        m_wgt_wait->close();
        QMessageBox::critical(NULL,tr("表没创建"),tr("请先创建表"), QMessageBox::Ok);
        m_wgt_wait->show();
    }
    else if(iFieldCnt != bottomRightColumn)
    {
        m_wgt_wait->close();
        int iRet = QMessageBox::question(NULL,tr("注意"),tr("表字段与excel中字段数不一样，是否继续导入"), QMessageBox::Yes | QMessageBox::No);
        if(iRet == QMessageBox::No)
        {
            ui->m_lbl_status->setText(tr("已放弃导入"));
            return;
        }
        m_wgt_wait->show();
    }

    //导入数据库
    QString strHead = "insert into ";
    strHead += ui->m_cmb_table->currentText() + " values";
    QString strSql = strHead;
    qDebug()<<"excel column:"<<bottomRightColumn;
    qDebug()<<"table column:"<<iFieldCnt;
    int iIdx = 0;
    for(int i = 2; i <= bottomRightRow; ++i)
    {
        ++iIdx;
        strSql += "(";
        for(int j = 1; j <= iFieldCnt-1; ++j)
        {
            QString strValue = "";
            if(j <= bottomRightColumn)
            {
                strValue = excel.getCellValue(i, j).toString();
            }
            strSql += "'" + strValue +"',";
        }
        strSql += "now())";
        if(iIdx%2 != 0)
        {
            if(i != bottomRightRow)
                strSql += ",";
        }
        else
        {
            iIdx = 0;
            QSqlQuery query =  DBCommon::get_instance()->get_connect(m_strDbSelected);
            bool bRetCode =query.exec(strSql);
            if(!bRetCode)
            {
                ui->m_lbl_status->setText(tr("导入失败"));
                m_wgt_wait->close();
                QMessageBox::critical(NULL,tr("导入失败"),
                             DBCommon::get_instance()->get_connect(m_strDbSelected).lastError().text());

                return;
            }
            strSql = strHead;
        }
    }
    qDebug()<<"idx="<<iIdx;
    if(iIdx != 0)
    {
        QSqlQuery query =  DBCommon::get_instance()->get_connect(m_strDbSelected);
        qDebug()<<strSql;
        query.exec(strSql);
    }

    m_wgt_wait->close();
    QMessageBox::information(NULL,tr("成功"),tr("excel导入数据库成功"), QMessageBox::Ok);
    emit back_sig(this);
}
