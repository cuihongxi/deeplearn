#include "GradientDescent.h"
#include "math.h"



//梯度下降算法
matrixStr* GradientDescent(numpy* np,matrixStr* featureMatrix,matrixStr* weight,matrixStr* label)
	{
		matrixStr* result;
		matrixStr* featureMatrix_T = np->T(featureMatrix);
		matrixStr* dot = np->dot(featureMatrix,weight);
		matrixStr* sub = np->sub(dot,label);
		result = np->dot(featureMatrix_T,sub);
    np->alg(result,featureMatrix->line,divi);
		np->alg(result,2,mul);
		
		_free(featureMatrix_T);
		_free(dot);
		_free(sub);
    return result ;  //结果矩阵，[0][0]是对b的导数，[1][0]是对m的导数	
	}
	
	
//逻辑回归梯度下降算法
matrixStr* LogicGradientDescent(numpy* np,matrixStr* featureMatrix,matrixStr* weight,matrixStr* label)
	{
		matrixStr* result;
		matrixStr* featureMatrix_T = np->T(featureMatrix);
		matrixStr* dot = np->sigmoid(featureMatrix,weight);
		matrixStr* sub = np->sub(dot,label);
		result = np->dot(featureMatrix_T,sub);
    np->alg(result,featureMatrix->line,divi);
		np->alg(result,2,mul);
		
		_free(featureMatrix_T);
		_free(dot);
		_free(sub);
//		np->printMat(result);
    return result ;  //结果矩阵，[0][0]是对b的导数，[1][0]是对m的导数	
	}


//训练,返回m,b的矩阵weight
//gradientDescent来指定梯度下降的算法
matrixStr* Train(matrixStr* (*gradientDescent)(numpy*,matrixStr*,matrixStr*,matrixStr*),\
	numpy* np,matrixStr* feature,matrixStr* label,float learnRate,u32 times)
{
	u32 i =0;
	matrixStr* res;
	matrixStr* mat_one = np->ones(feature->line,1);
	matrixStr* featureMatrix = np->append(feature,mat_one,vertical);
	matrixStr* weight = np->ones(feature->list+1,label->list);					//一个[b，m]T的矩阵	
	_free(mat_one);
  for(i=0;i<times;i++)
	{
		res = gradientDescent(np,featureMatrix,weight,label);
		np->alg(res,learnRate,mul);
		np->iteraAlg(weight,res,sub);
		_free(res);
	}
	_free(featureMatrix);
	
	return weight;
}

//测试

matrixStr* Test(matrixStr*(*math)(matrixStr*,matrixStr*),matrixStr*feature,matrixStr* weight)
{
	return math(feature,weight);
}


