#include "matrix.h"
#include "math.h"


// 申请一个矩阵
matrixStr* matMalloc(u32 line,u32 list)
{
	//动态申请一片内存，并多申请两个用来保存行列数
	matrixStr* mat = (matrixStr*)malloc((line*list+2)*(sizeof(matDAT)/sizeof(u8)));
	if(mat == 0) 
	{
		ERROR_MAT_LOG("ERROR:动态内存申请失败\r\n");
		return 0;
	}else
	{
		mat->line = line;
		mat->list = list;
		return mat;	
	}
}

//添加数据&mat->list + 1
void matApendDat(matrixStr* mat , matDAT* dat)
{
	u32 L = 0;	//行
	u32 H = 0;	//列

	for(L = 0; L < mat->line; L ++)
	{
		for(H = 0; H < mat->list; H ++)
		{
			*(matDAT*)(mat+sizeof(matrixStr) + L*mat->list + H) = *dat;
			dat ++;
		}
		
	}
}



//打印一个矩阵
void PrintMat(matrixStr* mat)
{
	u32 L = 0;	//行
	u32 H = 0;	//列
	MAT_LOG("{\r\n");
	for(L = 0; L < mat->line; L ++)
	{
		MAT_LOG("[");
		for(H = 0; H < mat->list; H ++)
		{
			
			MAT_PRINT;
		}
		MAT_LOG("]\r\n");
	}
	MAT_LOG("}\r\n");
}

//获取一个矩阵的元素
matDAT Get_Mat(matrixStr* mat,u32 line,u32 list)
{
	if(line < mat->line && list < mat->list )
		return *(matDAT*)(&mat->list + 1 + line*mat->list + list);
	else return (matDAT)-1;
}

//获取矩阵元素单元的地址
matDAT* Get_MatAddr(matrixStr* mat,u32 line,u32 list)
{
	if(line < mat->line && list < mat->list )
		return (matDAT*)(&mat->list + 1 + line*mat->list + list);
	else return (matDAT*)-1;
}

//矩阵相加
matrixStr* matAdd(matrixStr* a,matrixStr* b)
{

	if(a->line == b->line && a->list == b->list)
	{
		u32 L = 0;
		u32 H = 0;
		matrixStr* mat = matMalloc(a->line,a->list);

		for(L = 0; L < a->line; L ++)
		{
			for(H = 0; H < a->list; H ++)
			{
				*(matDAT*)(&mat->list + 1 + L*mat->list + H) = Get_Mat(a,L,H) +  Get_Mat(b,L,H);
			}		
		}
		return mat;
	}else ERROR_MAT_LOG("错误：两个矩阵行列数不相等!\r\n");

	return (matrixStr*)-1;
}

//相乘，相加 ,a的第几行跟b的第几列相乘相加
// 返回相乘的结果
matDAT GetMat_MultAdd(matrixStr* a,matrixStr* b,u32 aline,u32 blist)
{
	u32 i = 0;
	matDAT dat = 0;
	for(i=0;i<a->list;i++)
	{	
		dat += (matDAT)Get_Mat(a,aline,i) *  (matDAT)Get_Mat(b,i,blist);
	//	printf("dat = %f\r\n",dat);
	}
	//printf("->dat = %f\r\n",dat);
	return dat;
}

