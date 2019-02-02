
#include "stdafx.h"

#include "TradeX.h"

#include <iostream>
#include <regex>

using namespace std;

//#define F1  1 // TdxHq_GetSecurityCount
//#define F2  1 // TdxHq_GetSecurityList
//#define F3  1 // TdxHq_GetMinuteTimeData
#define F4  1 // TdxHq_GetSecurityBars
//#define F5  1 // TdxHq_GetHistoryMinuteTimeData
//#define F6  1 // TdxHq_GetIndexBars
//#define F7  1 // TdxHq_GetTransactionData
//#define F8  1 // TdxHq_GetHistoryTransactionData
//#define F9  1 // TdxHq_GetSecurityQuotes
//#define F10 1 // TdxHq_GetCompanyInfoCategory
//#define F11 1 // TdxHq_GetCompanyInfoContent
//#define F12 1 // TdxHq_GetXDXRInfo
//#define F13 1 // TdxHq_GetFinanceInfo

int test_hq_batch_funcs(const char *pszHqSvrIP, short nPort)
{
    //��ʼ��ȡ��������
    char* m_szResult = new char[1024 * 1024];
    char* m_szErrInfo = new char[256];
    short Count = 10;

    //���ӷ�����
    int nConn = TdxHq_Connect(pszHqSvrIP, nPort, m_szResult, m_szErrInfo);
    if (nConn < 0)
    {
        cout << m_szErrInfo << endl;
        return -1;
    }

    std::cout << m_szResult << std::endl;

    bool bool1;

#if F1
    cout << "\n*** TdxHq_GetSecurityCount\n";

    Count = -1;
    bool1 = TdxHq_GetSecurityCount(nConn, 0, &Count, m_szErrInfo);
    if (!bool1)
    {
        cout << m_szErrInfo << endl;//����ʧ��
        getchar();
        return 0;
    }

    cout << "Count = " << Count << endl;
    getchar();
#endif

#if F2
    cout << "\n*** TdxHq_GetSecurityList\n";

    Count = 100;
    bool1 = TdxHq_GetSecurityList(nConn, 0, 0, &Count, m_szResult, m_szErrInfo);
    if (!bool1)
    {
        cout << m_szErrInfo << endl;//����ʧ��
        getchar();
        return 0;
    }

    cout << "Count = " << Count << endl;
    cout << m_szResult << endl;
    getchar();
#endif

#if F3
    cout << "\n*** TdxHq_GetMinuteTimeData\n";

    //��ȡ��ʱͼ����
    bool1 = TdxHq_GetMinuteTimeData(nConn, 0, "000001",  m_szResult, m_szErrInfo);
    if (!bool1)
    {
        cout << m_szErrInfo << endl;
        return 0;
    }
    cout << m_szResult << endl;
    getchar();
#endif

#if F4
    cout << "\n*** TdxHq_GetSecurityBars\n";

    //��ȡ��ƱK������
    Count = 800;  //200 MAX IS 800 
    //<param name="nCategory">K������, 0->5����K��    1->15����K��    2->30����K��  3->1СʱK��    
    // 4->��K��  5->��K��  6->��K��  7->1����  8->1����K��  9->��K��  10->��K��  11->��K��< / param>
    //bool1 = TdxHq_GetSecurityBars(nConn, 8, 0, "000001", 100, &Count, m_szResult, m_szErrInfo);//��������, 0->5����K��    1->15����K��    2->30����K��  3->1СʱK��    4->��K��  5->��K��  6->��K��  7->1����K��  8->1����K��  9->��K��  10->��K��  11->��K��
    
    int kline_type = 5;  // if week kline the date stamp is Friday of each week
    bool1 = TdxHq_GetSecurityBars(nConn, kline_type/*nCategory*/, 1, "600196", 0/*start pos from back to front*/, &Count, m_szResult, m_szErrInfo);//��������, 0->5����K��    1->15����K��    2->30����K��  3->1СʱK��    4->��K��  5->��K��  6->��K��  7->1����K��  8->1����K��  9->��K��  10->��K��  11->��K��
    if( !bool1 )
    {
        cout << m_szErrInfo << endl;
        return 0;
    }
    if( strlen(m_szResult) < 1 )
    {
        std::cout << " result empty !" << std::endl;
        return 0;
    }

    bool has_time = ( kline_type < 4 || kline_type == 7 || kline_type == 8 ) ? true : false;
    std::string expresstion_str;
    if( has_time )
        expresstion_str = "^(\\d{4}-\\d{2}-\\d{2})\\s(\\d{2}:\\d{2})\\t(\\d+\\.\\d+)\\t(\\d+\\.\\d+)\\t(\\d+\\.\\d+)\\t(\\d+\\.\\d+)\\t(\\d+)\\t(\\d+\\.\\d+)$";
    else
        expresstion_str = "^(\\d{8})\\t(\\d+\\.\\d+)\\t(\\d+\\.\\d+)\\t(\\d+\\.\\d+)\\t(\\d+\\.\\d+)\\t(\\d+)\\t(\\d+\\.\\d+)$";

    std::regex  regex_obj(expresstion_str);
    char *p = m_szResult;
    while( *p != '\0' && *p != '\n') ++p;
    ++p;

    char *p_line_beg = p;
    while( *p != '\0')
    {
        p_line_beg = p;
        while( *p != '\0' && *p != '\n')++p;
        *p = '\0';
        ++p;
        std::string src_str = p_line_beg;

        std::smatch  match_result;
        if( std::regex_match(src_str.cbegin(), src_str.cend(), match_result, regex_obj) )
        {
            int index = 1;
            std::cout << match_result[index] << " "; // date
            if( has_time )
                std::cout << match_result[++index] << " "; // time
            std::cout << match_result[++index] << " "; // open 
            std::cout << match_result[++index] << " "; // close 
            std::cout << match_result[++index] << " "; // high
            std::cout << match_result[++index] << " "; // low
            std::cout << match_result[++index] << " "; // vol
            std::cout << match_result[++index] << " " << std::endl; // amount
        }
    }
    
    cout << m_szResult << endl;
    getchar();
#endif

#if F5
    cout << "\n*** TdxHq_GetHistoryMinuteTimeData\n";

    //��ȡ��ʷ��ʱͼ����
    bool1 = TdxHq_GetHistoryMinuteTimeData(nConn, 1, "600196", 20140904, m_szResult, m_szErrInfo);
    //bool1 = TdxHq_GetHistoryMinuteTimeData(nConn, 0, "000001", 20140904, m_szResult, m_szErrInfo);
    if (!bool1)
    {
        cout << m_szErrInfo << endl;
        return 0;
    }
    cout << m_szResult << endl;
    getchar();
#endif

#if F6
    cout << "\n*** TdxHq_GetIndexBars\n";

    //��ȡָ��K������
    bool1 = TdxHq_GetIndexBars(nConn, 4, 1, "000001", 0, &Count, m_szResult, m_szErrInfo);//��������, 0->5����K��    1->15����K��    2->30����K��  3->1СʱK��    4->��K��  5->��K��  6->��K��  7->1����K��     8->1����K��    9->��K��  10->��K��  11->��K��
    if (!bool1)
    {
        cout << m_szErrInfo << endl;
        return 0;
    }
    cout << m_szResult << endl;
    getchar();
#endif

#if F7
    cout << "\n*** TdxHq_GetTransactionData\n";

    //��ȡ�ֱ�ͼ����
    bool1 = TdxHq_GetTransactionData(nConn, 0, "000001", 0, &Count, m_szResult, m_szErrInfo);
    if (!bool1)
    {
        cout << m_szErrInfo << endl;
        return 0;
    }
    cout << m_szResult << endl;
    getchar();
#endif

#if F8
    cout << "\n*** TdxHq_GetHistoryTransactionData\n";

    //��ȡ��ʷ�ֱ�ͼ����
    bool1 = TdxHq_GetHistoryTransactionData(nConn, 0, "000001", 0, &Count, 20140904,  m_szResult, m_szErrInfo);
    if (!bool1)
    {
        cout << m_szErrInfo << endl;
        return 0;
    }

    cout << m_szResult << endl;
    getchar();
#endif

#if F9
    cout << "\n*** TdxHq_GetSecurityQuotes\n";

    //��ȡ�嵵��������
    char xMarket[] = {0,1};
    const char* Zqdm[] = {"000001","600030"};
    short ZqdmCount = 2;
    bool1 = TdxHq_GetSecurityQuotes(nConn, xMarket, Zqdm, &ZqdmCount, m_szResult, m_szErrInfo);
    if (!bool1)
    {
        cout << m_szErrInfo << endl;
        return 0;
    }
    cout << m_szResult << endl;

    getchar();
#endif

#if F10
    cout << "\n*** TdxHq_GetCompanyInfoCategory\n";

    //��ȡF10���ݵ����
    bool1 = TdxHq_GetCompanyInfoCategory(nConn, 0, "000001", m_szResult, m_szErrInfo);
    if (!bool1)
    {
        cout << m_szErrInfo << endl;
        return 0;
    }
    cout << m_szResult << endl;

    getchar();
#endif

#if F11
    cout << "\n*** TdxHq_GetCompanyInfoContent\n";

    //��ȡF10���ݵ�ĳ��������
    bool1 = TdxHq_GetCompanyInfoContent(nConn, 1, "600030", "600030.txt", 142577, 5211, m_szResult, m_szErrInfo);
    if (!bool1)
    {
        cout << m_szErrInfo << endl;
        return 0;
    }
    cout << m_szResult << endl;

    getchar();
#endif

#if F12
    cout << "\n*** TdxHq_GetXDXRInfo\n";

    //��ȡ��Ȩ��Ϣ��Ϣ
    bool1 = TdxHq_GetXDXRInfo(nConn, 0, "000001", m_szResult, m_szErrInfo);
    if (!bool1)
    {
        cout << m_szErrInfo << endl;
        return 0;
    }
    cout << m_szResult << endl;

    getchar();
#endif

#if F13
    cout << "\n*** TdxHq_GetFinanceInfo\n";

    //��ȡ������Ϣ
    bool1 = TdxHq_GetFinanceInfo(nConn, 0, "000001", m_szResult, m_szErrInfo);
    if (!bool1)
    {
        cout << m_szErrInfo << endl;
        return 0;
    }
    cout << m_szResult << endl;

    getchar();
#endif

    TdxHq_Disconnect(nConn);

    cout << "�Ѿ��Ͽ����������" << endl;

    getchar();
    return 0;
}

