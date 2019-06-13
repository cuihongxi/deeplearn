#include "matrix_2.H"
#include "math.H"


u8 GetTypeEnumSize(typeEnum type)
{
	if(type == _UCHAR)return 1;
	else return 4;
}
// 申请一个矩阵
matrixStr* matMalloc(u32 rows,u32 columns,typeEnum type)
{
	matrixStr*	mat = (matrixStr*)malloc((rows*columns)*(GetTypeEnumSize(type)) + sizeof(matrixStr));
	if(mat == 0) 
	{
		ERROR_MAT_LOG("ERROR:动态内存申请失败\r\n");
		return 0;
	}else
	{
		mat->rows = rows;
		mat->columns = columns;
		mat->type = type;
		return mat;	
	}
}

//添加数据
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

//获取矩阵元素单元的地址
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
//打印一个矩阵
void PrintMat(matrixStr* mat)
{
	u32 rows = 0;	//行
	u32 columns = 0;	//列
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



//矩阵相加减,产生新空间
matrixStr* matAddSub(matrixStr* a,matrixStr* b,AlgMat arg)
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
				if(arg == ADD)_Traversal(mat,a,b,+);
				else if(arg == SUB)_Traversal(mat,a,b,-);
			}
		}
		return mat;
	}else ERROR_MAT_LOG("错误：两个矩阵行列数不相等!\r\n");

	return (matrixStr*)-1;
}

//相乘，相加 ,a的第几行跟b的第几列相乘相加
// 返回相乘的结果
//注 ： 目前想到的方法是，假定已知两个矩阵的类型，来定制函数，在应用中遍历所有可能，来调用相应的函数
_GetMat_MultAdd(float,float,float);
_GetMat_MultAdd(float,float,int);
_GetMat_MultAdd(float,float,u8);
_GetMat_MultAdd(float,u8,float);
_GetMat_MultAdd(float,int,float);
_GetMat_MultAdd(int,int,int);
_GetMat_MultAdd(int,int,u8);
_GetMat_MultAdd(int,u8,int);
_GetMat_MultAdd(int,u8,u8);

//矩阵相乘
//返回一个乘积结果矩阵
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
	}else ERROR_MAT_LOG("错误：A的列数与B的行数不相等，不能做乘法\r\n");
	return (matrixStr*)-1;
}

//返回矩阵的转置
//注意，如果不再需要需要释放内存
matrixStr* matrix_T(matrixStr* mat)
{
	matrixStr* mat_t = matMalloc(mat->columns,mat->rows,mat->type);
	u32 rows = 0;
	u32 columns = 0;
	for(rows = 0; rows < mat_t->rows; rows ++)
	{
		for(columns = 0; columns <mat_t->columns; columns ++)
		{
			_Give_MATDAT(mat_t,rows,columns,mat,columns,rows);
		}
	}
	return mat_t;
}

//生成一个矩阵，并全部赋值成num
matrixStr* matrix_Num(u32 rows,u32 columns,u8 num)
{
	u32 hang = 0;	//行
	u32 lie = 0;	//列
	matrixStr* mat = matMalloc(rows,columns,_UCHAR);
	for(hang = 0; hang < mat->rows; hang ++)
	{
		for(lie = 0; lie < mat->columns; lie ++)
		{
			*(u8*)Get_MatAddr(mat,hang,lie) = num;
		}
	}
	return mat;
}


//生成一个矩阵，并全部赋值成1
matrixStr* matrix_One(u32 rows,u32 columns)
{
	return matrix_Num(rows, columns,1);
}

//生成一个矩阵，并全部赋值成0
matrixStr* matrix_Zero(u32 rows,u32 columns)
{
	return matrix_Num(rows, columns,0);
}

