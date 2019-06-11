#include "matrix_2.H"
#include "math.H"


u8 GetTypeEnumSize(typeEnum type)
{
	if(type == _UCHAR)return 1;
	else return 4;
}
// ����һ������
matrixStr* matMalloc(u32 rows,u32 columns,typeEnum type)
{
	matrixStr*	mat = (matrixStr*)malloc((rows*columns)*(GetTypeEnumSize(type)) + sizeof(matrixStr));
	if(mat == 0) 
	{
		ERROR_MAT_LOG("ERROR:��̬�ڴ�����ʧ��\r\n");
		return 0;
	}else
	{
		mat->rows = rows;
		mat->columns = columns;
		mat->type = type;
		return mat;	
	}
}

//�������
void matApendDat(matrixStr* mat , void* dat)
{
	u32 size = GetTypeEnumSize(mat->type)*(mat->rows * mat->columns);
	u8*p = (u8*)dat;
	u8* pmat = MAT_DAT_POINTER;
	for(u32 i = 0; i < size; i ++)
	{
		pmat[i] = p[i];
	}
}

//��ȡ����Ԫ�ص�Ԫ�ĵ�ַ
u32 Get_MatAddr(matrixStr* mat,u32 rows,u32 columns)
{
	if(rows < mat->rows && columns < mat->columns )
	{
		return (u32)(MAT_DAT_POINTER + GetTypeEnumSize(mat->type)*(rows*mat->columns + columns));
	}
	else return 0;
}

void SwitchMat(matrixStr* mat,u32 rows,u32 columns)
{
	switch((u8)mat->type)
	{
		case _UCHAR: 	MAT_LOG("%d,	",*((u8*)Get_MatAddr(mat,rows,columns)));//MAT_LOG("%d,	",*((u8*)MAT_DAT_POINTER + rows*mat->columns + columns));		
		break;
		case _INT: 	MAT_LOG("%d,	",*((int*)Get_MatAddr(mat,rows,columns)));//MAT_LOG("%d,	",*((MAT_INT*)MAT_DAT_POINTER + rows*mat->columns + columns));		
		break;	
		case _FLOAT:MAT_LOG("%f,	",*((float*)Get_MatAddr(mat,rows,columns)));//MAT_LOG("%f,	",*((MAT_FLOAT*)MAT_DAT_POINTER + rows*mat->columns + columns)); 	
		break;	
	}
}
//��ӡһ������
void PrintMat(matrixStr* mat)
{
	u32 rows = 0;	//��
	u32 columns = 0;	//��
	MAT_LOG("{\r\n");
	for(rows = 0; rows < mat->rows; rows ++)
	{
		MAT_LOG("	[ ");
		for(columns = 0; columns < mat->columns; columns ++)
		{
			SwitchMat(mat,rows,columns);
		}
		MAT_LOG("],\r\n");
	}
	MAT_LOG("}\r\n");
}



//�������
matrixStr* matAdd(matrixStr* a,matrixStr* b)
{

	if(a->rows == b->rows && a->columns == b->columns)
	{
		u32 rows = 0;
		u32 columns = 0;
		matrixStr* mat;		
		if(a->type == _FLOAT ||  b->type == _FLOAT) mat = matMalloc(a->rows,a->columns,_FLOAT);
		else mat = matMalloc(a->rows,a->columns,_INT);
		for(rows = 0; rows < mat->rows; rows ++)
		{
			for(columns = 0; columns < mat->columns; columns ++)
			{
					_Traversal(mat,a,b,+);
			}
		}
		return mat;
	}else ERROR_MAT_LOG("�����������������������!\r\n");

	return (matrixStr*)-1;
}

//��ˣ���� ,a�ĵڼ��и�b�ĵڼ���������
// ������˵Ľ��
//ע �� Ŀǰ�뵽�ķ����ǣ��ٶ���֪������������ͣ������ƺ�������Ӧ���б������п��ܣ���������Ӧ�ĺ���
_GetMat_MultAdd(float,float,float);
_GetMat_MultAdd(float,float,int);
_GetMat_MultAdd(float,float,u8);
_GetMat_MultAdd(float,u8,float);
_GetMat_MultAdd(float,int,float);
_GetMat_MultAdd(int,int,int);
_GetMat_MultAdd(int,int,u8);
_GetMat_MultAdd(int,u8,int);
_GetMat_MultAdd(int,u8,u8);

