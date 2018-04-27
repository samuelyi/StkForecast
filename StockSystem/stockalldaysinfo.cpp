﻿#include "stockalldaysinfo.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <assert.h>
#include <memory>

#include <Windows.h>
#include <QtWidgets/QMessageBox>
#include <QDebug>

#define RESERVE_CAPACITY_IN_T_VECTOR    1024*16
//#define RESERVE_SIZE_IN_T_VECTOR    1024*16
//#define FIRST_STARTPOS_IN_T_VECTOR  10000


static bool compare(const T_StockHisDataItem &left_h, const T_StockHisDataItem &right_h)
{
    return left_h.date < right_h.date; // from small to big
}

static bool compare_index(const T_StockHisDataItem *left_h, const T_StockHisDataItem *right_h)
{
    return left_h->date < right_h->date;
}

static bool dompare( std::shared_ptr<T_KlineDateItem> &lh, std::shared_ptr<T_KlineDateItem> &rh)
{
    return lh->stk_item.date < rh->stk_item.date;
}

static bool bompare(const T_KlineDateItem &lh, const T_KlineDateItem &rh)
{
    return lh.stk_item.date < rh.stk_item.date;
}

// 下分形遍历
void TraverseSetUpwardFractal( std::vector<std::shared_ptr<T_KlineDateItem> > &kline_data_items);
// 上分形遍历
void TraverseSetDownwardFractal( std::vector<std::shared_ptr<T_KlineDateItem> > &kline_data_items);

StockAllDaysInfo::StockAllDaysInfo()
{
    //LoadDataFromFile("./data/600030.dat");

}

bool StockAllDaysInfo::Init()
{
    //-----------------
    HMODULE moudle_handl = LoadLibrary("StkQuoter.dll");
    if( !moudle_handl )
    {
        QMessageBox::information(nullptr, "ALERT", "can't load stkQuoter.dll");
        return false;
    }

    stk_his_data_ = (StkHisDataDelegate)GetProcAddress(moudle_handl, "StkHisData");
    stk_hisdata_release_ = (StkRelHisDataDelegate)GetProcAddress(moudle_handl, "StkRelHisData");
    if( stk_his_data_ && stk_hisdata_release_ )
        return true;
    else
        return false;

    /*std::vector<std::shared_ptr<int>> tmp_vector;
    tmp_vector.reserve(365*26);
    tmp_vector[200] = nullptr;*/
}

void StockAllDaysInfo::LoadDataFromFile(std::string &fileName)
{
    std::ifstream inputFile(fileName.c_str());
    std::string strLine;
    // read line at time until end-of-file
    while(getline(inputFile, strLine))
    {
        //cout<<strLine<<endl;
        StockDayInfo stockDayInfo;
        //将strLine中的所有字段拆解并赋值给stockDayInfo的各个数据成员
        stockDayInfo.ReadData(strLine);
        //stockDayInfo.Display();
        //this->stockAllDaysInfoList.push_back(stockDayInfo);
    }
    inputFile.close();
}

// date is save from recent to remote
T_HisDataItemContainer* StockAllDaysInfo::LoadStockData(const std::string &stk_code, int start_date, int end_date)
{
    assert( stk_his_data_ && stk_hisdata_release_ );

    //stock_days_info_.find(
    T_StockHisDataItem *p_data_items = nullptr;
    int count = stk_his_data_(const_cast<char*>(stk_code.c_str()), start_date, end_date, &p_data_items);

    if( !p_data_items )
    {
        return nullptr;
    }
#if 1
    auto iter = stock_his_items_.find(stk_code);
    if( iter == stock_his_items_.end() )
    {
        iter = stock_his_items_.insert(std::make_pair(stk_code, T_HisDataItemContainer())).first;
        //  19901219..20151231 | 20160104..
        //iter->second.reserve(RESERVE_CAPACITY_IN_T_VECTOR);
        // select count(*) from exchangeDate where is_tradeday=1 and date>=20160101 limit 10;
    }else
        iter->second.clear();

    std::vector<std::shared_ptr<T_KlineDateItem> > &kline_data_items = iter->second;

    for( int k = 0; k < count; ++k )
    {
        auto k_item = std::make_shared<T_KlineDateItem>(p_data_items[k]);
        kline_data_items.push_back(std::move(k_item)); 
    }

    // sort T_KlineDateItems by day from small to bigger
    std::sort(kline_data_items.begin(), kline_data_items.end(), dompare);
     
#endif 

#if 0
    auto iter = stock_his_items_.find(stk_code);
    if( iter == stock_his_items_.end() )
    {
       iter = stock_his_items_.insert(std::make_pair(stk_code, T_HisDataItemContainer())).first;
       //  19901219..20151231 | 20160104..
       //iter->second.reserve(RESERVE_CAPACITY_IN_T_VECTOR);
       // select count(*) from exchangeDate where is_tradeday=1 and date>=20160101 limit 10;
    }

 
    T_HisDataItemContainer & his_data_items = iter->second;
    for( int i = 0; i < count; ++i )
    {
        if( his_data_items.empty() )
        {
            his_data_items.push_back(kline_data_items[i]);
             continue;
        }
		 
        if( his_data_items.rbegin()->get()->stk_item.date < kline_data_items[i]->stk_item.date )
		{
			qDebug() << " rbegin data " << his_data_items.rbegin()->get()->stk_item.date << "\n";
            his_data_items.push_back(kline_data_items[i]);

		}else if( his_data_items.begin()->get()->stk_item.date > kline_data_items[i]->stk_item.date )
		{
			his_data_items.push_front(kline_data_items[i]);
		}
    }
 

#endif

	stk_hisdata_release_(p_data_items);

    TraverseSetUpwardFractal(kline_data_items);

    TraverseSetDownwardFractal(kline_data_items);
    
	return std::addressof(iter->second);

}

