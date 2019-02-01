
#include "stdafx.h"

#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

#include "TradeApi-M.h"

//
//
//

class CAccountInfo
{
public:
    CAccountInfo(
        int nQsid,
        const char *pszHost,
        short nPort,
        const char *pszVersion,
        short nYybId,
        char nAccountType,
        const char* pszAccountNo,
        const char* pszTradeAccount,
        const char* pszJyPassword,
        const char* pszTxPassword)
        : m_nQsid(nQsid),
          m_sHost(pszHost),
          m_nPort(nPort),
          m_sVersion(pszVersion),
          m_nYybId(nYybId),
          m_nAccountType(nAccountType),
          m_sAccountNo(pszAccountNo),
          m_sTradeAccount(pszTradeAccount),
          m_sJyPassword(pszJyPassword),
          m_sTxPassword(pszTxPassword)
    {
    }

public:
    int m_nQsid;
    std::string m_sHost;
    short m_nPort;
    std::string m_sVersion;
    short m_nYybId;
    char m_nAccountType;
    std::string m_sAccountNo;
    std::string m_sTradeAccount;
    std::string m_sJyPassword;
    std::string m_sTxPassword;
};

//
//

void StringReplace(std::string &strBase, const std::string &strSrc, const std::string &strDest)
{
    std::string::size_type pos = 0;
    std::string::size_type srcLen = strSrc.size();
    std::string::size_type desLen = strDest.size();

    pos = strBase.find(strSrc, pos);
    while ((pos != std::string::npos))
    {
        strBase.replace(pos, srcLen, strDest);
        pos=strBase.find(strSrc, (pos+desLen));
    }
}

//#ifdef DEMO
#if 1

char *FilterResult(char *pszResult)
{
    return pszResult;
}

//#error �������˺Ų����滻�滻�����Լ���,�滻�ú�,������ע�͵�

CAccountInfo a0(32, // ȯ�̱��
                "115.238.90.116", //"180.153.18.180", // ȯ�̽��׷�����IP
                7708, // ȯ�̽��׷������˿�
                "8.27", // ����ͨ���ſͻ��˵İ汾��
                1, // Ӫҵ������  2:������ȯ
                8, // �˺�����
                "880003767427", // �����ĵ�¼�˺ţ�ȯ��һ��ʹ���ʽ��ʻ���ͻ���
                "880003767427", // �����˺ţ�һ�����¼�ʺ���ͬ. ���¼ȯ��ͨ�����������ѯ�ɶ��б��ɶ��б��ڵ��ʽ��ʺž��ǽ����ʺ�
                "737372", // ��������
                ""); // ͨѶ����

CAccountInfo a1(32, // ȯ�̱��
                "115.238.90.116", //"180.153.18.180", // ȯ�̽��׷�����IP
                7708, // ȯ�̽��׷������˿�
                "8.27", // ����ͨ���ſͻ��˵İ汾��
                1, // Ӫҵ������  2:������ȯ
                8, // �˺�����
                "880003767427", // �����ĵ�¼�˺ţ�ȯ��һ��ʹ���ʽ��ʻ���ͻ���
                "880003767427", // �����˺ţ�һ�����¼�ʺ���ͬ. ���¼ȯ��ͨ�����������ѯ�ɶ��б��ɶ��б��ڵ��ʽ��ʺž��ǽ����ʺ�
                "737372", // ��������
                ""); // ͨѶ����


CAccountInfo a2(32, // ȯ�̱��
                "115.238.90.116", //"180.153.18.180", // ȯ�̽��׷�����IP
                7708, // ȯ�̽��׷������˿�
                "8.27", // ����ͨ���ſͻ��˵İ汾��
                1, // Ӫҵ������  2:������ȯ
                8, // �˺�����
                "880003767427", // �����ĵ�¼�˺ţ�ȯ��һ��ʹ���ʽ��ʻ���ͻ���
                "880003767427", // �����˺ţ�һ�����¼�ʺ���ͬ. ���¼ȯ��ͨ�����������ѯ�ɶ��б��ɶ��б��ڵ��ʽ��ʺž��ǽ����ʺ�
                "737372", // ��������
                ""); // ͨѶ����

