/**
2019��6��9��13:11:24
�ݶ��½��㷨������غ���

*/
#ifndef	__GradientDescent_H
#define	__GradientDescent_H

#include "udata.h"
#include "matrix.h"
#include "numpy.h"


/**
����
*/


matrixStr* GradientDescent(numpy* np,matrixStr* featureMatrix,matrixStr* weight,matrixStr* label);//�ݶ��½��㷨
matrixStr* LogicGradientDescent(numpy* np,matrixStr* featureMatrix,matrixStr* weight,matrixStr* label);//�߼��ع��ݶ��½��㷨

matrixStr* Train(matrixStr* (*gradientDescent)(numpy*,matrixStr*,matrixStr*,matrixStr*),\
numpy* np,matrixStr* feature,matrixStr* label,float learnRate,u32 times);			//ѵ��

matrixStr* Test(matrixStr*(*math)(matrixStr*,matrixStr*),matrixStr*feature,matrixStr* weight);//����

#endif