//矩阵相乘
//返回一个乘积结果矩阵
matrixStr* matDot(matrixStr* a,matrixStr* b)
{

	if( a->list == b->line)
	{
		u32 L = 0;
		u32 H = 0;
		matrixStr* mat = matMalloc(a->line,b->list);
		for(L = 0; L < a->line; L ++)
		{
			for(H = 0; H < b->list; H ++)
			{
				*Get_MatAddr(mat,L,H) = GetMat_MultAdd(a,b,L,H);
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
	u32 L = 0;	//行
	u32 H = 0;	//列
	matrixStr* mat_t = matMalloc(mat->list,mat->line);

	for(L = 0; L < mat_t->line; L ++)
	{
		for(H = 0; H < mat_t->list; H ++)
		{
			*Get_MatAddr(mat_t,L,H) = Get_Mat(mat,H,L);
		}
	}
	return mat_t;

}

//生成一个矩阵，并全部赋值成num
matrixStr* matrix_Num(u32 line,u32 list,matDAT num)
{
	u32 L = 0;	//行
	u32 H = 0;	//列
	matrixStr* mat = matMalloc(line,list);
	for(L = 0; L < mat->line; L ++)
	{
		for(H = 0; H < mat->list; H ++)
		{
			*Get_MatAddr(mat,L,H) = num;
		}
	}
	return mat;
}


//生成一个矩阵，并全部赋值成1
matrixStr* matrix_One(u32 line,u32 list)
{
	return matrix_Num(line, list,1);
}

//生成一个矩阵，并全部赋值成0
matrixStr* matrix_Zero(u32 line,u32 list)
{
	return matrix_Num(line, list,0);
}

// 将mat矩阵,添加到source矩阵中，axis = 1添加到右边，axis = 0 添加到下边
matrixStr* matrix_Append(matrixStr* source,matrixStr* bmat,Axis axis)
{
	matrixStr* mat = 0 ;
	u32 L = 0;	//行
	u32 H = 0;	//列
	if(axis == horizontal)	//添加到下边
	{
		if(source->list != bmat->list)
			ERROR_MAT_LOG("错误：axis=0，列数必须相同\r\n");
		else
		{
			mat = matMalloc(source->line + bmat->line,source->list);
			for(L = 0; L < source->line; L ++)			//拷贝源矩阵
			{
				for(H = 0; H < mat->list; H ++)
				{
					*Get_MatAddr(mat,L,H) = Get_Mat(source,L,H);
				}
			}

			for(L = source->line; L < mat->line; L ++)	//拷贝添加的矩阵
			{
				for(H = 0; H < mat->list; H ++)
				{
					*Get_MatAddr(mat,L,H) = Get_Mat(bmat,L - source->line ,H);
				}
			}
		}
	}
	else
	if(axis == vertical)
	{
		if(source->line != bmat->line)
			ERROR_MAT_LOG("错误：axis=1，行数必须相同\r\n");
		else
		{
			mat = matMalloc(source->line,source->list + bmat->list);
			for(H = 0; H < source->list; H ++)			//拷贝源矩阵
			{
				for(L = 0; L < mat->line; L ++)
				{
					*Get_MatAddr(mat,L,H) = Get_Mat(source,L,H);
				}
			}

			for(H = source->list; H < mat->list; H ++)	//拷贝添加的矩阵
			{
				for(L = 0; L < mat->line; L ++)
				{
					*Get_MatAddr(mat,L,H) = Get_Mat(bmat,L,H - source->list);
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
	u32 L = 0;	//行
	u32 H = 0;	//列
	
	if(end >= start)
	{
		if(axis == horizontal)
		{
			if(end > source->line) ERROR_MAT_LOG("ERROR: END 超出范围\r\n");
			else 
			{
				mat = matMalloc(end - start + 1,source->list);
				for(L = start; L <= end; L ++)			//拷贝源矩阵
				{
					for(H = 0; H < mat->list; H ++)
					{
						*Get_MatAddr(mat,L-start,H) = Get_Mat(source,L,H);
					}
				}
			}
		}else
		{
				if(end > source->list) ERROR_MAT_LOG("ERROR: END 超出范围\r\n");
				else 
				{
					mat = matMalloc(source->line,end - start + 1);
					for(H = start; H <= end; H ++)		//拷贝矩阵
					{
						for(L = 0; L < mat->line; L ++)
						{
							*Get_MatAddr(mat,L,H-start) = Get_Mat(source,L,H);
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
	return mat->line * mat->list;
}

//矩阵减法
matrixStr* matSub(matrixStr* a,matrixStr* b)
{

	if(a->line == b->line && a->list == b->list)
	{
		u32 L = 0;
		u32 H = 0;
		matrixStr* mat = matMalloc(a->line,a->list);
		for(L = 0; L < a->line; L ++)
		{
			for(H = 0; H < a->list; H ++)
			{
				*(matDAT*)(&mat->list + 1 + L*mat->list + H) = Get_Mat(a,L,H) -  Get_Mat(b,L,H);
			}		
		}
		return mat;
	}else ERROR_MAT_LOG("错误：两个矩阵行列数不相等!\r\n");

	return (matrixStr*)-1;
}

//矩阵与num的运算
void matAlgorithm(matrixStr* mat,float num,Algorithm alg)
{

		u32 L = 0;	// 行
		u32 H = 0;	// 列
		for(L = 0; L < mat->line; L ++)
		{
			for(H = 0; H < mat->list; H ++)
			{
				if(alg == add)
					*(matDAT*)(&mat->list + 1 + L*mat->list + H) = Get_Mat(mat,L,H) + num;
				else if(alg == sub)
					*(matDAT*)(&mat->list + 1 + L*mat->list + H) = Get_Mat(mat,L,H) - num;
				else if(alg == mul)
					*(matDAT*)(&mat->list + 1 + L*mat->list + H) = Get_Mat(mat,L,H) * num;
				else if(alg == divi)
					*(matDAT*)(&mat->list + 1 + L*mat->list + H) = Get_Mat(mat,L,H) / num;
				
			}		
		}

}


//矩阵与矩阵迭代的运算，不产生新空间，结果覆盖第一个矩阵
void matIteraAlgorithm(matrixStr* a,matrixStr* b,Algorithm alg)
{
	if(a->line == b->line && a->list == b->list)
	{
		u32 L = 0;
		u32 H = 0;

		for(L = 0; L < a->line; L ++)
		{
			for(H = 0; H < a->list; H ++)
			{
				
				if(alg == add)
					*(matDAT*)(&a->list + 1 + L*a->list + H) = Get_Mat(a,L,H) +  Get_Mat(b,L,H);
				else if(alg == sub)
					*(matDAT*)(&a->list + 1 + L*a->list + H) = Get_Mat(a,L,H) -  Get_Mat(b,L,H);
				else ERROR_MAT_LOG("错误：无法执行除加减法的迭代运算!\r\n");
			}		
		}

	}else ERROR_MAT_LOG("错误：两个矩阵行列数不相等!\r\n");

}

//矩阵旋转,radian弧度，顺时针为正
matrixStr* matRote(matrixStr* mat_sorce,float radian)
{
	matrixStr* mat = matMalloc(mat_sorce->line,mat_sorce->list);
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

//矩阵缩放,xtimes，ytimes
matrixStr* matZoom(matrixStr* mat_sorce,float xtimes,float ytimes)
{
	matrixStr* mat = matMalloc(mat_sorce->line,mat_sorce->list);
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




