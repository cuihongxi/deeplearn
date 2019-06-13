/**
		2019��6��3��07:57:33
		�������

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
	
//Ϊ�˼��ټ�������ֻ������3������
typedef enum{
	_UCHAR,
	_INT,
	_FLOAT,
	
}typeEnum;

typedef struct
{
	u32 rows;			//����
	u32 columns;	//����
	typeEnum type;
}matrixStr;						

typedef enum{
	horizontal,	//����
	vertical,		//����
}Axis;

typedef enum{
	add,
	sub,
	mul,
	divi,
}Algorithm;	//���㷨��

typedef enum{
	ADD,
	SUB,
}AlgMat;	//����Ӽ����㷨��

//�������˷��ĸ������ͺ���ģ��
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

//����˷���
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

//���������
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

//��������
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

//����ֵ
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
	����
*/


matrixStr* matMalloc(u32 rows,u32 columns,typeEnum type);												// ����һ������
void matApendDat(matrixStr* mat , void* dat); 								// �������

//void matApendDatU8(matrixStr* mat , u8* dat);									//���u8��������
void PrintMat(matrixStr* mat);																	// ��ӡһ������
u32 Get_MatAddr(matrixStr* mat,u32 rows,u32 columns);						// ��ȡ����Ԫ�ص�Ԫ�ĵ�ַ
matrixStr* matAddSub(matrixStr* a,matrixStr* b,AlgMat arg);			// �������
matrixStr* matDot(matrixStr* a,matrixStr* b);										// �������,����һ���˻��������
matrixStr* matrix_T(matrixStr* mat);														// ���ؾ����ת��,ע�⣬���������Ҫ��Ҫ�ͷ��ڴ�
matrixStr* matrix_Num(u32 rows,u32 columns,u8 num);							// ����һ�����󣬲�ȫ����ֵ��num
matrixStr* matrix_One(u32 rows,u32 columns);											// ����һ�����󣬲�ȫ����ֵ��1
matrixStr* matrix_Zero(u32 rows,u32 columns);											// ����һ�����󣬲�ȫ����ֵ��0
matrixStr* matrix_Append(matrixStr* source,matrixStr* bmat,Axis axis);   // ��mat����,��ӵ�source�����У�axis = 1��ӵ��ұߣ�axis = 0 ��ӵ��±�
matrixStr* matrix_CutOut(matrixStr* source,Axis axis,u32 start,u32 end); // ��ȡһ�ξ���
u32 GetMatLength(matrixStr* mat);																	// ��ȡ�����С
void matAlgorithm(matrixStr* mat,float num,Algorithm alg);			// ������num������
void matIteraAlgorithm(matrixStr* tomat,matrixStr* b,AlgMat arg);// �����������������㣬�������¿ռ䣬������ǵ�һ������

matrixStr* matRote(matrixStr* mat_sorce,float radian);					// ������ת,radian���ȣ�˳ʱ��Ϊ��
matrixStr* matZoom(matrixStr* mat_sorce,float xtimes,float ytimes);// ��������,xtimes��ytimes
matrixStr* matSigmoid(matrixStr* feature,matrixStr* weight);		//����sigmoid����
matrixStr* matSoftmax(matrixStr* feature,matrixStr* weight);		//softmax����


#endif

