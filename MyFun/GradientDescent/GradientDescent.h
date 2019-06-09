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
matrixStr* LogicGradientDescent(numpy* np,matrixStr* featureMatrix,matrixStr* weight,matrixStr* label);//逻辑回归梯度下降算法

matrixStr* Train(matrixStr* (*gradientDescent)(numpy*,matrixStr*,matrixStr*,matrixStr*),\
numpy* np,matrixStr* feature,matrixStr* label,float learnRate,u32 times);			//训练

matrixStr* Test(matrixStr*(*math)(matrixStr*,matrixStr*),matrixStr*feature,matrixStr* weight);//测试

#endif
