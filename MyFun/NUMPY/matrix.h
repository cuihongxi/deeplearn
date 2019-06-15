/**
		2019��6��3��07:57:33
		�������

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


#define		FLOAT 1								//��������ת������
#if FLOAT >0
typedef	 float  matDAT;					//������󱣴����������
#define		MAT_PRINT			MAT_LOG("%f,	",*((matDAT*)((u8*)mat+sizeof(matrixStr)) + rows*mat->columns + columns))		
#else 
typedef	 u8  matDAT;					//������󱣴����������
#define		MAT_PRINT			MAT_LOG("%d	",*((matDAT*)((u8*)mat+sizeof(matrixStr)) + L*mat->columns + H))	
	
#endif

typedef struct
{
	u32 rows;	//����
	u32 columns;	//����
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

/**
	����
*/


matrixStr* matMalloc(u32 rows,u32 columns);												// ����һ������
void matApendDat(matrixStr* mat , matDAT* dat); 									// �������

void matApendDatU8(matrixStr* mat , u8* dat);											// ���u8��������
void PrintMat(matrixStr* mat);																		// ��ӡһ������
matDAT Get_Mat(matrixStr* mat,u32 rows,u32 columns);							// ��ȡһ�������Ԫ��
matDAT* Get_MatAddr(matrixStr* mat,u32 rows,u32 columns);					// ��ȡ����Ԫ�ص�Ԫ�ĵ�ַ
matrixStr* matAdd(matrixStr* a,matrixStr* b);											// �������
matrixStr* matDot(matrixStr* a,matrixStr* b);											// �������,����һ���˻��������
matrixStr* matrix_T(matrixStr* mat);															// ���ؾ����ת��,ע�⣬���������Ҫ��Ҫ�ͷ��ڴ�
matrixStr* matrix_Num(u32 rows,u32 columns,matDAT num);						// ����һ�����󣬲�ȫ����ֵ��num
matrixStr* matrix_One(u32 rows,u32 columns);											// ����һ�����󣬲�ȫ����ֵ��1
matrixStr* matrix_Zero(u32 rows,u32 columns);											// ����һ�����󣬲�ȫ����ֵ��0
matrixStr* matrix_Append(matrixStr* source,matrixStr* bmat,Axis axis);   // ��mat����,��ӵ�source�����У�axis = 1��ӵ��ұߣ�axis = 0 ��ӵ��±�
matrixStr* matrix_CutOut(matrixStr* source,Axis axis,u32 start,u32 end); // ��ȡһ�ξ���
u32 GetMatLength(matrixStr* mat);																	// ��ȡ�����С
matrixStr* matSub(matrixStr* a,matrixStr* b);											// �������
void matAlgorithm(matrixStr* mat,matDAT num,Algorithm alg);				// ������num������
void matIteraAlgorithm(matrixStr* a,matrixStr* b,Algorithm alg);	// �����������������㣬�������¿ռ䣬������ǵ�һ������

matrixStr* matRote(matrixStr* mat_sorce,float radian);							// ������ת,radian���ȣ�˳ʱ��Ϊ��
matrixStr* matZoom(matrixStr* mat_sorce,float xtimes,float ytimes);	// ��������,xtimes��ytimes
matrixStr* matSigmoid(matrixStr* feature,matrixStr* weight);				// ����sigmoid����
matrixStr* matSoftmax(matrixStr* feature,matrixStr* weight);				// softmax����
matrixStr* matLabelFilter(matrixStr* label);							// label������
void matShape(matrixStr* mat);//��ȡ�������״

matrixStr* matDot_T(matrixStr* a,matrixStr* b);//����a��ת�õ���ʽ���г˷�����
u8 GetListMax(matrixStr* mat,u8 row);//�����ݵ��н������򣬷�������
#endif

