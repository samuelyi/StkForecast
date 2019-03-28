#include "stdafx.h"

#include <iostream>
#include <fstream>
#include <string>
#include <xstring>

#include <Windows.h>

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
 

#ifdef JASON_TEST
//#include <wchar.h>
std::wstring UTF8ToUnicode( const std::string & s);

//#define  RAPIDJSON_HAS_STDSTRING
/* {
"MsgSendFlag": 1,
"MsgErrorReason": "IDorpassworderror",
"MsgRef": 1,
"Info": [
{
"lots": 10,
"order_algorithm": "01",
"list_instrument_id": [
"cu1701",
"cu1701"
]
},
{
"lots": 11,
"order_algorithm": "01",
"list_instrument_id": [
"cu1701",
"cu1701"
]
}
]
}
*/
/*
 { "FavCodes" :[{ "code" : "000609", "name":"�е�Ͷ��"}
              , { "code" : "600196", "name":"����ҽҩ"}]
 }
*/

/*const*/ std::string cst_code_tag = "code";
/*const*/ std::string cst_name_tag = "name";
/*const*/ std::string cst_is_index_tag = "is_index";

void AppendRecord(const std::string &code, const std::string &name, bool is_index);

using namespace rapidjson;
using namespace std;
int main() 
{
    AppendRecord("600196", "����ҽҩ", false);
    return 0;
    // 1. Parse a JSON string into DOM.
    const char* json ="{\"Info\":[{\"lots\":10,\"order_algorithm\":\"01\",\"buy_close\":9000,\
                      \"spread_shift\":0,\"position_b_sell\":0,\"position_a_buy_today\":0,\
                      \"position_a_buy_yesterday\":0,\"sell_open\":-9000,\
  \"list_instrument_id\":[\"rb1705\",\"rb1701\"],\"position_b_buy_today\":0,\"buy_open\":-9000,\"position_a_sell_yesterday\":0,\"strategy_id\":\"02\",\"position_b_buy\":0,\"a_wait_price_tick\":1,\"trade_model\":\"boll_reversion\",\"b_wait_price_tick\":0,\"sell_close\":9000,\"only_close\":0,\"order_action_limit\":400,\"is_active\":1,\"lots_batch\":1,\"position_a_sell\":0,\"position_b_buy_yesterday\":0,\"user_id\":\"063802\",\"position_a_buy\":0,\"trader_id\":\"1601\",\"position_a_sell_today\":0,\"stop_loss\":0,\"position_b_sell_today\":0,\"position_b_sell_yesterday\":0,\"on_off\":0},{\"lots\":20,\"order_algorithm\":\"02\",\"buy_close\":9000,\"spread_shift\":0,\"position_b_sell\":0,\"position_a_buy_today\":0,\"position_a_buy_yesterday\":0,\"sell_open\":-9000,\"list_instrument_id\":[\"ni1705\",\"ni1701\"],\"position_b_buy_today\":0,\"buy_open\":-9000,\"position_a_sell_yesterday\":0,\"strategy_id\":\"01\",\"position_b_buy\":0,\"a_wait_price_tick\":1,\"trade_model\":\"boll_reversion\",\"b_wait_price_tick\":0,\"sell_close\":9000,\"only_close\":0,\"order_action_limit\":400,\"is_active\":1,\"lots_batch\":1,\"position_a_sell\":0,\"position_b_buy_yesterday\":0,\"user_id\":\"063802\",\"position_a_buy\":0,\"trader_id\":\"1601\",\"position_a_sell_today\":0,\"stop_loss\":0,\"position_b_sell_today\":0,\"position_b_sell_yesterday\":0,\"on_off\":0}],\"MsgSendFlag\":0,\"MsgErrorReason\":\"IDorpassworderror\",\"MsgRef\":1,\"MsgType\":3,\"MsgResult\":0}";
    //std::cout << json << std::endl;
    //std::cout << "\n" << std::endl;
    std::cout << "|==================|" << std::endl;
    std::cout << "||rapidjson output||" << std::endl;
    std::cout << "|==================|" << std::endl;
    Document doc;
    doc.SetObject();
    rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();

    doc.AddMember("MsgSendFlag", 1, allocator);
    doc.AddMember("MsgErrorReason", "IDorpassworderror", allocator);
    doc.AddMember("MsgRef", 1, allocator);

    rapidjson::Value info_array(rapidjson::kArrayType);

    for (int i = 0; i < 2; i++) {
        rapidjson::Value info_object(rapidjson::kObjectType);
        info_object.SetObject();
        info_object.AddMember("lots", 10 + i, allocator);
        info_object.AddMember("order_algorithm", "01", allocator);

        rapidjson::Value instrument_array(rapidjson::kArrayType);
        for (int j = 0; j < 2; j++) {
            rapidjson::Value instrument_object(rapidjson::kObjectType);
            instrument_object.SetObject();
            instrument_object.SetString("cu1701");
            instrument_array.PushBack(instrument_object, allocator);
        }
        info_object.AddMember("list_instrument_id", instrument_array, allocator);

        info_array.PushBack(info_object, allocator); 
    }
    doc.AddMember("Info", info_array, allocator);

    // 3. Stringify the DOM
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    doc.Accept(writer);
    std::cout << buffer.GetString() << std::endl;

    getchar();
    return 0;
}

