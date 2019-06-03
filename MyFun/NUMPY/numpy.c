#include "numpy.h"

//初始化numpy对象
void numpy_Init(numpy* np)
{
	np->array = matMalloc;
	np->apendData = matApendDat;
	np->printMat = PrintMat;
	np->T = matrix_T;
	np->ones = matrix_One;
	np->zeros = matrix_Zero;
	np->dot = matDot;
	np->append = matrix_Append;
	np->cutOut = matrix_CutOut;
	np->len = GetMatLength;
	np->sub = matSub;
	np->alg = matAlgorithm;
	np->iteraAlg = matIteraAlgorithm;
}