//�������
//����һ���˻��������
matrixStr* matDot(matrixStr* a,matrixStr* b)
{
	if( a->columns == b->rows)
	{
		u32 rows = 0;
		u32 columns = 0;
		matrixStr* mat;		
		if(a->type == _FLOAT ||  b->type == _FLOAT) mat = matMalloc(a->rows,b->columns,_FLOAT);
		else mat = matMalloc(a->rows,b->columns,_INT);
		
		for(rows = 0; rows < a->rows; rows ++)
		{
			for(columns = 0; columns < b->columns; columns ++)
			{
				_TraversalDot(mat,a,b);
			}		
		}
		return mat;
	}else ERROR_MAT_LOG("����A��������B����������ȣ��������˷�\r\n");
	return (matrixStr*)-1;
}

////���ؾ����ת��
////ע�⣬���������Ҫ��Ҫ�ͷ��ڴ�
//matrixStr* matrix_T(matrixStr* mat)
//{
//	u32 rows = 0;	//��
//	u32 columns = 0;	//��
//	matrixStr* mat_t = matMalloc(mat->columns,mat->rows);

//	for(rows = 0; rows < mat_t->rows; rows ++)
//	{
//		for(columns = 0; columns < mat_t->columns; columns ++)
//		{
//			*Get_MatAddr(mat_t,rows,columns) = Get_Mat(mat,columns,rows);
//		}
//	}
//	return mat_t;

//}

////����һ�����󣬲�ȫ����ֵ��num
//matrixStr* matrix_Num(u32 rows,u32 columns,matDAT num)
//{
//	u32 hang = 0;	//��
//	u32 lie = 0;	//��
//	matrixStr* mat = matMalloc(rows,columns);
//	for(hang = 0; hang < mat->rows; hang ++)
//	{
//		for(lie = 0; lie < mat->columns; lie ++)
//		{
//			*Get_MatAddr(mat,hang,lie) = num;
//		}
//	}
//	return mat;
//}


////����һ�����󣬲�ȫ����ֵ��1
//matrixStr* matrix_One(u32 rows,u32 columns)
//{
//	return matrix_Num(rows, columns,1);
//}

////����һ�����󣬲�ȫ����ֵ��0
//matrixStr* matrix_Zero(u32 rows,u32 columns)
//{
//	return matrix_Num(rows, columns,0);
//}

//// ��mat����,��ӵ�source�����У�axis = 1��ӵ��ұߣ�axis = 0 ��ӵ��±�
//matrixStr* matrix_Append(matrixStr* source,matrixStr* bmat,Axis axis)
//{
//	matrixStr* mat = 0 ;
//	u32 rows = 0;	//��
//	u32 columns = 0;	//��
//	if(axis == horizontal)	//��ӵ��±�
//	{
//		if(source->columns != bmat->columns)
//			ERROR_MAT_LOG("����axis=0������������ͬ\r\n");
//		else
//		{
//			mat = matMalloc(source->rows + bmat->rows,source->columns);
//			for(rows = 0; rows < source->rows; rows ++)			//����Դ����
//			{
//				for(columns = 0; columns < mat->columns; columns ++)
//				{
//					*Get_MatAddr(mat,rows,columns) = Get_Mat(source,rows,columns);
//				}
//			}

//			for(rows = source->rows; rows < mat->rows; rows ++)	//������ӵľ���
//			{
//				for(columns = 0; columns < mat->columns; columns ++)
//				{
//					*Get_MatAddr(mat,rows,columns) = Get_Mat(bmat,rows - source->rows ,columns);
//				}
//			}
//		}
//	}
//	else
//	if(axis == vertical)
//	{
//		if(source->rows != bmat->rows)
//			ERROR_MAT_LOG("����axis=1������������ͬ\r\n");
//		else
//		{
//			mat = matMalloc(source->rows,source->columns + bmat->columns);
//			for(columns = 0; columns < source->columns; columns ++)			//����Դ����
//			{
//				for(rows = 0; rows < mat->rows; rows ++)
//				{
//					*Get_MatAddr(mat,rows,columns) = Get_Mat(source,rows,columns);
//				}
//			}