CAccountInfo a3(32, // ȯ�̱��
                "115.238.90.116", //"180.153.18.180", // ȯ�̽��׷�����IP
                7708, // ȯ�̽��׷������˿�
                "8.27", // ����ͨ���ſͻ��˵İ汾��
                1, // Ӫҵ������  2:������ȯ
                8, // �˺�����
                "880003767427", // �����ĵ�¼�˺ţ�ȯ��һ��ʹ���ʽ��ʻ���ͻ���
                "880003767427", // �����˺ţ�һ�����¼�ʺ���ͬ. ���¼ȯ��ͨ�����������ѯ�ɶ��б��ɶ��б��ڵ��ʽ��ʺž��ǽ����ʺ�
                "737372", // ��������
                ""); // ͨѶ����

#else

#include "../deps/TradeXPrivate.cpp"

#endif


//
//
//

void SplitStrToVector(std::vector<std::string> &sVec, const std::string &sStr, const std::string &sSep)
{
    std::string::size_type i = 0;
    std::string::size_type j = sStr.find(sSep);

    while (j != std::string::npos)
    {
        sVec.push_back(sStr.substr(i, j-i));

        i = j + sSep.length();
        j = sStr.find(sSep, j + sSep.length());
    }

    if (j == std::string::npos)
        sVec.push_back(sStr.substr(i, sStr.length()));
}


class CTdxResult
{
public:
    std::map<std::string, int> m_mapHeader;

    std::vector<std::string> m_vecHeader;
    std::vector<std::vector<std::string> > m_vecContent;

public:
    CTdxResult(const std::string &sResult, const std::string &sLineSep = "\n", const std::string &sFieldSep = "\t")
    {
        std::vector<std::string> vecInfo;

        SplitStrToVector(vecInfo, sResult, sLineSep);

        if (vecInfo.empty())
            return;

        //
        //
        SplitStrToVector(m_vecHeader, vecInfo[0], sFieldSep);

        for (unsigned int i=0; i<m_vecHeader.size(); ++i)
        {
            char szBuff[10];

            if (m_vecHeader[i].empty())
            {
                sprintf(szBuff, "i%d", i);
                m_vecHeader[i] = szBuff;
            }

            m_mapHeader[m_vecHeader[i]] = i;
        }

        //
        //
        std::vector<std::string> vecFields;

        for (unsigned int i=1; i<vecInfo.size(); ++i)
        {
            vecFields.clear();

            SplitStrToVector(vecFields, vecInfo[i], sFieldSep);

            if (vecFields.size() < m_vecHeader.size())
                continue;

            m_vecContent.push_back(vecFields);
        }
    }

    int GetRowNum()
    {
        return m_vecContent.size();
    }

    int GetColNum()
    {
        return m_vecHeader.size();
    }

    int GetIndexByTitle(const std::string sTitle)
    {
        std::map<std::string, int>::iterator iter;

        iter = m_mapHeader.find(sTitle);
        if (iter == m_mapHeader.end())
            return -1;

        return iter->second;
    }

    std::string GetValue(int nRow, const std::string &sTitle)
    {
        if (nRow >= m_vecContent.size())
            return "";

        int nIndex = GetIndexByTitle(sTitle);
        if (nIndex < 0)
            return "";

        return m_vecContent[nRow][nIndex];
    }
};

//
//

