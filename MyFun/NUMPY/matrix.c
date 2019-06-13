#include "matrix.H"
#include "math.H"


// ����һ������
matrixStr* matMalloc(u32 rows,u32 columns)
{
	//��̬����һƬ�ڴ棬��������������������������
	matrixStr* mat = (matrixStr*)malloc((rows*columns)*(sizeof(matDAT)) + sizeof(matrixStr));
	if(mat == 0) 
	{
		ERROR_MAT_LOG("ERROR:��̬�ڴ�����ʧ��\r\n");
		return 0;
	}else
	{
		mat->rows = rows;
		mat->columns = columns;
		return mat;	
	}
}

//�������
void matApendDat(matrixStr* mat , matDAT* dat)
{
	u32 rows = 0;	//��
	u32 columns = 0;	//��

	for(rows = 0; rows < mat->rows; rows ++)
	{
		for(columns = 0; columns < mat->columns; columns ++)
		{
			*((matDAT*)((u8*)mat+sizeof(matrixStr)) + rows*mat->columns + columns) = *dat;
			dat ++;
		}
		
	}
}

//���u8��������
void matApendDatU8(matrixStr* mat , u8* dat)
{
	u32 rows = 0;	//��
	u32 columns = 0;	//��

	for(rows = 0; rows < mat->rows; rows ++)
	{
		for(columns = 0; columns < mat->columns; columns ++)
		{
			*((matDAT*)((u8*)mat+sizeof(matrixStr)) + rows*mat->columns + columns) = *dat;
			dat ++;
		}
		
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
		MAT_LOG("[");
		for(columns = 0; columns < mat->columns; columns ++)
		{
			
			MAT_PRINT;
		}
		MAT_LOG("],\r\n");
	}
	MAT_LOG("}\r\n");
}

//��ȡһ�������Ԫ��
matDAT Get_Mat(matrixStr* mat,u32 rows,u32 columns)
{
	if(rows < mat->rows && columns < mat->columns )
		return 	*((matDAT*)((u8*)mat+sizeof(matrixStr)) + rows*mat->columns + columns);

	else return (matDAT)-1;
}

//��ȡ����Ԫ�ص�Ԫ�ĵ�ַ
matDAT* Get_MatAddr(matrixStr* mat,u32 rows,u32 columns)
{
	if(rows < mat->rows && columns < mat->columns )
		return ((matDAT*)((u8*)mat+sizeof(matrixStr))) + rows*mat->columns + columns;
	else return (matDAT*)-1;
	
}

//�������
matrixStr* matAdd(matrixStr* a,matrixStr* b)
{

	if(a->rows == b->rows && a->columns == b->columns)
	{
		u32 rows = 0;
		u32 columns = 0;
		matrixStr* mat = matMalloc(a->rows,a->columns);

		for(rows = 0; rows < a->rows; rows ++)
		{
			for(columns = 0; columns < a->columns; columns ++)
			{
				*((matDAT*)((u8*)mat+sizeof(matrixStr)) +  rows*mat->columns + columns) = Get_Mat(a,rows,columns) +  Get_Mat(b,rows,columns);
					
			}		
		}
		return mat;
	}else ERROR_MAT_LOG("�����������������������!\r\n");

	return (matrixStr*)-1;
}

//��ˣ���� ,a�ĵڼ��и�b�ĵڼ���������
// ������˵Ľ��
matDAT GetMat_MultAdd(matrixStr* a,matrixStr* b,u32 aline,u32 blist)
{
	u32 i = 0;
	matDAT dat = 0;
	for(i=0;i<a->columns;i++)
	{	
		dat += (matDAT)Get_Mat(a,aline,i) *  (matDAT)Get_Mat(b,i,blist);
	}

	return dat;
}

//�������
//����һ���˻��������
matrixStr* matDot(matrixStr* a,matrixStr* b)
{

	if( a->columns == b->rows)
	{
		u32 rows = 0;
		u32 columns = 0;
		matrixStr* mat = matMalloc(a->rows,b->columns);
		for(rows = 0; rows < a->rows; rows ++)
		{
			for(columns = 0; columns < b->columns; columns ++)
			{
				*Get_MatAddr(mat,rows,columns) = GetMat_MultAdd(a,b,rows,columns);
			}		
		}
		return mat;
	}else ERROR_MAT_LOG("����A��������B����������ȣ��������˷�\r\n");
	return (matrixStr*)-1;
}

//���ؾ����ת��
//ע�⣬���������Ҫ��Ҫ�ͷ��ڴ�
matrixStr* matrix_T(matrixStr* mat)
{
	u32 rows = 0;	//��
	u32 columns = 0;	//��
	matrixStr* mat_t = matMalloc(mat->columns,mat->rows);

	for(rows = 0; rows < mat_t->rows; rows ++)
	{
		for(columns = 0; columns < mat_t->columns; columns ++)
		{
			*Get_MatAddr(mat_t,rows,columns) = Get_Mat(mat,columns,rows);
		}
	}
	return mat_t;

}

