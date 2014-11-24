#ifndef IMPORTWIDGET_H
#define IMPORTWIDGET_H

#include <QWidget>

namespace Ui {
    class ImportWidget;
}

class ImportWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ImportWidget(QWidget *parent = 0);
    ~ImportWidget();

private:
    Ui::ImportWidget *ui;
};

#endif // IMPORTWIDGET_H
