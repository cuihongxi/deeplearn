/**
	2019��6��8��15:23:17
	http://yann.lecun.com/exdb/mnist/
	��ȡ����ѵ�������� ѹ������train-images-idx3-ubyte.gz
*/

#ifndef	__MINIST_H
#define	__MINIST_H

#include "udata.h"
#include "matrix.h"
#include "numpy.h"

#define	FILE_TRAIN_FEATURESET			"feature1"												//ѵ����Ŀ¼
#define	FILE_TRAIN_LABELESET			"labels1"													//ѵ�������Ŀ¼

#define	FILE_TEST_FEATURESET			"feature2"												//����ѵ����
#define	FILE_TEST_LABELSET				"labels2"													//���Խ����	

#define	IMAGE_SIZE								784																//һ��ͼƬ�Ĵ�С

// ѵ��������ṹ��,The labels values are 0 to 9. 
typedef struct{
	u32 magicNumber;	//0x00000801
	u32 numberImages;	//��������60000��0x0000ea60

}labelStr;

// ѵ���������ṹ��
typedef struct{
	u32 magicNumber;	//0x00000803
	u32 numberImages;	//��������60000��0x0000ea60
	u32 rows;					//������28
	u32 columns ;			//������28

}featureStr;

typedef struct{
	matrixStr* featureData;	//�������ݾ���
	matrixStr* labelData;		//������ݾ���
	u32 num;								//����
	u32 columns;						//ͼƬ�Ĵ�С	
	u32 rows;								//ͼƬ�Ĵ�С
}miniData;


/**
����
*/

miniData* MinistGetData(u32 start ,u32 num);
void SaveWeight(matrixStr* weightDat,const char*  fileName);//����weight����

#endif
