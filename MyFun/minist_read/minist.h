/**
	2019年6月8日15:23:17
	http://yann.lecun.com/exdb/mnist/
	读取特征训练集数据 压缩包：train-images-idx3-ubyte.gz
*/

#ifndef	__MINIST_H
#define	__MINIST_H

#include "udata.h"
#include "matrix.h"
#include "numpy.h"

#define	FILE_TRAIN_FEATURESET			"feature1"												//训练集目录
#define	FILE_TRAIN_LABELESET			"labels1"													//训练结果集目录

#define	FILE_TEST_FEATURESET			"feature2"												//测试训练集
#define	FILE_TEST_LABELSET				"labels2"													//测试结果集	

#define	IMAGE_SIZE								784																//一张图片的大小

// 训练结果集结构体,The labels values are 0 to 9. 
typedef struct{
	u32 magicNumber;	//0x00000801
	u32 numberImages;	//总条数，60000，0x0000ea60

}labelStr;

// 训练特征集结构体
typedef struct{
	u32 magicNumber;	//0x00000803
	u32 numberImages;	//总条数，60000，0x0000ea60
	u32 rows;					//排数，28
	u32 columns ;			//列数，28

}featureStr;

typedef struct{
	matrixStr* featureData;	//特征数据矩阵
	matrixStr* labelData;		//结果数据矩阵
	u32 num;								//条数
	u32 columns;						//图片的大小	
	u32 rows;								//图片的大小
}miniData;


/**
函数
*/

miniData* MinistGetData(u32 start ,u32 num);
void SaveWeight(matrixStr* weightDat,const char*  fileName);//保存weight数据

#endif
