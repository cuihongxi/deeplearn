#include "MINIST.H"
#include "fatfs.h"

u32 GetBigEndDat(u32* buff)
{
	u32 dat = 0;
	u8* p = (u8*)buff;
	dat = p[0]<<24 | p[1]<<16 | p[2]<<8 | p[3];
	return dat;
}


	//��MINIST���ݼ��е�startpic�����ݿ�ʼ����ȡnum��ѵ����,��num�������
	miniData* MinistGetData(u32 startpic ,u32 num)
	{
		FATFS*	fs = malloc(sizeof(FATFS));	
		FIL*	fdst =  malloc(sizeof(FIL));
		featureStr feaInf = {0};
		miniData* minidata = malloc(sizeof(miniData));
		u32 size_fea = 0;
		u32 bw = 0;		//��¼ָ��λ��
		
		u8* buffer = malloc(_MIN_SS);		
		
		f_mount(fs,"0:",1);
		CheckError_Handler(f_open (fdst,FILE_TRAIN_FEATURESET,FA_READ));	//������ѵ�����ļ�
		CheckError_Handler(f_read(fdst,buffer,_MIN_SS,&bw));							//��һ����С����
		feaInf.magicNumber = GetBigEndDat(&(((featureStr*)buffer)->magicNumber))	;
		feaInf.numberImages = GetBigEndDat(&(((featureStr*)buffer)->numberImages))	;
		feaInf.rows =  GetBigEndDat(&(((featureStr*)buffer)->rows))	;
		feaInf.columns =  GetBigEndDat(&(((featureStr*)buffer)->columns))	;
		f_close(fdst);
		
		_free(buffer);		//�ͷ�
		
		size_fea = num * feaInf.columns * feaInf.rows;											
		bw = sizeof(featureStr) + startpic * feaInf.columns * feaInf.rows;	//ƫ���ļ�ָ��
		matrixStr* featureMat = matMalloc(num,feaInf.columns * feaInf.rows);//���뱣���������ݾ���
		CheckError_Handler(f_open (fdst,FILE_TRAIN_FEATURESET,FA_READ));		//������ѵ�����ļ�		
		CheckError_Handler(f_lseek(fdst,bw));																//ƫ���ļ�ָ��	
		CheckError_Handler(f_read(fdst,(u8*)featureMat + sizeof(matrixStr),size_fea,&bw));								//��num������	
		minidata->featureData = featureMat;
		f_close(fdst);
		
		size_fea = num ;																										//label��С										
		bw = sizeof(labelStr) + startpic;																		//ƫ���ļ�ָ��
		matrixStr* labelMat = matMalloc(num,1);															//���뱣�������ݾ���
		CheckError_Handler(f_open (fdst,FILE_TRAIN_LABELESET,FA_READ));			//������ѵ�����ļ�		
		CheckError_Handler(f_lseek(fdst,bw));																//ƫ���ļ�ָ��	
		CheckError_Handler(f_read(fdst,(u8*)labelMat + sizeof(matrixStr),size_fea,&bw));								//��num������	
		minidata->labelData = labelMat;
		f_close(fdst);
		
		minidata->num = num;
		minidata->columns = feaInf.columns;
		minidata->rows = feaInf.rows;
			
		_free(fs);
		_free(fdst);
		
		return minidata;
	}







