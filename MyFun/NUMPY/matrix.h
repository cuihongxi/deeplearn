/**
		2019年6月3日07:57:33
		矩阵操作

*/


#ifndef	__MATRIX_H
#define	__MATRIX_H

#include "udata.h"
#include "cui_malloc.h"
#include "stdio.h"


#define	MAT_LOG								printf
#define	ERROR_MAT_LOG					printf

#define	malloc					CUI_MALLOC
#define	_free						FreeCUI_MALLOC


#define		pi	3.1415926


#define		FLOAT 1								//数据类型转换开关
#if FLOAT >0
typedef	 float  matDAT;					//定义矩阵保存的数据类型
#define		MAT_PRINT			MAT_LOG("%f,	",*((matDAT*)((u8*)mat+sizeof(matrixStr)) + rows*mat->columns + columns))		
#else 
typedef	 u8  matDAT;					//定义矩阵保存的数据类型
#define		MAT_PRINT			MAT_LOG("%d	",*((matDAT*)((u8*)mat+sizeof(matrixStr)) + L*mat->columns + H))	
	
#endif

typedef struct
{
	u32 rows;	//行数
	u32 columns;	//列数
}matrixStr;						

typedef enum{
	horizontal,	//横轴
	vertical,		//纵轴
}Axis;

typedef enum{
	add,
	sub,
	mul,
	divi,
}Algorithm;	//运算法则

/**
	函数
*/


matrixStr* matMalloc(u32 rows,u32 columns);												// 申请一个矩阵
void matApendDat(matrixStr* mat , matDAT* dat); 									// 添加数据

void matApendDatU8(matrixStr* mat , u8* dat);											// 添加u8类型数据
void PrintMat(matrixStr* mat);																		// 打印一个矩阵
matDAT Get_Mat(matrixStr* mat,u32 rows,u32 columns);							// 获取一个矩阵的元素
matDAT* Get_MatAddr(matrixStr* mat,u32 rows,u32 columns);					// 获取矩阵元素单元的地址
matrixStr* matAdd(matrixStr* a,matrixStr* b);											// 矩阵相加
matrixStr* matDot(matrixStr* a,matrixStr* b);											// 矩阵相乘,返回一个乘积结果矩阵
matrixStr* matrix_T(matrixStr* mat);															// 返回矩阵的转置,注意，如果不再需要需要释放内存
matrixStr* matrix_Num(u32 rows,u32 columns,matDAT num);						// 生成一个矩阵，并全部赋值成num
matrixStr* matrix_One(u32 rows,u32 columns);											// 生成一个矩阵，并全部赋值成1
matrixStr* matrix_Zero(u32 rows,u32 columns);											// 生成一个矩阵，并全部赋值成0
matrixStr* matrix_Append(matrixStr* source,matrixStr* bmat,Axis axis);   // 将mat矩阵,添加到source矩阵中，axis = 1添加到右边，axis = 0 添加到下边
matrixStr* matrix_CutOut(matrixStr* source,Axis axis,u32 start,u32 end); // 截取一段矩阵
u32 GetMatLength(matrixStr* mat);																	// 获取矩阵大小
matrixStr* matSub(matrixStr* a,matrixStr* b);											// 矩阵减法
void matAlgorithm(matrixStr* mat,matDAT num,Algorithm alg);				// 矩阵与num的运算
void matIteraAlgorithm(matrixStr* a,matrixStr* b,Algorithm alg);	// 矩阵与矩阵迭代的运算，不产生新空间，结果覆盖第一个矩阵

matrixStr* matRote(matrixStr* mat_sorce,float radian);							// 矩阵旋转,radian弧度，顺时针为正
matrixStr* matZoom(matrixStr* mat_sorce,float xtimes,float ytimes);	// 矩阵缩放,xtimes，ytimes
matrixStr* matSigmoid(matrixStr* feature,matrixStr* weight);				// 矩阵sigmoid函数
matrixStr* matSoftmax(matrixStr* feature,matrixStr* weight);				// softmax运算
matrixStr* matLabelFilter(matrixStr* label);							// label过滤器
void matShape(matrixStr* mat);//获取矩阵的形状

matrixStr* matDot_T(matrixStr* a,matrixStr* b);//矩阵a以转置的形式进行乘法运算
u8 GetListMax(matrixStr* mat,u8 row);//对数据的行进行排序，返回列数
#endif