void AppendRecord(const std::string &code, const std::string &name, bool is_index)
{
    Document doc;
    doc.SetObject();
    rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();

    rapidjson::Value code_array(rapidjson::kArrayType);

    rapidjson::Value code_object(rapidjson::kObjectType);
    code_object.SetObject(); 
    rapidjson::Value val;
    rapidjson::Value val0;
    code_object.AddMember(val.SetString(cst_code_tag.c_str(), allocator), val0.SetString(code.c_str(), allocator), allocator);
    code_object.AddMember(val.SetString(cst_name_tag.c_str(), allocator), val0.SetString(name.c_str(), allocator), allocator);
    code_object.AddMember(val.SetString(cst_is_index_tag.c_str(), allocator), is_index, allocator);
    code_array.PushBack(code_object, allocator);

    doc.AddMember("FavCodes", code_array, allocator);

    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    doc.Accept(writer);

    fstream fstr_obj;
    fstr_obj.open("c:/fav.json", ios::out | ios::trunc);
    if( fstr_obj.is_open() )
    {
        fstr_obj << buffer.GetString();
        fstr_obj.close();
    }
}

bool parse()
{
    //��������json��ʽ
        //1����json��ʽ�ַ���ת��
    StringBuffer buffer;

    string readdate;
    readdate = buffer.GetString();
    Document document;  
    document.Parse<0>(readdate.c_str());  

    //2,ȡ���Լ���Ҫ��ֵ
    Value &node1=document["name"];  
    cout<<"name:"<<node1.GetString()<<endl; 

    Value &node2=document["number"];  
    cout<<"number: "<<endl;  
    if(node2.IsArray())  
    {  
        for(int i=0;i<node2.Size();i++)  
            cout<<'\t'<<node2[i].GetInt()<<endl;  
    }  

    return true;
}

void filewrite_sample()
{
    StringBuffer s;
    fstream fstr_obj;
    fstr_obj.open("c:/test.json", ios::out | ios::trunc);
    if( fstr_obj.is_open() )
    {
        fstr_obj << s.GetString();
        fstr_obj.close();
    }
    getchar();

}


std::wstring UTF8ToUnicode( const std::string & s)
{
    wstring result;

    int n = MultiByteToWideChar( CP_UTF8, 0, s.c_str(), -1, NULL, 0 );
    wchar_t * buffer = new wchar_t[n];

    ::MultiByteToWideChar( CP_UTF8, 0, s.c_str(), -1, buffer, n );

    result = buffer;
    delete[] buffer;

    return result;
}

std::string WChar2Ansi(LPCWSTR pwszSrc)
{
    int nLen = 0;
    nLen = WideCharToMultiByte(CP_ACP, 0, pwszSrc, -1, NULL, 0, NULL, NULL);
    if (nLen<= 0) 
        return std::string("");

    char* pszDst = new char[nLen];
    if (NULL == pszDst)
        return std::string("");

    WideCharToMultiByte(CP_ACP, 0, pwszSrc, -1, pszDst, nLen, NULL, NULL);
    pszDst[nLen -1] = 0;
    std::string strTemp(pszDst);
    delete [] pszDst;

    return strTemp;
}

#endif