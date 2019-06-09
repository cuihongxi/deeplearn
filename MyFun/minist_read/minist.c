#include "MINIST.H"
#include "fatfs.h"

u32 GetBigEndDat(u32* buff)
{
	u32 dat = 0;
	u8* p = (u8*)buff;
	dat = p[0]<<24 | p[1]<<16 | p[2]<<8 | p[3];
	return dat;
}


	//从MINIST数据集中第startpic条数据开始，获取num条训练集,和num条结果集
	miniData* MinistGetData(u32 startpic ,u32 num)
	{
		FATFS*	fs = malloc(sizeof(FATFS));	
		FIL*	fdst =  malloc(sizeof(FIL));
		featureStr feaInf = {0};
		miniData* minidata = malloc(sizeof(miniData));
		u32 size_fea = 0;
		u32 bw = 0;		//记录指针位置
		
		u8* buffer = malloc(_MIN_SS);		
		
		f_mount(fs,"0:",1);
		CheckError_Handler(f_open (fdst,FILE_TRAIN_FEATURESET,FA_READ));	//打开特征训练集文件
		CheckError_Handler(f_read(fdst,buffer,_MIN_SS,&bw));							//读一个最小扇区
		feaInf.magicNumber = GetBigEndDat(&(((featureStr*)buffer)->magicNumber))	;
		feaInf.numberImages = GetBigEndDat(&(((featureStr*)buffer)->numberImages))	;
		feaInf.rows =  GetBigEndDat(&(((featureStr*)buffer)->rows))	;
		feaInf.columns =  GetBigEndDat(&(((featureStr*)buffer)->columns))	;
		f_close(fdst);
		
		_free(buffer);		//释放
		
		size_fea = num * feaInf.columns * feaInf.rows;											
		bw = sizeof(featureStr) + startpic * feaInf.columns * feaInf.rows;	//偏移文件指针
		matrixStr* featureMat = matMalloc(num,feaInf.columns * feaInf.rows);//申请保存特征数据矩阵
		CheckError_Handler(f_open (fdst,FILE_TRAIN_FEATURESET,FA_READ));		//打开特征训练集文件		
		CheckError_Handler(f_lseek(fdst,bw));																//偏移文件指针	
		CheckError_Handler(f_read(fdst,(u8*)featureMat + sizeof(matrixStr),size_fea,&bw));								//读num张数据	
		minidata->featureData = featureMat;
		f_close(fdst);
		
		size_fea = num ;																										//label大小										
		bw = sizeof(labelStr) + startpic;																		//偏移文件指针
		matrixStr* labelMat = matMalloc(num,1);															//申请保存结果数据矩阵
		CheckError_Handler(f_open (fdst,FILE_TRAIN_LABELESET,FA_READ));			//打开特征训练集文件		
		CheckError_Handler(f_lseek(fdst,bw));																//偏移文件指针	
		CheckError_Handler(f_read(fdst,(u8*)labelMat + sizeof(matrixStr),size_fea,&bw));								//读num张数据	
		minidata->labelData = labelMat;
		f_close(fdst);
		
		minidata->num = num;
		minidata->columns = feaInf.columns;
		minidata->rows = feaInf.rows;
			
		_free(fs);
		_free(fdst);
		
		return minidata;
	}








