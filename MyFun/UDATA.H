/******************************************************************
*�ļ���:��������
	2019��6��3��08:06:44
*�ļ�˵��:���幫���������궨�壬����
*/

#ifndef  __UDATA_H  
#define  __UDATA_H 

#define GUI_COUNTOF(a)          (sizeof(a) / sizeof(a[0]))
#define ExchangeDat(a,b)      a^=b;b^=a;a^=b    // ������������ֵ

typedef unsigned char           MSTYPE;

typedef	 unsigned char u8;
typedef	 unsigned  int u32;

typedef unsigned short	WCHAR;
typedef unsigned int	  UINT;
typedef unsigned char   BYTE;


typedef enum {ISOK = 0, ISERROR = 1} Flag_Status;



#endif