//			for(columns = source->columns; columns < mat->columns; columns ++)	//������ӵľ���
//			{
//				for(rows = 0; rows < mat->rows; rows ++)
//				{
//					*Get_MatAddr(mat,rows,columns) = Get_Mat(bmat,rows,columns - source->columns);
//				}
//			}		
//		}

//	}
//	else ERROR_MAT_LOG("����axis ������0����1��0��ӵ��±ߣ�1��ӵ��ұ�\r\n");
//	return mat;
//}

////��ȡһ�ξ���
//matrixStr* matrix_CutOut(matrixStr* source,Axis axis,u32 start,u32 end)
//{
//	matrixStr* mat = 0;
//	u32 rows = 0;	//��
//	u32 columns = 0;	//��
//	
//	if(end >= start)
//	{
//		if(axis == horizontal)
//		{
//			if(end > source->rows) ERROR_MAT_LOG("ERROR: END ������Χ\r\n");
//			else 
//			{
//				mat = matMalloc(end - start + 1,source->columns);
//				for(rows = start; rows <= end; rows ++)			//����Դ����
//				{
//					for(columns = 0; columns < mat->columns; columns ++)
//					{
//						*Get_MatAddr(mat,rows-start,columns) = Get_Mat(source,rows,columns);
//					}
//				}
//			}
//		}else
//		{
//				if(end > source->columns) ERROR_MAT_LOG("ERROR: END ������Χ\r\n");
//				else 
//				{
//					mat = matMalloc(source->rows,end - start + 1);
//					for(columns = start; columns <= end; columns ++)		//��������
//					{
//						for(rows = 0; rows < mat->rows; rows ++)
//						{
//							*Get_MatAddr(mat,rows,columns-start) = Get_Mat(source,rows,columns);
//						}
//					}	
//				}			
//		}	
//	}
//	else ERROR_MAT_LOG("ERROR: END ������� START\r\n");
//	return mat;
//}

////��ȡ�����С
//u32 GetMatLength(matrixStr* mat)
//{
//	return mat->rows * mat->columns;
//}

////�������
//matrixStr* matSub(matrixStr* a,matrixStr* b)
//{

//	if(a->rows == b->rows && a->columns == b->columns)
//	{
//		u32 rows = 0;
//		u32 columns = 0;
//		matrixStr* mat = matMalloc(a->rows,a->columns);
//		for(rows = 0; rows < a->rows; rows ++)
//		{
//			for(columns = 0; columns < a->columns; columns ++)
//			{
//				*((matDAT*)((u8*)mat+sizeof(matrixStr)) + rows*mat->columns + columns)	 = Get_Mat(a,rows,columns) -  Get_Mat(b,rows,columns);
//				
//			}		
//		}
//		return mat;
//	}else ERROR_MAT_LOG("�����������������������!\r\n");

//	return (matrixStr*)-1;
//}

////������num������
//void matAlgorithm(matrixStr* mat,MAT_FLOAT num,Algorithm alg)
//{

//		u32 rows = 0;	// ��
//		u32 columns = 0;	// ��
//		for(rows = 0; rows < mat->rows; rows ++)
//		{
//			for(columns = 0; columns < mat->columns; columns ++)
//			{
//				if(alg == add)
//					*((matDAT*)((u8*)mat+sizeof(matrixStr)) + rows*mat->columns + columns)	 = Get_Mat(mat,rows,columns) + num;
//				else if(alg == sub)
//					*((matDAT*)((u8*)mat+sizeof(matrixStr)) + rows*mat->columns + columns)	 = Get_Mat(mat,rows,columns) - num;
//				else if(alg == mul)
//					*((matDAT*)((u8*)mat+sizeof(matrixStr)) + rows*mat->columns + columns)	 = Get_Mat(mat,rows,columns) * num;
//				else if(alg == divi)
//					*((matDAT*)((u8*)mat+sizeof(matrixStr)) + rows*mat->columns + columns)	 = Get_Mat(mat,rows,columns) / num;
//				
//			}		
//		}

//}


////�����������������㣬�������¿ռ䣬������ǵ�һ������
//void matIteraAlgorithm(matrixStr* a,matrixStr* b,Algorithm alg)
//{
//	if(a->rows == b->rows && a->columns == b->columns)
//	{
//		u32 rows = 0;
//		u32 columns = 0;