class CTestTdx
{
public:
    CTestTdx(const CAccountInfo &account)
        : m_nQsid(account.m_nQsid),
          m_sHost(account.m_sHost),
          m_sVersion(account.m_sVersion),
          m_nPort(account.m_nPort),
          m_nYybId(account.m_nYybId),
          m_nAccountType(account.m_nAccountType),
          m_sAccountNo(account.m_sAccountNo),
          m_sTradeAccount(account.m_sTradeAccount),
          m_sJyPassword(account.m_sJyPassword),
          m_sTxPassword(account.m_sTxPassword)
    {
        m_nClientID = -1;

        memset(m_szResult, 0, sizeof(m_szResult));
        memset(m_szErrInfo, 0, sizeof(m_szErrInfo));
    }

	int GetClientID()
	{
		return m_nClientID;
	}

    ~CTestTdx()
    {
        if (m_nClientID >= 0)
            XLogoff();
    }

    bool XLogin()
    {
        int nClientID;

        nClientID = Logon(m_nQsid,
                          m_sHost.c_str(),
                          m_nPort,
                          m_sVersion.c_str(),
                          m_nYybId,
                          m_nAccountType,
                          m_sAccountNo.c_str(),
                          m_sTradeAccount.c_str(),
                          m_sJyPassword.c_str(),
                          m_sTxPassword.c_str(),
                          m_szErrInfo);
        if (nClientID < 0)
        {
            cout << "Login fail ! " << m_szErrInfo << endl;
            return 0;
        }

        m_nClientID = nClientID;

        cout << "Login to " << m_sAccountNo << " ok ! <" << m_nClientID << ">" << endl;
        cout << "\tConnectOK - " << IsConnectOK(nClientID) << endl;
        return 1;
    }

    bool XQueryData(int nCategory)
    {
        if (m_nClientID < 0)
        {
            cout << "<" << m_nClientID << "> δ��¼ !" << endl;
            return 0;
        }

        int nRet = QueryData(m_nClientID, nCategory, m_szResult, m_szErrInfo);
        if (nRet < 0)
        {
            cout << "<" << m_nClientID << "> QueryData fail ! " << endl;
            cout << m_szErrInfo << endl;
            return 0;
        }

        cout << "<" << m_nClientID << "> QueryData ok ! " << endl;
        cout << FilterResult(m_szResult) << endl;
        return 1;
    }

    bool XShareHolder()
    {
        if (m_nClientID < 0)
        {
            cout << "<" << m_nClientID << "> δ��¼ !" << endl;
            return 0;
        }

        cout << "*** " << m_nClientID << endl;

        int nRet = QueryData(m_nClientID, 5, m_szResult, m_szErrInfo);
        if (nRet < 0)
        {
            cout << "<" << m_nClientID << "> QueryData fail ! " << endl;
            cout << m_szErrInfo << endl;
            return 0;
        }

        //
        //

        CTdxResult share_holder(m_szResult);

        for (int i=0; i<share_holder.GetRowNum(); ++i)
        {
            std::string sAccountType = share_holder.GetValue(i, "�ʺ����");

            if (sAccountType == "0")
            {
                m_sShareHolderSZ = share_holder.GetValue(i, "�ɶ�����");
                cout << "<" << m_nClientID << "> ����-�ɶ�����=" << m_sShareHolderSZ << endl;
            }
            else if (sAccountType == "1")
            {
                m_sShareHolderSH = share_holder.GetValue(i, "�ɶ�����");
                cout << "<" << m_nClientID << "> �Ϻ�-�ɶ�����=" << m_sShareHolderSH << endl;
            }
        }

        cout << "<" << m_nClientID << "> QueryData ok ! " << endl;
        cout << FilterResult(m_szResult) << endl;
        return 1;
    }

    /*
    int GetTradableQuantity(
        char nCategory,
        int nPriceType,
        const char *pszGddm,
        const char *pszZqdm,
        float fPrice,
        char *pszResult,
        char *pszErrInfo);
        */

