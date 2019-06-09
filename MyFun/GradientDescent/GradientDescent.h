/**
2019年6月9日13:11:24
梯度下降算法，及相关函数

*/
#ifndef	__GradientDescent_H
#define	__GradientDescent_H

#include "udata.h"
#include "matrix.h"
#include "numpy.h"


/**
函数
*/


matrixStr* GradientDescent(numpy* np,matrixStr* featureMatrix,matrixStr* weight,matrixStr* label);//梯度下降算法
matrixStr* Train(numpy* np,matrixStr* feature,matrixStr* label,float learnRate,u32 times);	//训练,返回m,b的矩阵weight

#endif
