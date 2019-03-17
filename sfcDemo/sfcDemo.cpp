// sfcDemo.cpp : Defines the entry point for the console application.
// some body say that tuple is not ok for python 3.5 3.6

//#pragma execution_character_set("utf-8")  // ��������ʱ,��˾�

/* 
    //PyObject* arg1 = Py_BuildValue("i", 100); // ��������
    //PyObject* arg2 = Py_BuildValue("f", 3.14); // ����������
    //PyObject* arg3 = Py_BuildValue("s", "hello"); // �ַ�������

*/
#include "stdafx.h"

#if 0

#ifdef GET_DATA_DIRECT_USE_TUSHARE

#include <string>
#include <iostream>

#include "Python.h"
#include "frameobject.h"

#include <list>
#include <vector>

#include <algorithm>
#include <stdio.h>



#pragma comment(lib, "python36.lib")

using namespace std;


class ListA
{
public:
    int val;
};

bool compare( ListA *left, ListA *right)
{
    return left->val < right->val;
}

bool compare2( ListA &left, ListA &right)
{
    return left.val < right.val;
}
 

void printDict(PyObject* obj)
{
    if(!PyDict_Check(obj))
        return ;

    PyObject *k, *keys;
    keys = PyDict_Keys(obj);

    for(int i=0; i < PyList_GET_SIZE(keys); i++)
    {
        k = PyList_GET_ITEM(keys, i);
        PyObject* pyStr = PyUnicode_AsEncodedString(k, "utf-8", "error");
        const char *strExcType = PyBytes_AS_STRING(pyStr);
        //char *c_name = PyString_AsString(k);
        printf("%s\n", strExcType);
    }
}