// 将mat矩阵,添加到source矩阵中，axis = 1添加到右边，axis = 0 添加到下边
matrixStr* matrix_Append(matrixStr* source,matrixStr* bmat,Axis axis)
{
	matrixStr* mat = 0 ;
	u32 rows = 0;
	u32 columns = 0;
	if(axis == horizontal)	//添加到下边
	{
		if(source->columns != bmat->columns)
			ERROR_MAT_LOG("错误：axis=0，列数必须相同\r\n");
		else
		{
			if(source->type > bmat->type)
				mat = matMalloc(source->rows + bmat->rows,source->columns,source->type);
			else mat = matMalloc(source->rows + bmat->rows,source->columns,bmat->type);
			for(rows = 0; rows < source->rows; rows ++)			//拷贝源矩阵
			{
				for(columns = 0; columns < mat->columns; columns ++)
				{
						_Give_MATDAT(mat,rows,columns,source,rows,columns);
				}
			}

			for(rows = source->rows; rows < mat->rows; rows ++)	//拷贝添加的矩阵
			{
				for(columns = 0; columns < mat->columns; columns ++)
				{
					_Give_MATDAT(mat,rows,columns,bmat,rows-source->rows,columns);
				}
			}
		}
	}
	else
	if(axis == vertical)
	{
		if(source->rows != bmat->rows)
			ERROR_MAT_LOG("错误：axis=1，行数必须相同\r\n");
		else
		{
			if(source->type > bmat->type)
				mat = matMalloc(source->rows,source->columns + bmat->columns,source->type);
			else mat = matMalloc(source->rows ,source->columns + bmat->columns,bmat->type);
			for(columns = 0; columns < source->columns; columns ++)			//拷贝源矩阵
			{
				for(rows = 0; rows < mat->rows; rows ++)
				{
					_Give_MATDAT(mat,rows,columns,source,rows,columns);
				}
			}
			PrintMat(mat);
			for(columns = source->columns; columns < mat->columns; columns ++)	//拷贝添加的矩阵
			{
				for(rows = 0; rows < mat->rows; rows ++)
				{
					_Give_MATDAT(mat,rows,columns,bmat,rows,columns - source->columns);
				}
			}			
		}

	}
	else ERROR_MAT_LOG("错误：axis 必须是0或者1。0添加到下边，1添加到右边\r\n");
	return mat;
}

//截取一段矩阵
matrixStr* matrix_CutOut(matrixStr* source,Axis axis,u32 start,u32 end)
{
	matrixStr* mat = 0;
	u32 rows = 0;	//行
	u32 columns = 0;	//列
	
	if(end >= start)
	{
		if(axis == horizontal)
		{
			if(end > source->rows) ERROR_MAT_LOG("ERROR: END 超出范围\r\n");
			else 
			{
				mat = matMalloc(end - start + 1,source->columns,source->type);
				for(rows = start; rows <= end; rows ++)			//拷贝源矩阵
				{
					for(columns = 0; columns < mat->columns; columns ++)
					{
						_Give_MATDAT(mat,rows-start,columns,source,rows,columns);
					}
				}
			}
		}else
		{
				if(end > source->columns) ERROR_MAT_LOG("ERROR: END 超出范围\r\n");
				else 
				{
					mat = matMalloc(source->rows,end - start + 1,source->type);
					for(columns = start; columns <= end; columns ++)		//拷贝矩阵
					{
						for(rows = 0; rows < mat->rows; rows ++)
						{
								_Give_MATDAT(mat,rows,columns-start,source,rows,columns);
						}
					}	
				}			
		}	
	}
	else ERROR_MAT_LOG("ERROR: END 必须大于 START\r\n");
	return mat;
}

//获取矩阵大小
u32 GetMatLength(matrixStr* mat)
{
	return mat->rows * mat->columns;
}


//矩阵与num的运算
void matAlgorithm(matrixStr* mat,MAT_FLOAT num,Algorithm alg)
{

		u32 rows = 0;	// 行
		u32 columns = 0;	// 列
		for(rows = 0; rows < mat->rows; rows ++)
		{
			for(columns = 0; columns < mat->columns; columns ++)
			{
				if(alg == add)
					*((float*)MAT_DAT_POINTER + rows*mat->columns + columns)	 +=   num;
				else if(alg == sub)
					*((float*)MAT_DAT_POINTER + rows*mat->columns + columns)	 -=   num;
				else if(alg == mul)
					*((float*)MAT_DAT_POINTER + rows*mat->columns + columns)	 *=   num;
				else if(alg == divi)
					*((float*)MAT_DAT_POINTER + rows*mat->columns + columns)	 /=   num;
				
			}
		}

}


//矩阵与矩阵迭代的运算，不产生新空间，结果覆盖第一个矩阵,两个矩阵的类型得相同
void matIteraAlgorithm(matrixStr* tomat,matrixStr* b,AlgMat arg)
{
	if(tomat->type != b->type)
	{
		ERROR_MAT_LOG("错误：两个矩阵行类型不相等!\r\n");
	}
	if(tomat->rows == b->rows && tomat->columns == b->columns)
	{
		u32 rows = 0;
		u32 columns = 0;

		for(rows = 0; rows < tomat->rows; rows ++)
		{
			for(columns = 0; columns < tomat->columns; columns ++)
			{				
				if(arg == add)
					_Traversal(tomat,tomat,b,+);
				else if(arg == sub)
					_Traversal(tomat,tomat,b,-);
				else ERROR_MAT_LOG("错误：无法执行除加减法的迭代运算!\r\n");
			}		
		}

	}else ERROR_MAT_LOG("错误：两个矩阵行列数不相等!\r\n");

}

