/********************************************************************
 File: serialCom.cpp
 Function: serial communication function
 Author: Luobihe
 Date: 2016-1-6
*********************************************************************/

#ifndef _WIN32

#include     <stdio.h>      /*��׼�����������*/
#include     <stdlib.h>     /*��׼�����ⶨ��*/
#include     <unistd.h>     /*Unix ��׼��������*/
#include     <sys/types.h>  
#include     <sys/stat.h>   
#include     <fcntl.h>      /*�ļ����ƶ���*/
#include     <termios.h>    /*PPSIX �ն˿��ƶ���*/
#include     <errno.h>      /*����Ŷ���*/

#endif

#include "serialCom.h"

#ifndef _WIN32

static int speed_arr[] = { B230400, B115200, B57600, B38400, 
                           B19200,  B9600,   B4800,  B2400, 
                           B1800,   B1200,   B600,   B300, 
                           B200,    B150,    B134,   B110, 
                           B75,     B50,     B0,};

static int name_arr[] = { 230400, 115200, 57600, 38400, 
                          19200,  9600,   4800,  2400, 
                          1800,   1200,   600,   300, 
                          200,    150,    134,   110, 
                          75,     50,     0,};

#endif

/**
*@brief  ���ô���ͨ������
*@param  fd     ���� int  �򿪴��ڵ��ļ����
*@param  speed  ���� int  �����ٶ�
*@return  0 -- success, -1 -- failed
*/
int set_speed(int fd, int speed)
{
#ifdef _WIN32

    return 0;

#else

    int i = 0; 
    struct termios Opt = {0};

    if (tcgetattr(fd, &Opt))
        return -1;

    for (i = 0; i < sizeof(speed_arr) / sizeof(int); i++) {
        if (speed == name_arr[i]) {
            tcflush(fd, TCIOFLUSH);
            cfsetispeed(&Opt, speed_arr[i]);
            cfsetospeed(&Opt, speed_arr[i]);
            if (tcsetattr(fd, TCSANOW, &Opt)) 
                return -1;

            tcflush(fd, TCIOFLUSH);
            return 0;
        }
    }

    return -1;

#endif
}

/**
*@brief   ���ô�������λ��ֹͣλ��Ч��λ
*@param  fd     ����  int  �򿪵Ĵ����ļ����
*@param  databits ����  int ����λ   ȡֵ Ϊ 7 ����8
*@param  stopbits ����  int ֹͣλ   ȡֵΪ 1 ����2
*@param  parity  ����  int  Ч������ ȡֵΪN,E,O,,S
*@return  0 -- success, -1 -- failed
*/
int set_Parity(int fd, int databits, int stopbits, int parity)
{ 
#ifndef _WIN32

    struct termios options = {0}; 
    if  (tcgetattr(fd, &options)) 
        return -1;

    options.c_cflag &= ~CSIZE; 
    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);  /*Input*/
    options.c_oflag &= ~OPOST;   /*Output*/

    /* ��������λ*/ 
    switch (databits) {
    case 7:
        options.c_cflag |= CS7; 
        break;

    case 8:
        options.c_cflag |= CS8;
        break;   

    default:    
        return -1;  
    }

    /* ����У��λ*/ 
    switch (parity) {   
    case 'n':
    case 'N':    
        options.c_cflag &= ~PARENB;   /* Clear parity enable */
        options.c_iflag &= ~INPCK;    /* Enable parity checking */ 
        break;  

    case 'o':   
    case 'O':     
        options.c_cflag |= (PARODD | PARENB); /* ����Ϊ��Ч��*/  
        options.c_iflag |= INPCK;             /* Disnable parity checking */ 
        break;  

    case 'e':  
    case 'E':   
        options.c_cflag |= PARENB;     /* Enable parity */
        options.c_cflag &= ~PARODD;    /* ת��ΪżЧ��*/
        options.c_iflag |= INPCK;      /* Disnable parity checking */
        break;

    case 'S': 
    case 's':  /*as no parity*/   
        options.c_cflag &= ~PARENB;
        options.c_cflag &= ~CSTOPB;
        break;  

    default:   
        return -1;  
    }  

    /* ����ֹͣλ*/  
    switch (stopbits) {   
    case 1:    
        options.c_cflag &= ~CSTOPB;  
        break;  

    case 2:    
        options.c_cflag |= CSTOPB;  
        break;

    default: 
        return -1;
    } 

    /* Set input parity option */ 
    if (parity != 'n')   
        options.c_iflag |= INPCK; 

    tcflush(fd,TCIFLUSH);
    options.c_cc[VTIME] = 150; /* ���ó�ʱ15 seconds*/   
    options.c_cc[VMIN] = 0; /* define the minimum bytes data to be readed*/

    if (tcsetattr(fd,TCSANOW,&options))   
        return -1;
#endif

    return 0;  
}