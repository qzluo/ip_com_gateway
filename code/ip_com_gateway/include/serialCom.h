/********************************************************************
 File: serialCom.h
 Function: serial communication function
 Author: Luobihe
 Date: 2016-1-6
*********************************************************************/

#ifndef __SERIALCOM_H__
#define __SERIALCOM_H__

//���ô���ͨ������
int set_speed(int fd, int speed);

//���ô�������λ��ֹͣλ��Ч��λ
int set_Parity(int fd, int databits, int stopbits, int parity);

#endif  //__SERIALCOM_H__