/********************************************************************
 File: gateCmdHandler.h
 Function: Transfer the source data to the target data. 
           Output the target data.
 Author: Luobihe
 Date: 2016-1-4
*********************************************************************/

#ifndef __GATECMDHANDLER_H__
#define __GATECMDHANDLER_H__

#include <list>
using namespace std;

#include "termioManager.h"

#define MAX_DATA_LENGTH   258
#define MAX_INFO_LENGTH   64

#define FILE_DATA_TRANS   "data_trans.dat"

//��ʼ�����������ļ�
int initObj(void);

class CGateCmdHandler
{
private:
    static CGateCmdHandler* m_pInst;
    list <char*> m_listTransExp;

private:
    CGateCmdHandler(void); 
    void clearList(void);

    //�����ʽ�������������ת��������ִ��
    //0 -- success, -1 -- failed
    int cmdHandleSingleExp(const char* expression, 
        const char* srcInfo, char* in_data, int in_datalen);

    //���ݱ��ʽ��������Դ��Ϣ���������ݲ�������˿���Ϣ���������
    int tansDataFromRule(const char* expression, const char* srcInfo,
        char* in_data, int in_datalen, char* tarInfo, char* out_data);

    //����ִ��
    int putoutData(const char* tarInfo, char* out_data, int out_datalen);   

    int compareSrcInfo(const char* info_from_src, const char* info_from_exp);
    int compareInData(char* in_data, int in_datalen, const char* indata_from_exp);

    //��16���Ƹ�ʽ���ı���������
    //�ı���ʽΪ16���ƣ�ÿ�ֽ�ռ2λ������0x��ʼ���м��Կո�ָ�
    int genDataFromText(const char* data_text, char* out_data, int* datalen);

    int addExpression(const char* exp);

    //�ɶ˿��ַ���ʶ��ȡ�ýӿڲ��� 
    //0 -- success, -1 -- failed
    int getTermParas(const char* tarInfo, TerminalPara* p_paras);     

public:
    ~CGateCmdHandler(void);    

    static CGateCmdHandler* getInstance(void);

    //init ��ʼ�����������ļ�
    int init(void);

    //�����
    void cmdHandle(const char* srcInfo, char* in_data, int in_datalen);

    list <char*>* getList(void) {
        return &m_listTransExp;
    }    
};

#endif  //__GATECMDHANDLER_H__