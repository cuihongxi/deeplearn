#include "numpy.h"

//��ʼ��numpy����
void numpy_Init(numpy* np)
{
	np->array = matMalloc;
	np->apendData = matApendDat;
	np->apendDataU8 = matApendDatU8;
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
	np->sigmoid = matSigmoid;
	np->filter = matLabelFilter;
	np->shape = matShape;
	np->dot_T = matDot_T;
}

