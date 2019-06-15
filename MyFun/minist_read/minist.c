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
		CheckError_MALLOC(fs); 
		FIL*	fdst =  malloc(sizeof(FIL));
		CheckError_MALLOC(fdst); 
		featureStr feaInf = {0};
		miniData* minidata = malloc(sizeof(miniData));
		CheckError_MALLOC(minidata); 
		u32 size_fea = 0;
		u32 bw = 0;		//��¼ָ��λ��
		u8* buffer = malloc(_MIN_SS);		
		CheckError_MALLOC(buffer);	
		
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
		u8* featureBuf = malloc(size_fea);//���뱣���������ݻ���
		if(featureBuf == 0) ERROR_MAT_LOG("���뱣���������ݻ���ʧ��\r\nfile :%s  rows :%d\r\n",__FILE__, __LINE__);

		CheckError_Handler(f_open (fdst,FILE_TRAIN_FEATURESET,FA_READ));		//������ѵ�����ļ�		
		CheckError_Handler(f_lseek(fdst,bw));																//ƫ���ļ�ָ��	
		CheckError_Handler(f_read(fdst,featureBuf,size_fea,&bw));								//��num������			
		matApendDatU8(featureMat,featureBuf);//����������
		minidata->featureData = featureMat;
		f_close(fdst);
		_free(featureBuf);
		size_fea = num ;																										//label��С										
		bw = sizeof(labelStr) + startpic;																		//ƫ���ļ�ָ��
		matrixStr* labelMat = matMalloc(num,1);															//���뱣�������ݾ���
		u8* labelBuf = malloc(size_fea);																		//���뱣�������ݻ���
		if(labelBuf == 0) ERROR_MAT_LOG("���뱣�������ݻ���ʧ��\r\nfile :%s  rows :%d\r\n",__FILE__, __LINE__);

		CheckError_Handler(f_open (fdst,FILE_TRAIN_LABELESET,FA_READ));			//������ѵ�����ļ�		
		CheckError_Handler(f_lseek(fdst,bw));																//ƫ���ļ�ָ��	
		CheckError_Handler(f_read(fdst,labelBuf,size_fea,&bw));							//��num������	
		matApendDatU8(labelMat,labelBuf);																		//����������
		minidata->labelData = labelMat;
		f_close(fdst);
		_free(labelBuf);
		
		minidata->num = num;
		minidata->columns = feaInf.columns;
		minidata->rows = feaInf.rows;

		_free(fs);
		_free(fdst);
		
		return minidata;
}

	//��MINIST�������ݼ��е�startpic�����ݿ�ʼ����ȡnum��ѵ����,��num�������
miniData* MinistGetTestData(u32 startpic ,u32 num)
{
		FATFS*	fs = malloc(sizeof(FATFS));
		CheckError_MALLOC(fs); 
		FIL*	fdst =  malloc(sizeof(FIL));
		CheckError_MALLOC(fdst); 
		featureStr feaInf = {0};
		miniData* minidata = malloc(sizeof(miniData));
		CheckError_MALLOC(minidata); 
		u32 size_fea = 0;
		u32 bw = 0;		//��¼ָ��λ��
		u8* buffer = malloc(_MIN_SS);		
		CheckError_MALLOC(buffer);	
		
		f_mount(fs,"0:",1);		
		CheckError_Handler(f_open (fdst,FILE_TEST_FEATURESET,FA_READ));	//���������Լ��ļ�	
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
		u8* featureBuf = malloc(size_fea);//���뱣���������ݻ���
		if(featureBuf == 0) ERROR_MAT_LOG("���뱣���������ݻ���ʧ��\r\nfile :%s  rows :%d\r\n",__FILE__, __LINE__);

		CheckError_Handler(f_open (fdst,FILE_TEST_FEATURESET,FA_READ));		//���������Լ��ļ�		
		CheckError_Handler(f_lseek(fdst,bw));																//ƫ���ļ�ָ��	
		CheckError_Handler(f_read(fdst,featureBuf,size_fea,&bw));								//��num������			
		matApendDatU8(featureMat,featureBuf);//����������
		minidata->featureData = featureMat;
		f_close(fdst);
		_free(featureBuf);
		size_fea = num ;																										//label��С										
		bw = sizeof(labelStr) + startpic;																		//ƫ���ļ�ָ��
		matrixStr* labelMat = matMalloc(num,1);															//���뱣�������ݾ���
		u8* labelBuf = malloc(size_fea);																		//���뱣�������ݻ���
		if(labelBuf == 0) ERROR_MAT_LOG("���뱣�������ݻ���ʧ��\r\nfile :%s  rows :%d\r\n",__FILE__, __LINE__);

		CheckError_Handler(f_open (fdst,FILE_TEST_LABELSET,FA_READ));			//�򿪲��Լǹ����ļ�		
		CheckError_Handler(f_lseek(fdst,bw));																//ƫ���ļ�ָ��	
		CheckError_Handler(f_read(fdst,labelBuf,size_fea,&bw));							//��num������	
		matApendDatU8(labelMat,labelBuf);																		//����������
		minidata->labelData = labelMat;
		f_close(fdst);
		_free(labelBuf);
		
		minidata->num = num;
		minidata->columns = feaInf.columns;
		minidata->rows = feaInf.rows;

		_free(fs);
		_free(fdst);
		
		return minidata;
}


////����weight����
//void SaveWeight(matrixStr* weightDat,const char*  fileName)
//{
//		FATFS*	fs = malloc(sizeof(FATFS));	
//		FIL*	fdst =  malloc(sizeof(FIL));
//		UINT bw = 0;
//		f_mount(fs,"0:",1);
//		CheckError_Handler(f_open (fdst,fileName,FA_WRITE|FA_OPEN_ALWAYS));	//���ļ�
//		CheckError_Handler(f_write(fdst,(u8*)weightDat+sizeof(matrixStr),weightDat->rows*weightDat->columns,&bw));	//д������
//		f_close(fdst);			
//		_free(fs);
//		_free(fdst);
//}