//����һ�����󣬲�ȫ����ֵ��num
matrixStr* matrix_Num(u32 rows,u32 columns,matDAT num)
{
	u32 hang = 0;	//��
	u32 lie = 0;	//��
	matrixStr* mat = matMalloc(rows,columns);
	for(hang = 0; hang < mat->rows; hang ++)
	{
		for(lie = 0; lie < mat->columns; lie ++)
		{
			*Get_MatAddr(mat,hang,lie) = num;
		}
	}
	return mat;
}


//����һ�����󣬲�ȫ����ֵ��1
matrixStr* matrix_One(u32 rows,u32 columns)
{
	return matrix_Num(rows, columns,1);
}

//����һ�����󣬲�ȫ����ֵ��0
matrixStr* matrix_Zero(u32 rows,u32 columns)
{
	return matrix_Num(rows, columns,0);
}

// ��mat����,��ӵ�source�����У�axis = 1��ӵ��ұߣ�axis = 0 ��ӵ��±�
matrixStr* matrix_Append(matrixStr* source,matrixStr* bmat,Axis axis)
{
	matrixStr* mat = 0 ;
	u32 rows = 0;	//��
	u32 columns = 0;	//��
	if(axis == horizontal)	//��ӵ��±�
	{
		if(source->columns != bmat->columns)
			ERROR_MAT_LOG("����axis=0������������ͬ\r\n");
		else
		{
			mat = matMalloc(source->rows + bmat->rows,source->columns);
			for(rows = 0; rows < source->rows; rows ++)			//����Դ����
			{
				for(columns = 0; columns < mat->columns; columns ++)
				{
					*Get_MatAddr(mat,rows,columns) = Get_Mat(source,rows,columns);
				}
			}

			for(rows = source->rows; rows < mat->rows; rows ++)	//������ӵľ���
			{
				for(columns = 0; columns < mat->columns; columns ++)
				{
					*Get_MatAddr(mat,rows,columns) = Get_Mat(bmat,rows - source->rows ,columns);
				}
			}
		}
	}
	else
	if(axis == vertical)
	{
		if(source->rows != bmat->rows)
			ERROR_MAT_LOG("����axis=1������������ͬ\r\n");
		else
		{
			mat = matMalloc(source->rows,source->columns + bmat->columns);
			for(columns = 0; columns < source->columns; columns ++)			//����Դ����
			{
				for(rows = 0; rows < mat->rows; rows ++)
				{
					*Get_MatAddr(mat,rows,columns) = Get_Mat(source,rows,columns);
				}
			}

			for(columns = source->columns; columns < mat->columns; columns ++)	//������ӵľ���
			{
				for(rows = 0; rows < mat->rows; rows ++)
				{
					*Get_MatAddr(mat,rows,columns) = Get_Mat(bmat,rows,columns - source->columns);
				}
			}		
		}

	}
	else ERROR_MAT_LOG("����axis ������0����1��0��ӵ��±ߣ�1��ӵ��ұ�\r\n");
	return mat;
}

//��ȡһ�ξ���
matrixStr* matrix_CutOut(matrixStr* source,Axis axis,u32 start,u32 end)
{
	matrixStr* mat = 0;
	u32 rows = 0;	//��
	u32 columns = 0;	//��
	
	if(end >= start)
	{
		if(axis == horizontal)
		{
			if(end > source->rows) ERROR_MAT_LOG("ERROR: END ������Χ\r\n");
			else 
			{
				mat = matMalloc(end - start + 1,source->columns);
				for(rows = start; rows <= end; rows ++)			//����Դ����
				{
					for(columns = 0; columns < mat->columns; columns ++)
					{
						*Get_MatAddr(mat,rows-start,columns) = Get_Mat(source,rows,columns);
					}
				}
			}
		}else
		{
				if(end > source->columns) ERROR_MAT_LOG("ERROR: END ������Χ\r\n");
				else 
				{
					mat = matMalloc(source->rows,end - start + 1);
					for(columns = start; columns <= end; columns ++)		//��������
					{
						for(rows = 0; rows < mat->rows; rows ++)
						{
							*Get_MatAddr(mat,rows,columns-start) = Get_Mat(source,rows,columns);
						}
					}	
				}			
		}	
	}
	else ERROR_MAT_LOG("ERROR: END ������� START\r\n");
	return mat;
}

//��ȡ�����С
u32 GetMatLength(matrixStr* mat)
{
	return mat->rows * mat->columns;
}

//�������
matrixStr* matSub(matrixStr* a,matrixStr* b)
{

	if(a->rows == b->rows && a->columns == b->columns)
	{
		u32 rows = 0;
		u32 columns = 0;
		matrixStr* mat = matMalloc(a->rows,a->columns);
		for(rows = 0; rows < a->rows; rows ++)
		{
			for(columns = 0; columns < a->columns; columns ++)
			{
				*((matDAT*)((u8*)mat+sizeof(matrixStr)) + rows*mat->columns + columns)	 = Get_Mat(a,rows,columns) -  Get_Mat(b,rows,columns);
				
			}		
		}
		return mat;
	}else ERROR_MAT_LOG("�����������������������!\r\n");

	return (matrixStr*)-1;
}

