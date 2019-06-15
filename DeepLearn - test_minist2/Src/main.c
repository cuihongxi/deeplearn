
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2019 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx_hal.h"
#include "dma.h"
#include "fatfs.h"
#include "sdio.h"
#include "usart.h"
#include "gpio.h"

/* USER CODE BEGIN Includes */
#include "matrix.h"
#include "numpy.h"
#include "MINIST.H"
#include "GradientDescent.h"

#include "stm32f4xx_hal_uart.h"
#define	BUFNUM 30
u8 pIDLE_Buff[BUFNUM] = {0};
u32 while_i = 0;
numpy np;
matrixStr* weight ;
u8 flag_test = 0;
u32 stardat = 0;
u32 enddat = 0;
extern DMA_HandleTypeDef hdma_usart1_rx;
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  *
  * @retval None
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */



  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_USART1_UART_Init();
  MX_SDIO_SD_Init();
  MX_FATFS_Init();
  /* USER CODE BEGIN 2 */
	printf("\r\nstart:\r\n");
	

	numpy_Init(&np);
	float learnRate = 0.1;//0.001;	
	weight = np.ones(785,10);	//代表10个数的weight
	//weight = np.array(785,10);
	//np.apendData(weight,(matDAT*)weightDat2816);//加载数据
	HAL_UART_Receive_DMA(&huart1,pIDLE_Buff,BUFNUM);
	__HAL_UART_ENABLE_IT(&huart1, UART_IT_IDLE);						// 开启空闲接收中断 
	__HAL_UART_CLEAR_IDLEFLAG(&huart1); 										//清空闲中断

#define	STEP	10
	//训练
	while(1)
	{

		miniData*  mini = MinistGetData((while_i*STEP)%(60000),STEP);		
		printf("%d	",while_i);
		//np.printMat(mini->labelData);
		
		weight = TrainMinist(&np,mini->featureData,mini->labelData,weight,learnRate,100);
		_free((u8*)(mini->featureData));
		_free((u8*)mini->labelData);
		_free(mini);
		
		while_i++;
		if(flag_test==1)
		{
				flag_test = 0;
				miniData*  mini = MinistGetTestData(stardat,enddat%15);	
			//	printf("-----测试集数据：---------\r\n");
			//	np.printMat(mini->labelData);
				
				matrixStr* test = Test(np.sigmoid,mini->featureData,weight);
			printf("---------------------------start: %d----------------------------\r\n\r\n",stardat);
			for(u8 i=0;i<enddat%15;i++)
			{
				if(Get_Mat(mini->labelData,i,0) != (float)GetListMax(test,i))printf("!error		");
				else printf("ok		");
				printf("[%d]真实值为: %d	测试值为: %d	概率为 %.2f\r\n\r\n",\
				stardat+i,(u8)Get_Mat(mini->labelData,i,0),GetListMax(test,i),Get_Mat(test,i,GetListMax(test,i)));
				
			}
			printf("---------------------------end: %d------------------------------\r\n\r\n",enddat%15);
				_free((u8*)(mini->featureData));
				_free((u8*)mini->labelData);
				_free(mini);
				_free(test);
		}
		if(flag_test == 100)	//测试所有测试集
		{
				flag_test = 0;
				u16 erro_time = 0;
				miniData*  mini = MinistGetTestData(0,1);	
				u16	num = 10000;				
			for(u16 i =0;i<num;i+=10)
			{
				miniData*  mini = MinistGetTestData(i,10);	
				//printf("-----测试集数据：---------\r\n");
				//np.printMat(mini->labelData);
				
				matrixStr* test = Test(np.sigmoid,mini->featureData,weight);
				for(u8 i = 0;i< mini->labelData->rows;i++)
				{
					if(Get_Mat(mini->labelData,i,0) != (float)GetListMax(test,i))
					{
						erro_time ++;
						
					}
				}
				if(i%100 == 0)printf("已经测试%d条\r\n",i+100);
				_free((u8*)(mini->featureData));
				_free((u8*)mini->labelData);
				_free(mini);
				_free(test);			
			}
			printf("测试完成:\r\n	失败数：%d,\r\n	测试量：%d,\r\n	成功率：%.2f\r\n",erro_time,num,(float)(num -erro_time)/num);
		}
	}


	

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */

  }
  /* USER CODE END 3 */

}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Configure the main internal regulator output voltage 
    */
  __HAL_RCC_PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 15;
  RCC_OscInitStruct.PLL.PLLN = 216;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 8;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Activate the Over-Drive mode 
    */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USER CODE BEGIN 4 */

//比较两个字符串，相同则返回指针,不同则返回0
u32 compareStr(u8* str1,u8* str2)
{
	u8 i =0;
	while(str1[i])
	{
		if(str1[i]^str2[i]) //不同
			return 0;
		i++;
	}
	return (u32)&str2[i];
}

//获取一个字符串中的数字,lastAdd保存移动到的地址
u32 GetStrNum(u8* str,u32* lastAdd)
{
	u8 i = 0;
	u32 dat = 0;
	while(str[i] != ',' && str[i] != '\r')
	{
			while(str[i]==' ')i++;
		dat = dat*10 + str[i] - '0';
		i++;
	}
	*lastAdd = (u32)&str[i+1];
	return dat;
}

/************************************************************************************
*-函数名称	：DMA串口接收函数
*-参数			：huart 串口句柄, hdma_usart_rx DMA 串口句柄
*-返回值		：
*-备注			：
*-创建者		：蓬莱市博硕电子科技
*/


void MD_DMAInUART_IDLE()
{
		uint16_t i = 0; 		

		i = hdma_usart1_rx.Instance->NDTR;
	//	printf("i = %d\r\n",i);
		__HAL_UART_CLEAR_IDLEFLAG(&huart1);
		if(i <= BUFNUM)
		{
			 
			HAL_DMA_Abort(&hdma_usart1_rx);
			hdma_usart1_rx.Instance->NDTR = BUFNUM;//这个寄存器只能在通道不工作(DMA_CCRx的EN=0)时写入  
			pIDLE_Buff[BUFNUM - i] = 0;
			printf("\r\n%s\r\n",pIDLE_Buff);
			if(compareStr((u8*)"weight",pIDLE_Buff))
			{
				printf("\r\n--------weight %d------\r\n",while_i);
				np.printMat(weight);
			}
			
			if(compareStr((u8*)"label",pIDLE_Buff))	//校验
			{
					u32 staraddr = compareStr((u8*)"label",pIDLE_Buff);
					u32 lastAdd =0;
					stardat =  GetStrNum((u8*)staraddr,&lastAdd);
					enddat = GetStrNum((u8*)lastAdd,&staraddr);
					flag_test = 1;
				
			}	
			if(compareStr((u8*)"test all",pIDLE_Buff))	//校验
			{
					flag_test = 100;
				
			}	
			
		}
		
				
		
		HAL_UART_Receive_DMA(&huart1,pIDLE_Buff,BUFNUM);		

		//np.printMat(weight);

				
}


/* 串口接收空闲中断 */ 
void UsartReceive_IDLE(UART_HandleTypeDef *huart) 
	{ 
		
		if(huart == &huart1)
		{			
			MD_DMAInUART_IDLE();
		}	
	} 
	
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
	printf("_Error_Handler FILE :%s ,line : %d\r\n",file,line);
  while(1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
