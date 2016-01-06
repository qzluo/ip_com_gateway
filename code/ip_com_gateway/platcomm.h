/********************************************************************
 File: platcomm.h
 Function: �ṩ����ʹ�õĺ����Ľӿ�. 
 Author: Luobihe
 Date: 2015-7-9
*********************************************************************/

#ifndef __PLATCOMM_H__
#define __PLATCOMM_H__

#ifdef _WIN32
#include <Windows.h>
#else
#include <pthread.h>
#endif

#define TCP_LISTEN_NUM  50    //tcp ��������

void platSleep(int iSeconds);

void platMSleep(int iMSecons);  //mS

/*-------------------------------------------------------------------
 Function: getExePath(processDir, name, len)
 Purpose: get current process path
 Parameters: processDir -- [OUT], dir of current process
             processName -- [OUT], current process name
             len -- [IN], size of path
 return: 0 --  success
         -1 -- failed
-------------------------------------------------------------------*/
int getExePath(char* processDir, char* processName, int len);

/*-------------------------------------------------------------------
 Function: initSocket(void)
 Purpose: ��ʼ��socket,windowsƽ̨�£�ʹ��socketǰ�����
 Parameters:
 return: 0 --  �ɹ�
         -1 -- ʧ��
-------------------------------------------------------------------*/
int initSocket(void);

/*-------------------------------------------------------------------
 Function: deinitSocket(void)
 Purpose: ����ʹ��socketʱ��������
 Parameters:
 return:
-------------------------------------------------------------------*/
void deinitSocket(void);

/*-------------------------------------------------------------------
 Function: sendUdpData(peerIPAddr, port, p_data, datalen)
 Purpose: send data to peer ip by udp mode
 Parameters: peerIPAddr -- [IN], ip addr to send
             port -- [IN], port 
             p_data -- [IN], data to send
             dataLen -- [IN], data length
 return: 0 -- success
         -1 -- failed
-------------------------------------------------------------------*/
int sendUdpData(const char* peerIPAddr, int port, 
                const char* p_data, int dataLen);

/*-------------------------------------------------------------------
 Function: broadCastUdpData(port, p_data, datalen)
 Purpose: broadcast udp data
 Parameters: port -- [IN], port 
             p_data -- [IN], data to send
             dataLen -- [IN], data length
 return: 0 -- success
         -1 -- failed
-------------------------------------------------------------------*/
int broadCastUdpData(int port, const char* p_data, int dataLen);

/*-------------------------------------------------------------------
 Function: sendTcpData(peerIPAddr, port, p_data, datalen)
 Purpose: send data to peer ip by tcp mode
 Parameters: peerIPAddr -- [IN], ip addr to send
             port -- [IN], port 
             p_data -- [IN], data to send
             dataLen -- [IN], data length
 return: 0 -- success
         -1 -- failed
-------------------------------------------------------------------*/
int sendTcpData(const char* peerIPAddr, int port, 
                const char* p_data, int dataLen);

/*-------------------------------------------------------------------
 Function: getLocalIp(szIp)
 Purpose: get eth0 ip address
 Parameters: szIp -- [OUT], ip address
 return: 0 --  success
         -1 -- failed
-------------------------------------------------------------------*/
int getLocalIp(char* szIp);

/*-------------------------------------------------------------------
 Function: initTcpServer(int* p_sfd)
 Purpose: ��ʼ����ʼtcp����
 Parameters: szIpAddr -- [IN], ip
             iPort -- [IN], port
             p_sfd -- [OUT], ���ص�socket
 return: 0 --  �ɹ�
         -1 -- ʧ��
-------------------------------------------------------------------*/
int initTcpServer(const char* szIpAddr, int iPort, int* p_sfd);

/*-------------------------------------------------------------------
 Function: checkStrIsInteger(szSrc)
 Purpose: ����ַ����Ƿ�ȫ������
 Parameters: szSrc -- [IN], �������ַ���
 return: 0 --  ����
         1 -- ��
-------------------------------------------------------------------*/
int checkStrIsInteger(const char* szSrc);

/*-------------------------------------------------------------------
 Function: calcByteSum(szIn, iInLen)
 Purpose: calculate sum of bytes
 Parameters: szIn -- [IN], data bytes
             iInLen -- [IN], length of bytes to calculate
 return: sum result
-------------------------------------------------------------------*/
unsigned short calcByteSum(const char* szIn, int iInLen);

/*-------------------------------------------------------------------
 Function: getFileSize(p_filename)
 Purpose: get file size
 Parameters: p_filename -- [IN], file name
 return: -1 -- file not exist
         >=0 -- file size
-------------------------------------------------------------------*/
int getFileSize(const char* p_filename);

/*-------------------------------------------------------------------
 Function: easyCreateThread(threadId, start_routine, arg)
 Purpose: create a thread
 Parameters: start_routine -- [IN], thread function
             arg -- [IN], argument delivered to thread function
 return: 0 --  success
         -1 -- failed
-------------------------------------------------------------------*/
int easyCreateThread(void* (* start_routine)(void*), void* arg);


//difine a mutex class for both linux and windows
class EasyMutex
{
private:

#ifdef _WIN32
    HANDLE m_hMutex;
#else
    pthread_mutex_t m_lock;
#endif

public:
    //init lock, 0 --  success , other -- failed
    int init(void);

    //lock, 0 --  success , other -- failed
    int lock(void);

    //unlock, 0 --  success , other -- failed
    int unlock(void);

    //destroy lock
    void destroy(void);
};


/////////////////////////////////////////////////////////////////////
//tcp client

class CTcpCltAppInterface 
{
public:
    //while the client is notified to read, this fun should be called.
    //in this fun, user should read the socket data
    virtual int readHandle(void) = 0;
};

typedef struct tagTcpCltAppParas {
    char szAddr[16];
    int  iPort;
    CTcpCltAppInterface* p_app;
} TCPCLTAPPPARAS, *PTCPCLTAPPPARAS;


class CEasyTcpClt
{
private:
    int m_sfd;
    int m_bIsClosed;
    CTcpCltAppInterface* m_pApp;
    EasyMutex m_hLock;

private:
    //here to call the callback function of m_pApp
    int readHandle(void);

    void setClosedState(int iState);
    int getClosedState(void);

    //read thread
    static void* tcpReadThreadFun(void* arg);

public:
    CEasyTcpClt(void);
    ~CEasyTcpClt(void);

    int open(void);
    int init(void* pParas);
    int write(const char* pBuf, int len);
    int read(char* pBuf, int len);
    void clear(void);

    //1 -- closed, 0 -- connect
    int isClosed(void);
};

class EasyMath
{
public:
    static void shortToBytes(short val, char* p_bytes);
    static void intToBytes(int val, char* p_bytes);
    static void longToBytes(long val, char* p_bytes);
};

#endif  //__PLATCOMM_H__