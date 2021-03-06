#ifndef STK_FORECAST_APP_SDF8533_H_
#define STK_FORECAST_APP_SDF8533_H_

#include <memory>

#include <QtWidgets/QApplication>

#include <TLib/tool/tsystem_server_client_appbase.h>
#include <TLib/core/tsystem_communication_common.h>
#include <TLib/core/tsystem_serialization.h>

#include "stock_data_man.h"

class ExchangeCalendar;
class DataBase;
class StockMan;
class MainWindow;
class KLineWall;
class StkForecastApp : public QApplication, public TSystem::ServerClientAppBase
{
    //Q_OBJECT

public:

    StkForecastApp(int argc, char* argv[]); 
    ~StkForecastApp();

    bool Init();
    void Stop();

    std::shared_ptr<ExchangeCalendar>&  exchange_calendar() { return exchange_calendar_;}
    std::shared_ptr<DataBase>& data_base() { return data_base_; }

    StockDataMan & stock_data_man() { return *stock_data_man_; }

    MainWindow * main_window() { return main_window_.get(); }

protected:

    virtual void HandleNodeHandShake(TSystem::communication::Connection* , const TSystem::Message& ) override {};
    virtual void HandleNodeDisconnect(std::shared_ptr<TSystem::communication::Connection>& 
        , const TSystem::TError& ) override {};

private:

    std::shared_ptr<MainWindow>  main_window_;

    std::shared_ptr<DataBase>  data_base_;
    std::shared_ptr<ExchangeCalendar>  exchange_calendar_;
    std::shared_ptr<StockMan>  stock_man_;

    std::shared_ptr<StockDataMan>  stock_data_man_;
};
#endif // STK_FORECAST_APP_SDF8533_H_