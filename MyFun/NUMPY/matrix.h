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

#define		MAT_PRINT			MAT_LOG("%f	",*((matDAT*)((u8*)mat+sizeof(matrixStr)) + L*mat->list + H))	
#define		pi	3.1415926

typedef	 float  matDAT;					//������󱣴����������

typedef struct
{
	u32 line;	//����
	u32 list;	//����
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


matrixStr* matMalloc(u32 line,u32 list);												// ����һ������
void matApendDat(matrixStr* mat , matDAT* dat); 								// �������
void PrintMat(matrixStr* mat);																	// ��ӡһ������
matDAT Get_Mat(matrixStr* mat,u32 line,u32 list);								// ��ȡһ�������Ԫ��
matDAT* Get_MatAddr(matrixStr* mat,u32 line,u32 list);					// ��ȡ����Ԫ�ص�Ԫ�ĵ�ַ
matrixStr* matAdd(matrixStr* a,matrixStr* b);										// �������
matrixStr* matDot(matrixStr* a,matrixStr* b);										// �������,����һ���˻��������
matrixStr* matrix_T(matrixStr* mat);														// ���ؾ����ת��,ע�⣬���������Ҫ��Ҫ�ͷ��ڴ�
matrixStr* matrix_Num(u32 line,u32 list,matDAT num);						// ����һ�����󣬲�ȫ����ֵ��num
matrixStr* matrix_One(u32 line,u32 list);												// ����һ�����󣬲�ȫ����ֵ��1
matrixStr* matrix_Zero(u32 line,u32 list);											// ����һ�����󣬲�ȫ����ֵ��0
matrixStr* matrix_Append(matrixStr* source,matrixStr* bmat,Axis axis);   // ��mat����,��ӵ�source�����У�axis = 1��ӵ��ұߣ�axis = 0 ��ӵ��±�
matrixStr* matrix_CutOut(matrixStr* source,Axis axis,u32 start,u32 end); // ��ȡһ�ξ���
u32 GetMatLength(matrixStr* mat);																// ��ȡ�����С
matrixStr* matSub(matrixStr* a,matrixStr* b);										// �������
void matAlgorithm(matrixStr* mat,float num,Algorithm alg);			// ������num������
void matIteraAlgorithm(matrixStr* a,matrixStr* b,Algorithm alg);// �����������������㣬�������¿ռ䣬������ǵ�һ������

matrixStr* matRote(matrixStr* mat_sorce,float radian);					// ������ת,radian���ȣ�˳ʱ��Ϊ��
matrixStr* matZoom(matrixStr* mat_sorce,float xtimes,float ytimes);// ��������,xtimes��ytimes


#endif