//		for(rows = 0; rows < a->rows; rows ++)
//		{
//			for(columns = 0; columns < a->columns; columns ++)
//			{
//				
//				if(alg == add)
//					*(matDAT*)(&a->columns + 1 + rows*a->columns + columns) = Get_Mat(a,rows,columns) +  Get_Mat(b,rows,columns);
//				else if(alg == sub)
//					*(matDAT*)(&a->columns + 1 + rows*a->columns + columns) = Get_Mat(a,rows,columns) -  Get_Mat(b,rows,columns);
//				else ERROR_MAT_LOG("�����޷�ִ�г��Ӽ����ĵ�������!\r\n");
//			}		
//		}

//	}else ERROR_MAT_LOG("�����������������������!\r\n");

//}

////������ת,radian���ȣ�˳ʱ��Ϊ��
//matrixStr* matRote(matrixStr* mat_sorce,MAT_FLOAT radian)
//{
//	matrixStr* mat = matMalloc(mat_sorce->rows,mat_sorce->columns);
//	matrixStr* mat2 = matMalloc(2,2);
//	matDAT data[] = {
//		cos(radian), -sin(radian),
//		sin(radian),cos(radian),
//	};
//	matApendDat(mat2,data);
//	mat = matDot(mat_sorce,mat2);
//	_free(mat2);
//	return mat;
//	
//}

////��������,xtimes��ytimes
//matrixStr* matZoom(matrixStr* mat_sorce,MAT_FLOAT xtimes,MAT_FLOAT ytimes)
//{
//	matrixStr* mat = matMalloc(mat_sorce->rows,mat_sorce->columns);
//	matrixStr* mat2 = matMalloc(2,2);
//	matDAT data[] = {
//		xtimes, 0,
//		0,ytimes,
//	};
//	matApendDat(mat2,data);
//	mat = matDot(mat_sorce,mat2);
//	_free(mat2);
//	return mat;
//	
//}

////sigmoid����
//MAT_FLOAT sigmoid(MAT_FLOAT x)
//{
//    return (1 / (1 + exp(-x)));
//}
//	
////����sigmoid����
//matrixStr* matSigmoid(matrixStr* feature,matrixStr* weight)
//{
//	matrixStr* mat = matDot(feature,weight);
//	u32 rows = 0;	// ��
//	u32 columns = 0;	// ��
//		for(rows = 0; rows < mat->rows; rows ++)
//		{
//			for(columns = 0; columns < mat->columns; columns ++)
//			{
//					*((matDAT*)((u8*)mat+sizeof(matrixStr)) + rows*mat->columns + columns)	 = sigmoid(Get_Mat(mat,rows,columns));
//			}		
//		}
//	return mat;
//}


////rows��ȡexp�������,���غ�
//matDAT matAddexp(matrixStr* mat,u32 rows)
//{
//	matDAT dat = 0;
//	for(u32 i =0;i<mat->columns;i++)
//	{
//		dat += exp(Get_Mat(mat,rows,i));
//	}
//		
////	printf("dat = %f\r\n",dat);
//	return dat;
//}
////softmax����
//matrixStr* matSoftmax(matrixStr* feature,matrixStr* weight)
//{
//		matrixStr* mat = matDot(feature,weight);
//		matrixStr* matallexp = matMalloc(mat->rows,1);	//����exp����֮��
//	
//		u32 rows = 0;	// ��
//		u32 columns = 0;	// ��

//			for(rows = 0; rows < matallexp->rows; rows ++)
//			{
//				*Get_MatAddr(matallexp,rows,0) = matAddexp(mat,rows);
//			}

//	
//		for(rows = 0; rows < mat->rows; rows ++)
//		{
//			for(columns = 0; columns < mat->columns; columns ++)
//			{
//			//	printf("exp(Get_Mat(mat,rows,columns)) = %f,Get_Mat(matallexp,0,columns) = %f\r\n",exp(Get_Mat(mat,rows,columns)),Get_Mat(matallexp,0,columns));
//				*((matDAT*)((u8*)mat+sizeof(matrixStr)) + rows*mat->columns + columns) = exp(Get_Mat(mat,rows,columns))/Get_Mat(matallexp,rows,0);
//			//	printf("exp(Get_Mat(mat,rows,columns))/Get_Mat(matallexp,1,columns)= %f\r\n",*((matDAT*)((u8*)mat+sizeof(matrixStr)) + rows*mat->columns + columns));
//					
//			}		
//		}
//		_free(matallexp);
//	return mat;
//}