    bool XGetTradableQuantity()
    {
        if (m_nClientID < 0)
        {
            cout << "<" << m_nClientID << "> δ��¼ !" << endl;
            return 0;
        }

        cout << "<" << m_nClientID << "> 601390 �м� ... " << endl;

        int nRet = GetTradableQuantity(m_nClientID, 0, 4, m_sShareHolderSH.c_str(), "601390", 8.87, m_szResult, m_szErrInfo);
        if (nRet < 0)
        {
            cout << "<" << m_nClientID << "> GetTradableQuantity fail ! " << endl;
            cout << m_szErrInfo << endl;
        }
        else
        {
            cout << "<" << m_nClientID << "> GetTradableQuantity ok ! " << endl;
            cout << m_szResult << endl;
        }

        return 1;
    }

    bool XSendOrder(int nMarket)
    {
        if (m_nClientID < 0)
        {
            cout << "<" << m_nClientID << "> δ��¼ !" << endl;
            return 0;
        }

        int nRet;

        if (nMarket)
        {
            cout << "<" << m_nClientID << "> 601988 �м� 100�� ... " << endl;

            nRet = SendOrder(m_nClientID, 0, 4, m_sShareHolderSH.c_str(), "601988", 0, 100, m_szResult, m_szErrInfo);
            if (nRet < 0)
            {
                cout << "<" << m_nClientID << "> SendOrder fail ! " << endl;
                cout << m_szErrInfo << endl;
            }
            else
            {
                cout << "<" << m_nClientID << "> SendOrder ok ! " << endl;
                cout << m_szResult << endl;
            }
        }
        else
        {
            cout << "<" << m_nClientID << "> 000001 �м� 100�� ... " << endl;

            nRet = SendOrder(m_nClientID, 0, 4, m_sShareHolderSZ.c_str(), "000001", 0, 100, m_szResult, m_szErrInfo);
            if (nRet < 0)
            {
                cout << "<" << m_nClientID << "> SendOrder fail ! " << endl;
                cout << m_szErrInfo << endl;
            }
            else
            {
                cout << "<" << m_nClientID << "> SendOrder ok ! " << endl;
                cout << m_szResult << endl;
            }
        }

        return 1;
    }

    void XLogoff()
    {
        if (m_nClientID < 0)
        {
            cout << "<" << m_nClientID << "> δ��¼ !" << endl;
            return;
        }

        Logoff(m_nClientID);

        cout << "<" << m_nClientID << "> Logoff !" << endl;

        m_nClientID = -1;
    }


private:

    int m_nQsid;

    std::string m_sHost;
    int m_nPort;

    std::string m_sVersion;

    int m_nYybId;
    int m_nAccountType;

    std::string m_sAccountNo;
    std::string m_sTradeAccount;
    std::string m_sJyPassword;
    std::string m_sTxPassword;

    int m_nClientID;

    std::string m_sShareHolderSZ;
    std::string m_sShareHolderSH;

    char m_szResult[1024*1024];
    char m_szErrInfo[1024];
};


#define MAX_BATCH_NUM   4

char g_szErrInfo[256];

