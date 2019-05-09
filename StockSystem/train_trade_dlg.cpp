
#include "train_trade_dlg.h"

#include <QString>

TrainTradeDlg::TrainTradeDlg(bool is_sell) : is_sell_(is_sell)
{
    ui.setupUi(this);
    bool ret = QObject::connect(this, SIGNAL(showEvent(QShowEvent * )), SLOT(OnShowEvent(QShowEvent *)));

}

void TrainTradeDlg::OnShowEvent(QShowEvent * event)
{
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