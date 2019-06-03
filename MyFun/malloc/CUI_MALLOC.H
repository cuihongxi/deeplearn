/******************************************************************
*�ļ���:����ͷ�ļ�
*������:̽���Ƽ���www.explorersoftware.taobao.com
*����ʱ��:2017��8��9��14:07:03
*�ļ�˵��:��̬�����ڴ�
*2019��5��7��17:16:22
*	����С�ֽڵĶ�̬�ڴ����
���䷽���ǣ�����һ����СΪ��С���ֽڵ�Ԫ��ΪС�ֽڳأ�
						����8���ֽ���Ϊ���⹦���룬ǰ���ֽڼ�¼��һ��С�ֽڷ���ص�ָ�룬û����Ϊ0x00000000
						���ĸ��ֽ���Ϊ������������֮ǰ������������з��䡣
*/


#ifndef     __CUI_MALLOC_H
#define     __CUI_MALLOC_H


#include "UDATA.H"

#define     DEBUG_Malloc_LEVEL  0  // ���Կ���

#define			Malloc_MINI				4												// С�ֽڷ������С��Ԫ
#define			Malloc_MINIINDEX		31										// �����������ֽ�λ����һ��7,15,32
#define     Malloc_UNIT       (Malloc_MINI*Malloc_MINIINDEX+8)        // ���ֽڷ������С��Ԫ
#define     Malloc_MAXSIZE    150*8*Malloc_UNIT       // ��������ڴ�ռ䣬������Malloc_UNIT*8��������


#if   DEBUG_Malloc_LEVEL >0
#include<stdio.h>
#endif

#if (DEBUG_Malloc_LEVEL > 0)
#define  Malloc_Log(...)         printf(__VA_ARGS__);
#else
#define Malloc_Log(...)   
#endif                             


// С�ֽ��ڴ�����ݽṹ
typedef struct{
u8 dat[Malloc_MINI*Malloc_MINIINDEX];		// ������
u8* pNext;									// ָ����һ��С�ֽڳص�ַ
u32 index;									// ������						
}MiniMallocStr;

void* CUI_MALLOC(u32  leng_th);                   // �����ڴ�
Flag_Status  FreeCUI_MALLOC(void* Malloc);        // �ͷ��ڴ�
// u32 GetNumMalloc(u8* Malloc);                   // ��ȡ��malloc������
#endif