//������num������
void matAlgorithm(matrixStr* mat,matDAT num,Algorithm alg)
{

		u32 rows = 0;	// ��
		u32 columns = 0;	// ��
		for(rows = 0; rows < mat->rows; rows ++)
		{
			for(columns = 0; columns < mat->columns; columns ++)
			{
				if(alg == add)
					*((matDAT*)((u8*)mat+sizeof(matrixStr)) + rows*mat->columns + columns)	 = Get_Mat(mat,rows,columns) + num;
				else if(alg == sub)
					*((matDAT*)((u8*)mat+sizeof(matrixStr)) + rows*mat->columns + columns)	 = Get_Mat(mat,rows,columns) - num;
				else if(alg == mul)
					*((matDAT*)((u8*)mat+sizeof(matrixStr)) + rows*mat->columns + columns)	 = Get_Mat(mat,rows,columns) * num;
				else if(alg == divi)
					*((matDAT*)((u8*)mat+sizeof(matrixStr)) + rows*mat->columns + columns)	 = Get_Mat(mat,rows,columns) / num;
				
			}		
		}

}


//�����������������㣬�������¿ռ䣬������ǵ�һ������
void matIteraAlgorithm(matrixStr* a,matrixStr* b,Algorithm alg)
{
	if(a->rows == b->rows && a->columns == b->columns)
	{
		u32 rows = 0;
		u32 columns = 0;

		for(rows = 0; rows < a->rows; rows ++)
		{
			for(columns = 0; columns < a->columns; columns ++)
			{
				
				if(alg == add)
					*(matDAT*)(&a->columns + 1 + rows*a->columns + columns) = Get_Mat(a,rows,columns) +  Get_Mat(b,rows,columns);
				else if(alg == sub)
					*(matDAT*)(&a->columns + 1 + rows*a->columns + columns) = Get_Mat(a,rows,columns) -  Get_Mat(b,rows,columns);
				else ERROR_MAT_LOG("�����޷�ִ�г��Ӽ����ĵ�������!\r\n");
			}		
		}

	}else ERROR_MAT_LOG("�����������������������!\r\n");

}

//������ת,radian���ȣ�˳ʱ��Ϊ��
matrixStr* matRote(matrixStr* mat_sorce,float radian)
{
	matrixStr* mat = matMalloc(mat_sorce->rows,mat_sorce->columns);
	matrixStr* mat2 = matMalloc(2,2);
	matDAT data[] = {
		cos(radian), -sin(radian),
		sin(radian),cos(radian),
	};
	matApendDat(mat2,data);
	mat = matDot(mat_sorce,mat2);
	_free(mat2);
	return mat;
	
}

//��������,xtimes��ytimes
matrixStr* matZoom(matrixStr* mat_sorce,float xtimes,float ytimes)
{
	matrixStr* mat = matMalloc(mat_sorce->rows,mat_sorce->columns);
	matrixStr* mat2 = matMalloc(2,2);
	matDAT data[] = {
		xtimes, 0,
		0,ytimes,
	};
	matApendDat(mat2,data);
	mat = matDot(mat_sorce,mat2);
	_free(mat2);
	return mat;
	
}

//sigmoid����
matDAT sigmoid(matDAT x)
{
    return (1 / (1 + exp(-x)));
}
	
//����sigmoid����
matrixStr* matSigmoid(matrixStr* feature,matrixStr* weight)
{
	matrixStr* mat = matDot(feature,weight);
	u32 rows = 0;	// ��
	u32 columns = 0;	// ��
		for(rows = 0; rows < mat->rows; rows ++)
		{
			for(columns = 0; columns < mat->columns; columns ++)
			{
					*((matDAT*)((u8*)mat+sizeof(matrixStr)) + rows*mat->columns + columns)	 = sigmoid(Get_Mat(mat,rows,columns));
			}		
		}
	return mat;
}


//rows��ȡexp�������,���غ�
matDAT matAddexp(matrixStr* mat,u32 rows)
{
	matDAT dat = 0;
	for(u32 i =0;i<mat->columns;i++)
	{
		dat += exp(Get_Mat(mat,rows,i));
	}
		
//	printf("dat = %f\r\n",dat);
	return dat;
}

//columns��ȡexp�������,���غ�
matDAT matAddColumnsExp(matrixStr* mat,u32 columns)
{
	matDAT dat = 0;
	for(u32 i =0;i<mat->rows;i++)
	{
		dat += exp(Get_Mat(mat,i,columns));
	}
	return dat;
}





//label������,���0~9�ľ���
matrixStr* matLabelFilter(matrixStr* label)
{
		matrixStr* mat = matrix_Zero(label->rows,10);	//һ��ȫ0�ľ���
	//��ͬ������Ӧλ�ø�ֵ1
		for(u32 rows = 0; rows < mat->rows; rows ++)
		{
			*Get_MatAddr(mat,rows,Get_Mat(label,rows,0)) = 1;					
		}
		return mat;
}

//��ȡ�������״
void matShape(matrixStr* mat)
{
	MAT_LOG("(%d,%d)\r\n",mat->rows,mat->columns);
}





