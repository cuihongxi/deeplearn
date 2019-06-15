#include "GradientDescent.h"
#include "math.h"



//�ݶ��½��㷨
matrixStr* GradientDescent(numpy* np,matrixStr* featureMatrix,matrixStr* weight,matrixStr* label)
	{
		matrixStr* result;
		matrixStr* dot = np->dot(featureMatrix,weight);
		np->iteraAlg(dot,label,sub);			//�������,���ǵ�dot	
		result = np->dot_T(featureMatrix,dot);
    np->alg(result,featureMatrix->rows,divi);
		np->alg(result,2,mul);
		
		_free(dot);
    return result ;  //�������[0][0]�Ƕ�b�ĵ�����[1][0]�Ƕ�m�ĵ���	
	}
	
	
//�߼��ع��ݶ��½��㷨
matrixStr* LogicGradientDescent(numpy* np,matrixStr* featureMatrix,matrixStr* weight,matrixStr* label)
	{
		matrixStr* result;
		matrixStr* dot = np->sigmoid(featureMatrix,weight);	
		np->iteraAlg(dot,label,sub);			//�������,���ǵ�dot	
		result = np->dot_T(featureMatrix,dot);
    np->alg(result,featureMatrix->rows,divi);
		np->alg(result,2,mul);	
		_free(dot);

    return result ;  //�������[0][0]�Ƕ�b�ĵ�����[1][0]�Ƕ�m�ĵ���	
	}


//ѵ��,����m,b�ľ���weight��//ע�⣬�����feature��ֵ���ı�
//gradientDescent��ָ���ݶ��½����㷨
matrixStr* Train(matrixStr* (*gradientDescent)(numpy*,matrixStr*,matrixStr*,matrixStr*),\
	numpy* np,matrixStr* feature,matrixStr* label,matrixStr* weight,float learnRate,u32 times)
{
	u32 i =0;
	matrixStr* res;
		//��feature���ݽ��й�һ������	
	np->alg(feature,255,divi);	//ע�⣬�����feature��ֵ���ı�
	matrixStr* mat_one = np->ones(feature->rows,1);
	matrixStr* featureMatrix = np->append(feature,mat_one,vertical);
	_free(mat_one);
  for(i=0;i<times;i++)
	{
		res = gradientDescent(np,featureMatrix,weight,label);
		np->alg(res,learnRate,mul);	//weight*learnRate
		np->iteraAlg(weight,res,sub);//weight = weight - weight*learnRate
	//	printf("----------res---------\r\n");
	//	np->printMat(res);
		_free(res);
	}
	_free(featureMatrix);

	return weight;
}

//ѵ��MINIST���ݼ�
matrixStr* TrainMinist(numpy* np,matrixStr* feature,matrixStr* label,matrixStr* weight,float learnRate,u32 times)
{
	matrixStr* labelfilter = np->filter(label);						// ��label�����߼�ֵ���������߼�����
	Train(LogicGradientDescent,np,feature,labelfilter,weight,learnRate,times);
	_free(labelfilter);
	return weight;
}

//����

matDAT matAddRowsExp(matrixStr* mat,u32 rows)
{
	matDAT dat = 0;
	for(u32 i =0;i<mat->columns;i++)
	{
		dat += exp(Get_Mat(mat,rows,i));
	}
	return dat;
}

matDAT matAddRows(matrixStr* mat,u32 rows)
{
	matDAT dat = 0;
	for(u32 i =0;i<mat->columns;i++)
	{
		dat += (Get_Mat(mat,rows,i));
	}
	return dat;
}

//softmax����

matrixStr* matSoftmax(matrixStr* feature,matrixStr* weight)
{
		
		matrixStr* mat = matDot(feature,weight);
		matrixStr* matallexp = matMalloc(mat->rows,1);	//����exp����֮��
//	printf(" matDot(feature,weight):\r\n");
//	PrintMat(mat);
		u32 rows = 0;	// ��
		u32 columns = 0;	// ��

			for(rows = 0; rows < matallexp->rows; rows ++)
			{
				*Get_MatAddr(matallexp,rows,0) = matAddRowsExp(mat,rows);//���е�rows��EXP֮��
			}

	
		for(rows = 0; rows < mat->rows; rows ++)
		{
			for(columns = 0; columns < mat->columns; columns ++)
			{
				
			//	printf("Get_Mat(mat,rows,columns) = %f;exp(rows,columns) = %f,Get_Mat(matallexp,0,columns) = %f\r\n",Get_Mat(mat,rows,columns),exp(Get_Mat(mat,rows,columns)),Get_Mat(matallexp,0,columns));
				*((matDAT*)((u8*)mat+sizeof(matrixStr)) + rows*mat->columns + columns) = exp(Get_Mat(mat,rows,columns))/Get_Mat(matallexp,rows,0);
			//	printf("exp(Get_Mat(mat,rows,columns))/Get_Mat(matallexp,1,columns)= %f\r\n",*((matDAT*)((u8*)mat+sizeof(matrixStr)) + rows*mat->columns + columns));
					
			}		
		}
		_free(matallexp);
	return mat;
}

matrixStr* matmeth01(matrixStr* feature,matrixStr* weight)
{
		
		matrixStr* mat = matDot(feature,weight);
		matrixStr* matallexp = matMalloc(mat->rows,1);	//����exp����֮��
//	printf(" matDot(feature,weight):\r\n");
//	PrintMat(mat);
		u32 rows = 0;	// ��
		u32 columns = 0;	// ��

			for(rows = 0; rows < matallexp->rows; rows ++)
			{
				*Get_MatAddr(matallexp,rows,0) = matAddRows(mat,rows);//���е�rows��EXP֮��
			}

	
		for(rows = 0; rows < mat->rows; rows ++)
		{
			for(columns = 0; columns < mat->columns; columns ++)
			{
				
			//	printf("Get_Mat(mat,rows,columns) = %f;exp(rows,columns) = %f,Get_Mat(matallexp,0,columns) = %f\r\n",Get_Mat(mat,rows,columns),exp(Get_Mat(mat,rows,columns)),Get_Mat(matallexp,0,columns));
				*((matDAT*)((u8*)mat+sizeof(matrixStr)) + rows*mat->columns + columns) = (Get_Mat(mat,rows,columns))/Get_Mat(matallexp,rows,0);
			//	printf("exp(Get_Mat(mat,rows,columns))/Get_Mat(matallexp,1,columns)= %f\r\n",*((matDAT*)((u8*)mat+sizeof(matrixStr)) + rows*mat->columns + columns));
					
			}		
		}
		_free(matallexp);
	return mat;
}

matrixStr* Test(matrixStr*(*math)(matrixStr*,matrixStr*),matrixStr*feature,matrixStr* weight)
{
		//��feature���ݽ��й�һ������	
	matAlgorithm(feature,255,divi);	//ע�⣬�����feature��ֵ���ı�	
	matrixStr* mat_one = matrix_One(feature->rows,1);
	matrixStr* featureMatrix = matrix_Append(feature,mat_one,vertical);
	_free(mat_one);
	matrixStr* test = math(featureMatrix,weight);
	_free(featureMatrix);
	return test;
}


