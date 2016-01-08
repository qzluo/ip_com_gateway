/********************************************************************
 File: logsys.h
 Function: �ṩд��־�Ľӿ�.   
    ��־��ʽ���£�
    [yyyy-mm-dd HH:MM:SS] [loglevel] [info]
 Author: Luobihe
 Date: 2015-7-3
*********************************************************************/

#ifndef __LOGSYS_H__
#define __LOGSYS_H__

#ifdef __cplusplus
extern "C"
{
#endif

//��ӡ�������
#define LOG_EMERGENCY        0
#define LOG_ALARM            1
#define LOG_CRIT             2
#define LOG_ERR              3
#define LOG_WARNING          4
#define LOG_NOTICE           5
#define LOG_INFO             6
#define LOG_DEBUG            7

/*-------------------------------------------------------------------
 Function: loginit(filename, outlevel)
 Purpose: ��ʼ����־ϵͳ
 Parameters:
 return: 0 --  �ɹ�
         -1 -- ʧ��
-------------------------------------------------------------------*/
int loginit(const char* filename, int outlevel);


/*-------------------------------------------------------------------
 Function: logout(...)
 Purpose: д��־��Ϣ���ļ��������
 Parameters: level -- [IN], ��ӡ��־�ļ���
             info -- [IN], �������Ϣ
             filename -- [IN], ������־���ļ���
             line -- [IN], ������־���к�          
 return: 0 --  �ɹ�
         -1 -- ʧ��
-------------------------------------------------------------------*/
int logout(int level, const char* info, 
           const char* filename, int line);


#ifdef __cplusplus
}
#endif

#endif  //__LOGSYS_H__