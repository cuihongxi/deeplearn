/**
2019��6��3��08:25:59
��Python��numpy�Ծ���Ĳ���

*/

#ifndef		__NUMPY_H
#define		__NUMPY_H

#include "matrix.h"


typedef struct
{
	matrixStr* (*array)(u32 line,u32 list);							// ����һ������ע��������Ҫ�ͷ��ڴ�
	void (*apendData)(matrixStr* mat , matDAT* dat);		// �������������	
	void (*printMat)(matrixStr* );											// ��ӡ����
	matrixStr* (*T)(matrixStr* );												// ת�ã�ע��������Ҫ�ͷ��ڴ�
	matrixStr* (*ones)(u32 line,u32 list);							// ����һ�����󣬲�ȫ����ֵ��1
	matrixStr* (*zeros)(u32 line,u32 list);							// ����һ�����󣬲�ȫ����ֵ��0
	matrixStr* (*dot)(matrixStr* a,matrixStr* b);				// ����˷�
	matrixStr* (*append)(matrixStr* source,matrixStr* bmat,Axis axis); 		// ��mat����,��ӵ�source�����У�axis = 1��ӵ��ұߣ�axis = 0 ��ӵ��±�
	matrixStr* (*cutOut)(matrixStr* source,Axis axis,u32 start,u32 end); 	// ��ȡһ�ξ���
	u32 (*len)(matrixStr* mat);													// ��ȡ����ĳ���
	matrixStr* (*sub)(matrixStr* a,matrixStr* b);				// �������
	void (*alg)(matrixStr* mat,float num,Algorithm alg);// ������num������
	void (*iteraAlg)(matrixStr* a,matrixStr* b,Algorithm alg);// �����������������㣬�������¿ռ䣬������ǵ�һ������
	matrixStr* (*sigmoid)(matrixStr* feature,matrixStr* weight);		//����sigmoid����
}numpy;	//��Python��numpy


void numpy_Init(numpy* np); //��ʼ��numpy����

#endif