//在链表中搜索出最低价中的最小值
float StockAllDaysInfo::GetLowestMinPrice()
{
    float lowestMinPrice = 100000000.0f;
    //std::list<StockDayInfo>::iterator iter;
    for(auto iter = day_kline_data_container_.begin(); iter != day_kline_data_container_.end(); iter++)
    {
        //搜索当前元素是否比现有的最小值要更小，更小则替换
        if( lowestMinPrice > (*iter)->stk_item.low_price )
        {
            lowestMinPrice = (*iter)->stk_item.low_price;
        }
    }

    return lowestMinPrice;
}

float StockAllDaysInfo::GetHighestMaxPrice()
{
    float higestMaxPrice = 0.0f;
    //std::list<StockDayInfo>::iterator iter;
    for( auto iter = day_kline_data_container_.begin(); iter != day_kline_data_container_.end(); iter++)
    { 
        if(higestMaxPrice < (*iter)->stk_item.high_price )
        {
            higestMaxPrice = (*iter)->stk_item.high_price;
        }
    }
    return higestMaxPrice;
}

float StockAllDaysInfo::GetHisDataLowestMinPrice(const std::string& stock)
{
	auto iter = stock_his_items_.find(stock);
	if( iter == stock_his_items_.end() )
		return 0.0;
	 
	float lowestMinPrice = 100000000.0f; 
	std::for_each( std::begin(iter->second), std::end(iter->second), [&](const std::shared_ptr<T_KlineDateItem>& entry)
    { 
		if( lowestMinPrice > entry->stk_item.low_price )
        {
            lowestMinPrice = entry->stk_item.low_price;
        }
    }); 
    return lowestMinPrice;
}

