#ifndef K_LINE_WALL_SDF32DSF_
#define K_LINE_WALL_SDF32DSF_

#include <QtWidgets/QWidget>

#include "ui_klinewall.h"

#include "stockalldaysinfo.h"

class KLineWall : public QWidget
{
public:

    KLineWall();

    Ui_KLineWallForm  ui;

protected:

    void paintEvent(QPaintEvent*) override;
    void mouseDoubleClickEvent(QMouseEvent * e)  override;
    void mouseMoveEvent(QMouseEvent *e) override;
    void keyPressEvent(QKeyEvent *e) override;

private:

    std::list<StockDayInfo>  stk_days_infos_;
     
    StockAllDaysInfo stockAllDaysInfo_;  //一支股票的所有天数的消息

    std::string stockNum;
    

    float lowestMinPrice;
    float highestMaxPrice;
    bool  show_cross_line_;
    bool  is_repaint_k_;

    int  k_num_;
    std::string k_cycle_tag_;
    int  k_cycle_year_;
    int  date_;
    std::string k_data_str_;
};


#endif