int test_trade_multi_funcs()
{
    std::vector<CTestTdx *> vecTdx(MAX_BATCH_NUM);

    if (OpenTdx(14, "6.40", 12, 0, g_szErrInfo) < 0)
    {
        std::cout << "error! " << g_szErrInfo << std::endl;
        return 0;
    }

    //
    //

    vecTdx[0] = new CTestTdx(a0); // test
    vecTdx[1] = new CTestTdx(a1);
    vecTdx[2] = new CTestTdx(a2);
    vecTdx[3] = new CTestTdx(a3);

    //
    //

    cout << "\t 0 - Logon ...\n" << endl;

    for (int i=0; i<MAX_BATCH_NUM; i++)
        vecTdx[i]->XLogin();

    cout << endl;
    cout << "\t���س�������......\n";
    cin.get();

	if (1)
	{
		int nCategory[] = { 0, 1, 2 };
		int nCount = 3;

		char *pszResultOK[3];
		char *pszResultFail[3];
		char *pszErrInfo;
		
		// alloc memory

		for (int i=0; i<3; i++)
		{
			pszResultOK[i] = new char[4096];
		}

		for (int i=0; i<3; i++)
		{
			pszResultFail[i] = new char[256];
		}

		pszErrInfo = new char[256];

		// call 

		int ret = QueryDatas(vecTdx[1]->GetClientID(), nCategory, nCount, pszResultOK, pszResultFail, pszErrInfo);
		if (ret < 0)
		{
			printf("error: %s\n", pszErrInfo);
		}
		else
		{
			for (int i=0; i<3; i++)
			{
				printf("record %d\n", i);
				printf("\t%s\n", pszResultOK[i]);
				printf("\t%s\n", pszResultFail[i]);
			}
		}

		// free memory

		for (int i=0; i<3; i++)
		{ 
			delete []pszResultOK[i];
		}

		for (int i=0; i<3; i++)
		{
			delete pszResultFail[i];
		}

		delete []pszErrInfo;
	}

	if (1)
	{
		int nClientID[2];
		int nCategory[] = { 0, 0 };
		int nCount = 2;

		char *pszResultOK[2];
		char *pszResultFail[2];
		
		// alloc memory

		for (int i=0; i<2; i++)
		{
			pszResultOK[i] = new char[4096];
		}

		for (int i=0; i<2; i++)
		{
			pszResultFail[i] = new char[256];
		}

		// call 

		nClientID[0] = vecTdx[1]->GetClientID();
		nClientID[1] = vecTdx[2]->GetClientID();

		int ret = QueryMultiAccountsDatas(nClientID, nCategory, nCount, pszResultOK, pszResultFail);
		if (ret < 0)
		{
			printf("error");
		}
		else
		{
			for (int i=0; i<2; i++)
			{
				printf("record %d\n", i);
				printf("\t%s\n", pszResultOK[i]);
				printf("\t%s\n", pszResultFail[i]);
			}
		}

		// free memory

		for (int i=0; i<2; i++)
		{ 
			delete []pszResultOK[i];
		}

		for (int i=0; i<2; i++)
		{
			delete pszResultFail[i];
		}
	}


    //
    // ����
    //

    for (int i=0; i<MAX_BATCH_NUM; i++)
        delete vecTdx[i];

    //
    //
    CloseTdx();

	return 0;


    //
    //
    cout << "\t 0 - ShareHolder ...\n" << endl;

    for (int i=0; i<MAX_BATCH_NUM; i++)
    {
        vecTdx[i]->XShareHolder();
        cout << endl;
    }

    cout << endl;
    cout << "\t���س�������......\n";
    cin.get();

    //
    //

    if (1)
    {
        cout << "\t 0 - ��ѯ�ʽ� QueryData(nClientID, 0, Result, ErrInfo)\n" << endl;

        for (int i=0; i<MAX_BATCH_NUM; i++)
        {
            vecTdx[i]->XQueryData(0);
            cout << endl;
        }

        cout << endl;
        cout << "\t���س�������......\n";
        cin.get();

        //

        cout << "\t 1 - ��ѯ�ɷ�	 QueryData(nClientID, 1, Result, ErrInfo)\n" << endl;

        for (int i=0; i<MAX_BATCH_NUM; i++)
        {
            vecTdx[i]->XQueryData(1);
            cout << endl;
        }

        cout << endl;
        cout << "\t���س�������......\n";

        //

        cout << "\t 2 - ��ѯ����ί�� QueryData(nClientID, 2, Result, ErrInfo)\n" << endl;

        for (int i=0; i<MAX_BATCH_NUM; i++)
        {
            vecTdx[i]->XQueryData(2);
            cout << endl;
        }

        cout << endl;
        cout << "\t���س�������......\n";
        cin.get();

        //

        cout << "\t 3 - ��ѯ���ճɽ� QueryData(nClientID, 3, Result, ErrInfo)\n" << endl;

        for (int i=0; i<MAX_BATCH_NUM; i++)
        {
            vecTdx[i]->XQueryData(3);
            cout << endl;
        }

        cout << endl;
        cout << "\t���س�������......\n";
        cin.get();

        //

        cout << "\t 4 - ��ѯ�ɳ���	 QueryData(nClientID, 4, Result, ErrInfo)\n" << endl;

        for (int i=0; i<MAX_BATCH_NUM; i++)
        {
            vecTdx[i]->XQueryData(4);
            cout << endl;
        }

        cout << endl;
        cout << "\t���س�������......\n";
        cin.get();

        //

        cout << "\t 5 - ��ѯ�ɶ����� QueryData(nClientID, 5, Result, ErrInfo)\n" << endl;

        for (int i=0; i<MAX_BATCH_NUM; i++)
        {
            vecTdx[i]->XQueryData(5);
            cout << endl;
        }

        cout << endl;
        cout << "\t���س�������......\n";
        cin.get();
    }

    //
    //

    if (0)
    {
        cout << "\t 12 - ���깺�¹ɲ�ѯ QueryData(nClientID, 12, Result, ErrInfo)\n" << endl;

        for (int i=0; i<MAX_BATCH_NUM; i++)
        {
            vecTdx[i]->XQueryData(12);
            cout << endl;
        }

        cout << endl;
        cout << "\t���س�������......\n";
        cin.get();

        //

        cout << "\t 13 - �¹��깺��Ȳ�ѯ QueryData(nClientID, 13, Result, ErrInfo)\n" << endl;

        for (int i=0; i<MAX_BATCH_NUM; i++)
        {
            vecTdx[i]->XQueryData(13);
            cout << endl;
        }

        cout << endl;
        cout << "\t���س�������......\n";
        cin.get();

        //

        cout << "\t 14 - ��Ų�ѯ QueryData(nClientID, 14, Result, ErrInfo)\n" << endl;

        for (int i=0; i<MAX_BATCH_NUM; i++)
        {
            vecTdx[i]->XQueryData(14);
            cout << endl;
        }

        cout << endl;
        cout << "\t���س�������......\n";
        cin.get();

        //

        cout << "\t 15 - ��ǩ��ѯ QueryData(nClientID, 15, Result, ErrInfo)\n" << endl;

        for (int i=0; i<MAX_BATCH_NUM; i++)
        {
            vecTdx[i]->XQueryData(15);
            cout << endl;
        }

        cout << endl;
        cout << "\t���س�������......\n";
        cin.get();
    }


    //
    //

    if (1)
    {
        cout << "\t 12 - �ɽ���������ѯ XGetTradableQuantity ...\n" << endl;

        for (int i=0; i<MAX_BATCH_NUM; i++)
        {
            vecTdx[i]->XGetTradableQuantity();
            cout << endl;
        }

        cout << endl;
        cout << "\t���س�������......\n";
        cin.get();
    }

    //
    //

    if (1)
    {
        cout << "\t 4 - SendOrder �������� ... " << endl;

        for (int i=0; i<MAX_BATCH_NUM; i++)
        {
            vecTdx[i]->XSendOrder(0);
            cout << endl;
        }

        cout << endl;
        cout << "\t���س�������......\n";
        cin.get();

        cout << "\t 4 - SendOrder �������� ... " << endl;

        for (int i=0; i<MAX_BATCH_NUM; i++)
        {
            vecTdx[i]->XSendOrder(1);
            cout << endl;
        }

        cout << endl;
        cout << "\t���س�������......\n";
        cin.get();
    }

    //
    //

    cout << "\t 7 - Logoff ...\n" << endl;

    for (int i=0; i<MAX_BATCH_NUM; i++)
        vecTdx[i]->XLogoff();

    cout << endl;
    cout << "\t���س�������......\n";
    cin.get();


    //
    // ����
    //

    for (int i=0; i<MAX_BATCH_NUM; i++)
        delete vecTdx[i];

    //
    //
    CloseTdx();

    return 1;
}