float StockAllDaysInfo::GetHisDataHighestMaxPrice(const std::string& stock)
{
	auto iter = stock_his_items_.find(stock);
	if( iter == stock_his_items_.end() )
		return 0.0;
	float higestMaxPrice = 0.0f; 
	std::for_each( std::begin(iter->second), std::end(iter->second), [&](const std::shared_ptr<T_KlineDateItem>& entry)
    { 
		if( higestMaxPrice < entry->stk_item.high_price )
        {
            higestMaxPrice = entry->stk_item.high_price;
        }
    }); 
	return higestMaxPrice;
}

 
void TraverseSetUpwardFractal( std::vector<std::shared_ptr<T_KlineDateItem> > &kline_data_items)
{
    int index = 1;
    while( index < kline_data_items.size() - 1 )
    {
        if( kline_data_items[index-1]->stk_item.low_price < kline_data_items[index]->stk_item.low_price
            || kline_data_items[index+1]->stk_item.low_price < kline_data_items[index]->stk_item.low_price )
        {
            ++index;
            continue;
        }
        int n_fractal_ahead = 0;
        int n_fractal_follow = 0;
        // search fractal ahead  -----------
        int index_to_check = index;
        for( int k = index_to_check - 1; k > 0; )
        {
            if( kline_data_items[k]->stk_item.low_price > kline_data_items[index_to_check]->stk_item.low_price )
            { 
                if( kline_data_items[k]->stk_item.high_price > kline_data_items[index_to_check]->stk_item.high_price )
                { 
                    ++n_fractal_ahead;
                    index_to_check = k;
                } 
                --k;
            }else
            { 
                break;
            }
            
        }
         
        if( n_fractal_ahead > 0 )
        {   // search fractal follow  --------  
            index_to_check = index;
            for( int k = index + 1; k < kline_data_items.size(); )
            {
                if( kline_data_items[k]->stk_item.low_price > kline_data_items[index_to_check]->stk_item.low_price )
                {
                    if( kline_data_items[k]->stk_item.low_price > kline_data_items[index_to_check]->stk_item.high_price )
                    {
                        // it's transfer k line 
                    }else if( kline_data_items[k]->stk_item.high_price > kline_data_items[index_to_check]->stk_item.high_price )
                    {
                        //kline_data_items[k]->type |= UPWARD_FRACTAL;
                        ++n_fractal_follow;
                        index_to_check = k; 
                    } /* {else
                       kline_data_items[k]->type |= INSUFFIC_FRACTAL; 
                       }*/
                    ++k;
                     
                }else
                    break;
            }
        }

        if( n_fractal_ahead > 0 && n_fractal_follow > 0 )
        {
            kline_data_items[index]->type |= BTM_AXIS_T_3;
            if( n_fractal_ahead > 1 && n_fractal_follow > 1 )
            {
                kline_data_items[index]->type |= BTM_AXIS_T_5;
                if( n_fractal_ahead > 2 && n_fractal_follow > 2 )
                {
                    kline_data_items[index]->type |= BTM_AXIS_T_7;
                    if( n_fractal_ahead > 3 && n_fractal_follow > 3 )
                    {
                        kline_data_items[index]->type |= BTM_AXIS_T_9;
                        if( n_fractal_ahead > 4 && n_fractal_follow > 4 )
                        {
                            kline_data_items[index]->type |= BTM_AXIS_T_11;
                        }
                    }
                }
            }
        }
        ++index;
    }//while
}

void TraverseSetDownwardFractal( std::vector<std::shared_ptr<T_KlineDateItem> > &kline_data_items)
{
    int index = 1;
    while( index < kline_data_items.size() - 1 )
    {
        if( kline_data_items[index-1]->stk_item.high_price > kline_data_items[index]->stk_item.high_price
            || kline_data_items[index+1]->stk_item.high_price > kline_data_items[index]->stk_item.high_price )
        {
            ++index;
            continue;
        }
        int n_fractal_ahead = 0;
        int n_fractal_follow = 0;
        // search fractal ahead  -----------
        int index_to_check = index;
        for( int k = index_to_check - 1; k > 0; )
        {
            if( kline_data_items[k]->stk_item.high_price < kline_data_items[index_to_check]->stk_item.high_price )
            { 
                if( kline_data_items[k]->stk_item.low_price < kline_data_items[index_to_check]->stk_item.low_price )
                { 
                    ++n_fractal_ahead;
                    index_to_check = k;
                } 
                --k;
            }else
            { 
                break;
            }
            
        }
         
        if( n_fractal_ahead > 0 )
        {   // search fractal follow  --------  
            index_to_check = index;
            for( int k = index + 1; k < kline_data_items.size(); )
            {
                if( kline_data_items[k]->stk_item.high_price < kline_data_items[index_to_check]->stk_item.high_price )
                {
                    if( kline_data_items[k]->stk_item.high_price < kline_data_items[index_to_check]->stk_item.low_price )
                    {
                        // it's transfer k line 
                    }else if( kline_data_items[k]->stk_item.low_price < kline_data_items[index_to_check]->stk_item.low_price )
                    {
                        //kline_data_items[k]->type |= UPWARD_FRACTAL;
                        ++n_fractal_follow;
                        index_to_check = k; 
                    } /* {else
                       kline_data_items[k]->type |= INSUFFIC_FRACTAL; 
                       }*/
                    ++k;
                     
                }else
                    break;
            }
        }

        if( n_fractal_ahead > 0 && n_fractal_follow > 0 )
        {
            kline_data_items[index]->type |= TOP_AXIS_T_3;
            if( n_fractal_ahead > 1 && n_fractal_follow > 1 )
            {
                kline_data_items[index]->type |= TOP_AXIS_T_5;
                if( n_fractal_ahead > 2 && n_fractal_follow > 2 )
                {
                    kline_data_items[index]->type |= TOP_AXIS_T_7;
                    if( n_fractal_ahead > 3 && n_fractal_follow > 3 )
                    {
                        kline_data_items[index]->type |= TOP_AXIS_T_9;
                        if( n_fractal_ahead > 4 && n_fractal_follow > 4 )
                        {
                            kline_data_items[index]->type |= TOP_AXIS_T_11;
                        }
                    }
                }
            }
        }
        ++index;
    }//while
}