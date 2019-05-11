
#include "train_trade_dlg.h"

#include <QString>
#include <QShowEvent>
#include "train_dlg.h"

TrainTradeDlg::TrainTradeDlg(TrainDlg *train_dlg, bool is_sell) 
    : train_dlg_(train_dlg)
    , is_sell_(is_sell)
    , date_(0)
{
    ui.setupUi(this);
    bool ret = QObject::connect(ui.pbtn_close, SIGNAL(clicked()), SLOT(close()));

}

void TrainTradeDlg::closeEvent(QCloseEvent *event)
{
    QWidget::closeEvent(event);
    train_dlg_->showNormal();
}

void TrainTradeDlg::showEvent(QShowEvent * event)
{
    QWidget::showEvent(event);
    if( event->type() != QEvent::Show )
        return;
    if( is_sell_ )
    {
        this->setWindowTitle(QString::fromLocal8Bit("����"));

        ui.lab_price->setText(QString::fromLocal8Bit("�����۸�"));
        ui.lab_qty_ava->setText(QString::fromLocal8Bit("��������"));
        ui.lab_qty->setText(QString::fromLocal8Bit("��������"));
        ui.lab_capital_ava->setText(QString::fromLocal8Bit("�����ʽ�"));
        ui.lab_capital->setText(QString::fromLocal8Bit("�ʽ�"));
        ui.pbt_trade->setText(QString::fromLocal8Bit("����"));
    }else
    {
        this->setWindowTitle(QString::fromLocal8Bit("����"));

        ui.lab_price->setText(QString::fromLocal8Bit("����۸�"));
        ui.lab_qty_ava->setText(QString::fromLocal8Bit("��������"));
        ui.lab_qty->setText(QString::fromLocal8Bit("��������"));
        ui.lab_capital_ava->setText(QString::fromLocal8Bit("�����ʽ�"));
        ui.lab_capital->setText(QString::fromLocal8Bit("�����ʽ�"));
        ui.pbt_trade->setText(QString::fromLocal8Bit("����"));
    }
}