//矩阵旋转,radian弧度，顺时针为正
matrixStr* matRote(matrixStr* mat_sorce,MAT_FLOAT radian)
{
	matrixStr* mat = matMalloc(mat_sorce->rows,mat_sorce->columns,_FLOAT);
	matrixStr* mat2 = matMalloc(2,2,_FLOAT);
	float data[] = {
		cos(radian), -sin(radian),
		sin(radian),cos(radian),
	};
	matApendDat(mat2,data);
	mat = matDot(mat_sorce,mat2);
	_free(mat2);
	return mat;
	
}

//矩阵缩放,xtimes，ytimes
matrixStr* matZoom(matrixStr* mat_sorce,MAT_FLOAT xtimes,MAT_FLOAT ytimes)
{
	matrixStr* mat = matMalloc(mat_sorce->rows,mat_sorce->columns,_FLOAT);
	matrixStr* mat2 = matMalloc(2,2,_FLOAT);
	float data[] = {
		xtimes, 0,
		0,ytimes,
	};
	matApendDat(mat2,data);
	mat = matDot(mat_sorce,mat2);
	_free(mat2);
	return mat;
	
}

//sigmoid函数
MAT_FLOAT sigmoid(MAT_FLOAT x)
{
    return (1 / (1 + exp(-x)));
}
	
//矩阵sigmoid函数
matrixStr* matSigmoid(matrixStr* feature,matrixStr* weight)
{
	matrixStr* mat = matDot(feature,weight);
	matrixStr* tomat = matMalloc(mat->rows,mat->columns,_FLOAT);
	u32 rows = 0;	// 行
	u32 columns = 0;	// 列
		for(rows = 0; rows < mat->rows; rows ++)
		{
			for(columns = 0; columns < mat->columns; columns ++)
			{
				switch((u8)mat->type)
				{
					case _UCHAR:	*(float*)Get_MatAddr(tomat,rows,columns) = sigmoid(*(u8*)Get_MatAddr(mat,rows,columns));
						break;
					case _INT:		*(float*)Get_MatAddr(tomat,rows,columns) = sigmoid(*(int*)Get_MatAddr(mat,rows,columns));
						break;
					case _FLOAT:	*(float*)Get_MatAddr(tomat,rows,columns) = sigmoid(*(float*)Get_MatAddr(mat,rows,columns));
						break;
				}
			}		
		}
	return tomat;
}


////rows行取exp对数相加,返回和
//matDAT matAddexp(matrixStr* mat,u32 rows)
//{
//	matDAT dat = 0;
//	for(u32 i =0;i<mat->columns;i++)
//	{
//		switch((u8)mat->type)
//		{
//			case _UCHAR:	dat += sigmoid(*(u8*)Get_MatAddr(mat,rows,i));
//				break;
//			case _INT:		dat += sigmoid(*(int*)Get_MatAddr(mat,rows,i));
//				break;
//			case _FLOAT:	dat += sigmoid(*(float*)Get_MatAddr(mat,rows,i));
//				break;
//		}
//	}
		
//	printf("dat = %f\r\n",dat);
//	return dat;
//}
//softmax运算
matrixStr* matSoftmax(matrixStr* feature,matrixStr* weight)
{
		matrixStr* mat = matDot(feature,weight);
		matrixStr* mat_2 ;
		if(mat->type != _FLOAT)	mat_2 = matMalloc(mat->rows,mat->columns,_FLOAT);
		mat_2 = mat;
		matrixStr* matallexp = matMalloc(mat->rows,1,_FLOAT);	//保存exp所有之和
	
		u32 rows = 0;	// 行
		u32 columns = 0;	// 列

			for(rows = 0; rows < matallexp->rows; rows ++)
			{
				*(float*)Get_MatAddr(matallexp,rows,0) = matAddexp(mat,rows);
			}

	
		for(rows = 0; rows < mat->rows; rows ++)
		{
			for(columns = 0; columns < mat->columns; columns ++)
			{
				*((matDAT*)((u8*)mat+sizeof(matrixStr)) + rows*mat->columns + columns) = exp(Get_Mat(mat,rows,columns))/Get_Mat(matallexp,rows,0);			
				switch((u8)mat->type)
				{
					case _INT:		*(float*)Get_MatAddr(mat_2,rows,columns); = exp(*(int*)Get_MatAddr(mat,rows,columns))/ (*(float*)Get_MatAddr(matallexp,rows,0));	
						break;
					case _FLOAT:	*(float*)Get_MatAddr(mat_2,rows,columns); = exp(*(float*)Get_MatAddr(mat,rows,columns))/ (*(float*)Get_MatAddr(matallexp,rows,0));
						break;
				}
			}		
		}
		if(mat->type != _FLOAT)	_free(mat);
		_free(matallexp);
	return mat_2;
}
