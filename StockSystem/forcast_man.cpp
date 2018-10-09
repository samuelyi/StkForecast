#include "forcast_man.h"

ForcastMan::ForcastMan()
    : stock_2pdown_forcast_30m_(1024)
    , stock_2pdown_forcast_h_(1024)
    , stock_2pdown_forcast_d_(1024)
    , stock_2pdown_forcast_w_(1024)
    , stock_2pdown_forcast_mon_(1024)
    , stock_2pup_forcast_30m_(1024)
    , stock_2pup_forcast_h_(1024)
    , stock_2pup_forcast_d_(1024)
    , stock_2pup_forcast_w_(1024)
    , stock_2pup_forcast_mon_(1024)
{

}

void ForcastMan::Append(TypePeriod type_period, const std::string &code, T_Data2pDownForcast &forcast_data)
{
    _Append2pForcast(type_period, code, forcast_data); 
}


void ForcastMan::Append(TypePeriod type_period, const std::string &code, T_Data2pUpForcast &forcast_data)
{
    _Append2pForcast(type_period, code, forcast_data);
}

std::vector<T_Data2pDownForcast> * ForcastMan::Find2pDownForcast(const std::string &code, TypePeriod type_period)
{
    Code2pDownForcastType & holder_ref = Get2pDownDataHolder(type_period);
    auto vector_iter = holder_ref.find(code);
    if( vector_iter == stock_2pdown_forcast_d_.end() )
        return nullptr;
    return std::addressof(vector_iter->second);
}

std::vector<T_Data2pUpForcast> * ForcastMan::Find2pUpForcast(const std::string &code, TypePeriod type_period)
{
    Code2pUpForcastType & holder_ref = Get2pUpDataHolder(type_period);
    auto vector_iter = holder_ref.find(code);
    if( vector_iter == stock_2pup_forcast_d_.end() )
        return nullptr;
    return std::addressof(vector_iter->second);
}

bool ForcastMan::HasIn2pDownwardForcast(const std::string &code, TypePeriod type_period, T_KlineDataItem &item_a, T_KlineDataItem &item_b)
{
    static auto has_in2pforcasts = [this](std::vector<T_Data2pDownForcast>& data_vector, int date_a, int date_b)->bool
    { 
        if( data_vector.empty() ) return false;
        unsigned int i = 0;
        for( ; i < data_vector.size(); ++i )
        {
            if( data_vector.at(i).date_a == date_a && data_vector.at(i).date_b == date_b )
                break;
        }
        return i != data_vector.size();
    };

    Code2pDownForcastType & code_2pdown_fcst = Get2pDownDataHolder(type_period);
    auto vector_iter = code_2pdown_fcst.find(code);
    if( vector_iter != code_2pdown_fcst.end() )
        return has_in2pforcasts(vector_iter->second, item_a.kline_posdata.date, item_b.kline_posdata.date);
    else 
        return false;
}

bool ForcastMan::HasIn2pUpForcast(const std::string &code, TypePeriod type_period, T_KlineDataItem &item_a, T_KlineDataItem &item_b)
{
    static auto has_in2pforcasts = [this](std::vector<T_Data2pUpForcast>& data_vector, int date_a, int date_b)->bool
    { 
        if( data_vector.empty() ) return false;
        unsigned int i = 0;
        for( ; i < data_vector.size(); ++i )
        {
            if( data_vector.at(i).date_a == date_a && data_vector.at(i).date_b == date_b )
                break;
        }
        return i != data_vector.size();
    };
    Code2pUpForcastType &code_2pup_fcst = Get2pUpDataHolder(type_period);
    auto vector_iter = code_2pup_fcst.find(code);
    if( vector_iter != code_2pup_fcst.end() )
        return has_in2pforcasts(vector_iter->second, item_a.kline_posdata.date, item_b.kline_posdata.date);
    else 
        return false;
}

Code2pUpForcastType & ForcastMan::Get2pUpDataHolder(TypePeriod type_period)
{
    switch (type_period)
    {
    case TypePeriod::PERIOD_30M: return stock_2pup_forcast_30m_;
    case TypePeriod::PERIOD_HOUR: return stock_2pup_forcast_h_;
    case TypePeriod::PERIOD_DAY: return stock_2pup_forcast_d_;
    case TypePeriod::PERIOD_WEEK: return stock_2pup_forcast_w_;
    case TypePeriod::PERIOD_MON: return stock_2pup_forcast_mon_;
    default: assert(false);
    }
    return Code2pUpForcastType();
}

Code2pDownForcastType & ForcastMan::Get2pDownDataHolder(TypePeriod type_period)
{
    switch (type_period)
    {
    case TypePeriod::PERIOD_30M: return stock_2pdown_forcast_30m_;
    case TypePeriod::PERIOD_HOUR: return stock_2pdown_forcast_h_;
    case TypePeriod::PERIOD_DAY: return stock_2pdown_forcast_d_;
    case TypePeriod::PERIOD_WEEK: return stock_2pdown_forcast_w_;
    case TypePeriod::PERIOD_MON: return stock_2pdown_forcast_mon_;
    default: assert(false);
    }
    return Code2pDownForcastType();
}


std::tuple<double, double, double>  ForcastC_ABDown(double a, double b)
{
    double c2 = sqrtf(a * b);
    double c1 = sqrtf(b * c2);
    double c3 = c2 * c2 / c1;
    return std::make_tuple(c1, c2, c3);
}

std::tuple<double, double, double>  ForcastC_ABUp(double a, double b)
{
    double c2 = sqrtf(a * b);
    double c1 = sqrtf(b * c2);
    double c3 = c2 * c2 / c1;
    return std::make_tuple(c1, c2, c3);
}