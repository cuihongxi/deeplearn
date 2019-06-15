#include "GradientDescent.h"
#include "math.h"



//梯度下降算法
matrixStr* GradientDescent(numpy* np,matrixStr* featureMatrix,matrixStr* weight,matrixStr* label)
	{
		matrixStr* result;
		matrixStr* dot = np->dot(featureMatrix,weight);
		np->iteraAlg(dot,label,sub);			//与结果相减,覆盖掉dot	
		result = np->dot_T(featureMatrix,dot);
    np->alg(result,featureMatrix->rows,divi);
		np->alg(result,2,mul);
		
		_free(dot);
    return result ;  //结果矩阵，[0][0]是对b的导数，[1][0]是对m的导数	
	}
	
	
//逻辑回归梯度下降算法
matrixStr* LogicGradientDescent(numpy* np,matrixStr* featureMatrix,matrixStr* weight,matrixStr* label)
	{
		matrixStr* result;
		matrixStr* dot = np->sigmoid(featureMatrix,weight);	
		np->iteraAlg(dot,label,sub);			//与结果相减,覆盖掉dot	
		result = np->dot_T(featureMatrix,dot);
    np->alg(result,featureMatrix->rows,divi);
		np->alg(result,2,mul);	
		_free(dot);

    return result ;  //结果矩阵，[0][0]是对b的导数，[1][0]是对m的导数	
	}


//训练,返回m,b的矩阵weight，//注意，处理后feature的值被改变
//gradientDescent来指定梯度下降的算法
matrixStr* Train(matrixStr* (*gradientDescent)(numpy*,matrixStr*,matrixStr*,matrixStr*),\
	numpy* np,matrixStr* feature,matrixStr* label,matrixStr* weight,float learnRate,u32 times)
{
	u32 i =0;
	matrixStr* res;
		//对feature数据进行归一化处理	
	np->alg(feature,255,divi);	//注意，处理后feature的值被改变
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

//训练MINIST数据集
matrixStr* TrainMinist(numpy* np,matrixStr* feature,matrixStr* label,matrixStr* weight,float learnRate,u32 times)
{
	matrixStr* labelfilter = np->filter(label);						// 对label进行逻辑值处理，产生逻辑矩阵
	Train(LogicGradientDescent,np,feature,labelfilter,weight,learnRate,times);
	_free(labelfilter);
	return weight;
}

//测试

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

//softmax运算

matrixStr* matSoftmax(matrixStr* feature,matrixStr* weight)
{
		
		matrixStr* mat = matDot(feature,weight);
		matrixStr* matallexp = matMalloc(mat->rows,1);	//保存exp所有之和
//	printf(" matDot(feature,weight):\r\n");
//	PrintMat(mat);
		u32 rows = 0;	// 行
		u32 columns = 0;	// 列

			for(rows = 0; rows < matallexp->rows; rows ++)
			{
				*Get_MatAddr(matallexp,rows,0) = matAddRowsExp(mat,rows);//所有的rows的EXP之和
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
		matrixStr* matallexp = matMalloc(mat->rows,1);	//保存exp所有之和
//	printf(" matDot(feature,weight):\r\n");
//	PrintMat(mat);
		u32 rows = 0;	// 行
		u32 columns = 0;	// 列

			for(rows = 0; rows < matallexp->rows; rows ++)
			{
				*Get_MatAddr(matallexp,rows,0) = matAddRows(mat,rows);//所有的rows的EXP之和
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
		//对feature数据进行归一化处理	
	matAlgorithm(feature,255,divi);	//注意，处理后feature的值被改变	
	matrixStr* mat_one = matrix_One(feature->rows,1);
	matrixStr* featureMatrix = matrix_Append(feature,mat_one,vertical);
	_free(mat_one);
	matrixStr* test = math(featureMatrix,weight);
	_free(featureMatrix);
	return test;
}


