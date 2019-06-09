#include "matrix.h"
#include "math.h"


// ����һ������
matrixStr* matMalloc(u32 line,u32 list)
{
	//��̬����һƬ�ڴ棬��������������������������
	matrixStr* mat = (matrixStr*)malloc((line*list+2)*(sizeof(matDAT)/sizeof(u8)));
	if(mat == 0) 
	{
		ERROR_MAT_LOG("ERROR:��̬�ڴ�����ʧ��\r\n");
		return 0;
	}else
	{
		mat->line = line;
		mat->list = list;
		return mat;	
	}
}

//�������&mat->list + 1
void matApendDat(matrixStr* mat , matDAT* dat)
{
	u32 L = 0;	//��
	u32 H = 0;	//��

	for(L = 0; L < mat->line; L ++)
	{
		for(H = 0; H < mat->list; H ++)
		{
			*(matDAT*)(mat+sizeof(matrixStr) + L*mat->list + H) = *dat;
			dat ++;
		}
		
	}
}



//��ӡһ������
void PrintMat(matrixStr* mat)
{
	u32 L = 0;	//��
	u32 H = 0;	//��
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

//��ȡһ�������Ԫ��
matDAT Get_Mat(matrixStr* mat,u32 line,u32 list)
{
	if(line < mat->line && list < mat->list )
		return *(matDAT*)(&mat->list + 1 + line*mat->list + list);
	else return (matDAT)-1;
}

//��ȡ����Ԫ�ص�Ԫ�ĵ�ַ
matDAT* Get_MatAddr(matrixStr* mat,u32 line,u32 list)
{
	if(line < mat->line && list < mat->list )
		return (matDAT*)(&mat->list + 1 + line*mat->list + list);
	else return (matDAT*)-1;
}

//�������
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
	}else ERROR_MAT_LOG("�����������������������!\r\n");

	return (matrixStr*)-1;
}

//��ˣ���� ,a�ĵڼ��и�b�ĵڼ���������
// ������˵Ľ��
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

//�������
//����һ���˻��������
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
	}else ERROR_MAT_LOG("����A��������B����������ȣ��������˷�\r\n");
	return (matrixStr*)-1;
}

//���ؾ����ת��
//ע�⣬���������Ҫ��Ҫ�ͷ��ڴ�
matrixStr* matrix_T(matrixStr* mat)
{
	u32 L = 0;	//��
	u32 H = 0;	//��
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

//����һ�����󣬲�ȫ����ֵ��num
matrixStr* matrix_Num(u32 line,u32 list,matDAT num)
{
	u32 L = 0;	//��
	u32 H = 0;	//��
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


//����һ�����󣬲�ȫ����ֵ��1
matrixStr* matrix_One(u32 line,u32 list)
{
	return matrix_Num(line, list,1);
}

//����һ�����󣬲�ȫ����ֵ��0
matrixStr* matrix_Zero(u32 line,u32 list)
{
	return matrix_Num(line, list,0);
}

// ��mat����,��ӵ�source�����У�axis = 1��ӵ��ұߣ�axis = 0 ��ӵ��±�
matrixStr* matrix_Append(matrixStr* source,matrixStr* bmat,Axis axis)
{
	matrixStr* mat = 0 ;
	u32 L = 0;	//��
	u32 H = 0;	//��
	if(axis == horizontal)	//��ӵ��±�
	{
		if(source->list != bmat->list)
			ERROR_MAT_LOG("����axis=0������������ͬ\r\n");
		else
		{
			mat = matMalloc(source->line + bmat->line,source->list);
			for(L = 0; L < source->line; L ++)			//����Դ����
			{
				for(H = 0; H < mat->list; H ++)
				{
					*Get_MatAddr(mat,L,H) = Get_Mat(source,L,H);
				}
			}

			for(L = source->line; L < mat->line; L ++)	//������ӵľ���
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
			ERROR_MAT_LOG("����axis=1������������ͬ\r\n");
		else
		{
			mat = matMalloc(source->line,source->list + bmat->list);
			for(H = 0; H < source->list; H ++)			//����Դ����
			{
				for(L = 0; L < mat->line; L ++)
				{
					*Get_MatAddr(mat,L,H) = Get_Mat(source,L,H);
				}
			}

			for(H = source->list; H < mat->list; H ++)	//������ӵľ���
			{
				for(L = 0; L < mat->line; L ++)
				{
					*Get_MatAddr(mat,L,H) = Get_Mat(bmat,L,H - source->list);
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
	u32 L = 0;	//��
	u32 H = 0;	//��
	
	if(end >= start)
	{
		if(axis == horizontal)
		{
			if(end > source->line) ERROR_MAT_LOG("ERROR: END ������Χ\r\n");
			else 
			{
				mat = matMalloc(end - start + 1,source->list);
				for(L = start; L <= end; L ++)			//����Դ����
				{
					for(H = 0; H < mat->list; H ++)
					{
						*Get_MatAddr(mat,L-start,H) = Get_Mat(source,L,H);
					}
				}
			}
		}else
		{
				if(end > source->list) ERROR_MAT_LOG("ERROR: END ������Χ\r\n");
				else 
				{
					mat = matMalloc(source->line,end - start + 1);
					for(H = start; H <= end; H ++)		//��������
					{
						for(L = 0; L < mat->line; L ++)
						{
							*Get_MatAddr(mat,L,H-start) = Get_Mat(source,L,H);
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
	return mat->line * mat->list;
}

//�������
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
	}else ERROR_MAT_LOG("�����������������������!\r\n");

	return (matrixStr*)-1;
}

//������num������
void matAlgorithm(matrixStr* mat,float num,Algorithm alg)
{

		u32 L = 0;	// ��
		u32 H = 0;	// ��
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


//�����������������㣬�������¿ռ䣬������ǵ�һ������
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
				else ERROR_MAT_LOG("�����޷�ִ�г��Ӽ����ĵ�������!\r\n");
			}		
		}

	}else ERROR_MAT_LOG("�����������������������!\r\n");

}

//������ת,radian���ȣ�˳ʱ��Ϊ��
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

//��������,xtimes��ytimes
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




