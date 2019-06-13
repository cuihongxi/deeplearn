/**
		2019年6月3日07:57:33
		矩阵操作

*/


#ifndef	__MATRIX_2_H
#define	__MATRIX_2_H

#include "udata.h"
#include "cui_malloc.h"
#include "stdio.h"


#define	MAT_LOG								printf
#define	ERROR_MAT_LOG					printf

#define	malloc					CUI_MALLOC
#define	_free						FreeCUI_MALLOC


#define		pi	3.1415926

#define		MAT_DAT_POINTER		((u8*)mat+sizeof(matrixStr))

#define		_MAT_DAT_POINTER(a)		((u8*)(a)+sizeof(matrixStr))
	
#define	MAT_INT		int
#define	MAT_FLOAT	float
	
//为了减少计算量，只定义这3钟类型
typedef enum{
	_UCHAR,
	_INT,
	_FLOAT,
	
}typeEnum;

typedef struct
{
	u32 rows;			//行数
	u32 columns;	//列数
	typeEnum type;
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

typedef enum{
	ADD,
	SUB,
}AlgMat;	//矩阵加减运算法则

//定义矩阵乘法的各种类型函数模型
#define	_GetMat_MultAdd(returnType,type_a,type_b)	\
returnType GetMat_MultAdd_##type_a##_##type_b(matrixStr* a,matrixStr* b,u32 aline,u32 blist)\
{\
	returnType dat = 0;\
	for(u32 i=0;i<a->columns;i++)\
	{\
		dat += *((type_a*)Get_MatAddr(a,aline,i)) *  (*(type_b*)Get_MatAddr(b,i,blist));\
	}\
	return dat;\
}

//矩阵乘法宏
#define	_TraversalDot(mat,a,b)	do{\
if(mat##->type == _FLOAT)\
{\
	if(a##->type == _FLOAT)\
	{\
		if(b##->type == _FLOAT)	*((MAT_FLOAT*)MAT_DAT_POINTER +  rows*mat##->columns + columns) = GetMat_MultAdd_##float##_##float(a,b,rows,columns);\
		else if(b##->type == _INT)	*((MAT_FLOAT*)MAT_DAT_POINTER +  rows*mat##->columns + columns) = GetMat_MultAdd_##float##_##int(a,b,rows,columns);\
		else 	*((MAT_FLOAT*)MAT_DAT_POINTER +  rows*mat##->columns + columns) = GetMat_MultAdd_##float##_##u8(a,b,rows,columns);\
	}else\
	if(a##->type == _INT)\
	{\
		*((MAT_FLOAT*)MAT_DAT_POINTER +  rows*mat##->columns + columns) = GetMat_MultAdd_##int##_##float(a,b,rows,columns);\
	}else *((MAT_FLOAT*)MAT_DAT_POINTER +  rows*mat##->columns + columns) = GetMat_MultAdd_##u8##_##float(a,b,rows,columns);\
	}else\
{\
	if(a##->type == _INT)\
	{\
		if(b##->type == _INT) *((MAT_INT*)MAT_DAT_POINTER +  rows*mat##->columns + columns) = GetMat_MultAdd_##int##_##int(a,b,rows,columns);\
			else *((MAT_INT*)MAT_DAT_POINTER +  rows*mat##->columns + columns) = GetMat_MultAdd_##int##_##u8(a,b,rows,columns);\
	}else *((MAT_INT*)MAT_DAT_POINTER +  rows*mat##->columns + columns) = GetMat_MultAdd_##u8##_##int(a,b,rows,columns);\
}\
}while(0)

//矩阵运算宏
#define	_Traversal(tomat,a,b,Algorithm)	do{\
if(tomat##->type == _FLOAT)\
{\
	if(a##->type == _FLOAT)\
	{\
		if(b##->type == _FLOAT)	*((MAT_FLOAT*)_MAT_DAT_POINTER(tomat) +  rows * tomat##->columns + columns) = *(MAT_FLOAT*)Get_MatAddr(a,rows,columns) ##Algorithm## *(MAT_FLOAT*)Get_MatAddr(b,rows,columns);\
		else if(b##->type == _INT)	*((MAT_FLOAT*)_MAT_DAT_POINTER(tomat) +  rows * tomat##->columns + columns) = *(MAT_FLOAT*)Get_MatAddr(a,rows,columns) ##Algorithm## *(MAT_INT*)Get_MatAddr(b,rows,columns);\
		else 	*((MAT_FLOAT*)_MAT_DAT_POINTER(tomat) +  rows*tomat##->columns + columns) = *(MAT_FLOAT*)Get_MatAddr(a,rows,columns) ##Algorithm## *(u8*)Get_MatAddr(b,rows,columns);\
	}else\
	if(a##->type == _INT)\
	{\
		*((MAT_FLOAT*)_MAT_DAT_POINTER(tomat) +  rows*tomat##->columns + columns) = *(MAT_INT*)Get_MatAddr(a,rows,columns) ##Algorithm## *(MAT_FLOAT*)Get_MatAddr(b,rows,columns);\
	}else *((MAT_FLOAT*)_MAT_DAT_POINTER(tomat) +  rows*tomat##->columns + columns) = *(u8*)Get_MatAddr(a,rows,columns) ##Algorithm## *(MAT_FLOAT*)Get_MatAddr(b,rows,columns);\
}else\
{\
	if(a##->type == _INT)\
	{\
		if(b##->type == _INT) *((MAT_INT*)_MAT_DAT_POINTER(tomat) +  rows * tomat##->columns + columns) = *(MAT_INT*)Get_MatAddr(a,rows,columns) ##Algorithm## *(MAT_INT*)Get_MatAddr(b,rows,columns);\
			else *((MAT_INT*)_MAT_DAT_POINTER(tomat) +  rows * tomat##->columns + columns) = *(MAT_INT*)Get_MatAddr(a,rows,columns) ##Algorithm## *(u8*)Get_MatAddr(b,rows,columns);\
	}else *((MAT_INT*)_MAT_DAT_POINTER(tomat) +  rows * tomat##->columns + columns) = *(u8*)Get_MatAddr(a,rows,columns) ##Algorithm## *(MAT_INT*)Get_MatAddr(b,rows,columns);\
}\
}while(0)

//遍历类型
#define	_Switch(todat,sorceMat,sorcedat)	do{\
	switch((u8)sorceMat##->type)\
	{\
		case _UCHAR:	todat = *(u8*)(sorcedat);\
			break;\
		case _INT:		todat = *(int*)(sorcedat);\
			break;\
		case _FLOAT:	todat = *(float*)(sorcedat);\
			break;\
	}\
}while(0)

//矩阵赋值
#define	_Give_MATDAT(toMat,to_a0,to_a1,sorceMat,sorce_a0,sorce_a1)	do{\
switch((u8)toMat##->type)\
{\
	case _UCHAR: 	_Switch(*(u8*)Get_MatAddr(toMat,to_a0,to_a1),sorceMat,Get_MatAddr(sorceMat,sorce_a0,sorce_a1));\
		break;\
	case _INT: 		_Switch(*(int*)Get_MatAddr(toMat,to_a0,to_a1),sorceMat,Get_MatAddr(sorceMat,sorce_a0,sorce_a1));\
	break;\
	case _FLOAT:	_Switch(*(float*)Get_MatAddr(toMat,to_a0,to_a1),sorceMat,Get_MatAddr(sorceMat,sorce_a0,sorce_a1));\
		break;\
}\
}while(0)
/**
	函数
*/


matrixStr* matMalloc(u32 rows,u32 columns,typeEnum type);												// 申请一个矩阵
void matApendDat(matrixStr* mat , void* dat); 								// 添加数据

//void matApendDatU8(matrixStr* mat , u8* dat);									//添加u8类型数据
void PrintMat(matrixStr* mat);																	// 打印一个矩阵
u32 Get_MatAddr(matrixStr* mat,u32 rows,u32 columns);						// 获取矩阵元素单元的地址
matrixStr* matAddSub(matrixStr* a,matrixStr* b,AlgMat arg);			// 矩阵相加
matrixStr* matDot(matrixStr* a,matrixStr* b);										// 矩阵相乘,返回一个乘积结果矩阵
matrixStr* matrix_T(matrixStr* mat);														// 返回矩阵的转置,注意，如果不再需要需要释放内存
matrixStr* matrix_Num(u32 rows,u32 columns,u8 num);							// 生成一个矩阵，并全部赋值成num
matrixStr* matrix_One(u32 rows,u32 columns);											// 生成一个矩阵，并全部赋值成1
matrixStr* matrix_Zero(u32 rows,u32 columns);											// 生成一个矩阵，并全部赋值成0
matrixStr* matrix_Append(matrixStr* source,matrixStr* bmat,Axis axis);   // 将mat矩阵,添加到source矩阵中，axis = 1添加到右边，axis = 0 添加到下边
matrixStr* matrix_CutOut(matrixStr* source,Axis axis,u32 start,u32 end); // 截取一段矩阵
u32 GetMatLength(matrixStr* mat);																	// 获取矩阵大小
void matAlgorithm(matrixStr* mat,float num,Algorithm alg);			// 矩阵与num的运算
void matIteraAlgorithm(matrixStr* tomat,matrixStr* b,AlgMat arg);// 矩阵与矩阵迭代的运算，不产生新空间，结果覆盖第一个矩阵

matrixStr* matRote(matrixStr* mat_sorce,float radian);					// 矩阵旋转,radian弧度，顺时针为正
matrixStr* matZoom(matrixStr* mat_sorce,float xtimes,float ytimes);// 矩阵缩放,xtimes，ytimes
matrixStr* matSigmoid(matrixStr* feature,matrixStr* weight);		//矩阵sigmoid函数
matrixStr* matSoftmax(matrixStr* feature,matrixStr* weight);		//softmax运算


#endif

