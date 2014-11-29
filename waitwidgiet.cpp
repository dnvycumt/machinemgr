#include "waitwidgiet.h"
#include "ui_waitwidgiet.h"

WaitWidgiet::WaitWidgiet(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WaitWidgiet)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    //setAttribute(Qt::WA_TranslucentBackground); //使除窗口部件以外的其他部分透明。

    setAutoFillBackground(true);

    QPalette palette;
    palette.setColor(QPalette::WindowText, Qt::white);
    ui->m_lbl_content->setPalette(palette);

    palette.setColor(QPalette::Background, QColor(69,137,148));
    setPalette(palette);
    //palette.setBrush(QPalette::Background, QBrush(QPixmap(":/background.png")));


    move((QApplication::desktop()->width()-this->width())/2, (QApplication::desktop()->height()-this->height())/2);
}

WaitWidgiet::~WaitWidgiet()
{
    delete ui;
}

void WaitWidgiet::setContent(QString str)
{
    this->close();
    ui->m_lbl_content->setText(str);
    this->show();
}