int start()
{

#if 1 
    std::list<ListA> list_obj;
    //std::sort(list_obj.begin(),  list_obj.end(), compare2);
    list_obj.sort(compare2);

#endif
#if 0
    std::vector<ListA> vec_obj;
    std::sort(vec_obj.begin(),  vec_obj.end(), compare2);
#endif
    int r = Py_IsInitialized();  //1Ϊ�Ѿ���ʼ����
    if (r != 0)
    {
        cout << "init python fail " << endl;
        return 0;
    }
     
    //Py_SetPythonHome(L"C:\\Python35");
    Py_Initialize(); //��ʼ��
    auto p_main_Module = PyImport_ImportModule("__main__");
    if (!p_main_Module)
    {
        throw "";
    }
    auto pDict = PyModule_GetDict(p_main_Module);
    if ( !pDict ) 
    {          
        return -1;    
    }     
    //PyArg_ParseTuple(
     
     PyObject* pList = PyList_New(3); // new reference  
    bool ret = PyList_Check(pList);
    //assert(PyList_Check(pList)); 

    PyRun_SimpleString("print(\"hello\"\n)");
    PyRun_SimpleString("print('hello')");
         
#if 0
    PyRun_SimpleString("import sys");

    string path = "D:\\ProgramFilesBase\\Python\\Python36-32\\Lib";
    string chdir_cmd = string("sys.path.append(\"") + path + "\")";
    const char* cstr_cmd = chdir_cmd.c_str(); 
    PyRun_SimpleString(cstr_cmd);

    //����ģ��  
    //PyObject* pModule = PyImport_ImportModule("test"); 
    PyObject* pModule = PyImport_ImportModule("ddd"); 
    if (!pModule)  
    {  
        cout<<"Python get tushare module failed." << endl;  
        return 0;  
    }  
     
    PyObject* pv = PyObject_GetAttrString(pModule, "wwycreatefunc");   
    if (!pv || !PyCallable_Check(pv))  
    {  
        cout << "Can't find funftion (_add)" << endl;  
        return 0;  
    }  
      
    //PyObject* pobj1 = Py_BuildValue("(s)", "hello");
     PyObject *args = PyTuple_New(1);
     PyObject *arg0 = Py_BuildValue("s", "hello");
     PyTuple_SetItem(args, 0, arg0);
     PyObject* pRet = PyEval_CallObject(pv, args);  
     auto val = Py_TYPE(pRet);
    char *result;
    PyArg_Parse(pRet, "s", &result);
    printf("PyEval_CallObject get %s", result);

#elif 1
    // ��Python����·���л���������ģ������Ŀ¼��һ��Ҫ��֤·��������ȷ��
    string path = "D:\\ProgramFilesBase\\Python\\Python36-32\\Lib\\site-packages\\tushare";
    string chdir_cmd = string("sys.path.append(\"") + path + "\")";
    const char* cstr_cmd = chdir_cmd.c_str();
    PyRun_SimpleString("import sys");
    PyRun_SimpleString(cstr_cmd);

    //����ģ��  
    PyObject* pModule = PyImport_ImportModule("tushare"); 
    if (!pModule)  
    {  
        cout<<"Python get tushare module failed." << endl;  
        return 0;  
    }  
    auto pDict1 = PyModule_GetDict(pModule);
    if ( !pDict1 ) 
    {          
        return -1;    
    }    
    //printDict(pDict1);
    //��ȡInsertģ����_add����  
    PyObject* pv = PyObject_GetAttrString(pModule, "get_k_data");  
    if (!pv || !PyCallable_Check(pv))  
    {  
        cout << "Can't find funftion (_add)" << endl;  
        return 0;  
    }  
    cout << "Get function (_add) succeed." << endl;  
      
#if 1 

    PyObject *args = PyTuple_New(1);
    PyObject *arg0 = Py_BuildValue("s", "002337");
    PyTuple_SetItem(args, 0, arg0);
    PyObject* pRet = PyEval_CallObject(pv, args);

#endif 
    if (pRet)  
    {   
        int list_len = PyObject_Size(pRet);//�б��� 
        PyObject *list_item = NULL;//python���͵��б�Ԫ��
         
        for (int i = 0; i < list_len; i++)
        {
            PyObject *key = nullptr;
            PyObject *key1 = nullptr;
            auto val = Py_TYPE(pRet);
        list_item = PyObject_GetItem(pRet, key);//�����±�ȡ��python�б��е�Ԫ��
        list_item = PyDict_GetItem(pRet, key1);//�����±�ȡ��python�б��е�Ԫ��

        //str_item = PyString_AsString(list_item);//ת��Ϊc���͵����� python 2
         
        PyObject* str_exc_type = PyObject_Repr(list_item); //Now a unicodeobject
        PyObject* pyStr = PyUnicode_AsEncodedString(str_exc_type, "utf-8",
        "Error ~");
        const char *strExcType =  PyBytes_AS_STRING(pyStr);
       /* Py_XDECREF(str_exc_type);
        Py_XDECREF(pyStr);*/
/*
        Py_XDECREF(exc_type);
        Py_XDECREF(exc_value);
        Py_XDECREF(exc_tb);*/

        printf("%s\n", strExcType);
        }

        int nTupleSize = PyTuple_Size(pRet);

        PyObject *list1;
#if 0
        PyArg_Parse(pRet, "O", &list1);
        // PyList_CheckExact
        if(PyList_Check(list1))
        {
            printf( "yes it's list\n" );
        }
#endif
        PyObject  *p_obj;
        PyArg_Parse(pRet, "O", &p_obj);
        //PyObject_GetAttrString(p_obj, 
        if( PyDict_Check(p_obj) )
        {
            printf( "yes it's dict \n" );
        }

        char* ret_str;  
       
        auto ret1 = PyArg_Parse(pRet, "s", &ret_str);
        //����Ԫ��   
         int w = 0 , h = 0;  
        printf("%s, %d, %d\n", ret_str, w, h);  

        //������ֵת����long��  
        //long result = PyString_AsString(pRet);  // python 2
        //PyUnicode_FromString(
        //PyBytes_AS_STRING

        //pRet->encode('UTF-8')
       /* char *buf = nullptr;
        PyArg_Parse(pRet, "s", buf);
        cout << "result:" << buf;  */
    }  
#endif

#if 0

    //������ֵ:  
int size = PyList_Size(prrr);//prrr Ϊ�б�  
cout << "�����б�Ĵ�СΪ: " << size << endl;  
for(int i=0;i<size;++i)  
{  
    PyObject *pNewAge = PyList_GetItem(prrr,i);//�൱�� python�е�prrr[i]  
    char *  newAge;  
    PyArg_Parse(pNewAge, "s", &newAge);//��python���ַ���תΪc�ַ���  
    cout << newAge << endl;  
}  
  
#endif 
#if 0 
    //��ʼ��Ҫ����Ĳ�����args���óɴ�������������ģʽ  
    PyObject* pArgs = PyTuple_New(2);  
    //��Long������ת����Python�ɽ��յ�����  
    PyObject* arg1 = PyLong_FromLong(4);  
    PyObject* arg2 = PyLong_FromLong(3);  
  
    //��arg1����Ϊarg����ĵ�һ������  
    PyTuple_SetItem(pArgs, 0, arg1);  
    //��arg1����Ϊarg����ĵڶ�������  
    PyTuple_SetItem(pArgs, 1, arg2);  
  
    //����������ú���������ȡ����ֵ  
    PyObject* pRet = PyObject_CallObject(pv, pArgs);  
  
    if (pRet)  
    {  
        //������ֵת����long��  
        long result = PyLong_AsLong(pRet);  
        cout << "result:" << result;  
    }  
    //int retok = PyArg_Parse(pyRet, "i", &ok); // �ӷ���ֵ��ȡ��int�ͷ���ֵ  
#endif
     //Py_DECREF(pArgs);  
     //Py_DECREF(pModule); 
     //Py_DECREF(pModule); 
     return 0;
}
void end()
{
    Py_Finalize(); //����
}

int main(int argc, char* argv[])
{
    start();

    end();
    getchar();
	return 0;
}

#endif
#endif