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
matrixStr* Train(numpy* np,matrixStr* feature,matrixStr* label,float learnRate,u32 times);	//ѵ��,����m,b�ľ���weight

#endif
