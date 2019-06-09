/**
2019年6月3日08:25:59
仿Python中numpy对矩阵的操作

*/

#ifndef		__NUMPY_H
#define		__NUMPY_H

#include "matrix.h"


typedef struct
{
	matrixStr* (*array)(u32 line,u32 list);							// 申请一个矩阵，注：不用需要释放内存
	void (*apendData)(matrixStr* mat , matDAT* dat);		// 给矩阵添加数据	
	void (*printMat)(matrixStr* );											// 打印函数
	matrixStr* (*T)(matrixStr* );												// 转置，注：不用需要释放内存
	matrixStr* (*ones)(u32 line,u32 list);							// 生成一个矩阵，并全部赋值成1
	matrixStr* (*zeros)(u32 line,u32 list);							// 生成一个矩阵，并全部赋值成0
	matrixStr* (*dot)(matrixStr* a,matrixStr* b);				// 矩阵乘法
	matrixStr* (*append)(matrixStr* source,matrixStr* bmat,Axis axis); 		// 将mat矩阵,添加到source矩阵中，axis = 1添加到右边，axis = 0 添加到下边
	matrixStr* (*cutOut)(matrixStr* source,Axis axis,u32 start,u32 end); 	// 截取一段矩阵
	u32 (*len)(matrixStr* mat);													// 获取矩阵的长度
	matrixStr* (*sub)(matrixStr* a,matrixStr* b);				// 矩阵减法
	void (*alg)(matrixStr* mat,float num,Algorithm alg);// 矩阵与num的运算
	void (*iteraAlg)(matrixStr* a,matrixStr* b,Algorithm alg);// 矩阵与矩阵迭代的运算，不产生新空间，结果覆盖第一个矩阵
	matrixStr* (*sigmoid)(matrixStr* feature,matrixStr* weight);		//矩阵sigmoid函数
}numpy;	//仿Python的numpy


void numpy_Init(numpy* np); //初始化numpy对象

#endif
