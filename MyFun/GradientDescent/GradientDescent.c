#include "GradientDescent.h"
#include "math.h"



//�ݶ��½��㷨
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
    return result ;  //�������[0][0]�Ƕ�b�ĵ�����[1][0]�Ƕ�m�ĵ���	
	}
	
	
//�߼��ع��ݶ��½��㷨
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
    return result ;  //�������[0][0]�Ƕ�b�ĵ�����[1][0]�Ƕ�m�ĵ���	
	}


//ѵ��,����m,b�ľ���weight
//gradientDescent��ָ���ݶ��½����㷨
matrixStr* Train(matrixStr* (*gradientDescent)(numpy*,matrixStr*,matrixStr*,matrixStr*),\
	numpy* np,matrixStr* feature,matrixStr* label,float learnRate,u32 times)
{
	u32 i =0;
	matrixStr* res;
	matrixStr* mat_one = np->ones(feature->line,1);
	matrixStr* featureMatrix = np->append(feature,mat_one,vertical);
	matrixStr* weight = np->ones(feature->list+1,label->list);					//һ��[b��m]T�ľ���	
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

//����

matrixStr* Test(matrixStr*(*math)(matrixStr*,matrixStr*),matrixStr*feature,matrixStr* weight)
{
	return math(feature,weight);
}


