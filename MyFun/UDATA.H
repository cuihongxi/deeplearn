/******************************************************************
*文件名:公共参数
	2019年6月3日08:06:44
*文件说明:定义公共参数，宏定义，类型
*/

#ifndef  __UDATA_H  
#define  __UDATA_H 

typedef unsigned char           MSTYPE;

typedef	 unsigned char 	u8;
typedef	 unsigned short u16;
typedef	 unsigned int 	u32;

typedef unsigned short	WCHAR;
typedef unsigned int	  UINT;
typedef unsigned char   BYTE;


typedef enum {ISOK = 0, ISERROR = 1} Flag_Status;


#define GUI_COUNTOF(a)          (sizeof(a) / sizeof(a[0]))
#define ExchangeDat(a,b)      a^=b;b^=a;a^=b    // 交换两个数的值







#endif

