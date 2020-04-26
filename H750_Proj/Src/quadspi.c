/**
  ******************************************************************************
  * File Name          : QUADSPI.c
  * Description        : This file provides code for the configuration
  *                      of the QUADSPI instances.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "quadspi.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

QSPI_HandleTypeDef hqspi;

/* QUADSPI init function */
void MX_QUADSPI_Init(void)
{

  hqspi.Instance = QUADSPI;
  hqspi.Init.ClockPrescaler = 2;
  hqspi.Init.FifoThreshold = 8;
  hqspi.Init.SampleShifting = QSPI_SAMPLE_SHIFTING_NONE;
  hqspi.Init.FlashSize = 25;
  hqspi.Init.ChipSelectHighTime = QSPI_CS_HIGH_TIME_4_CYCLE;
  hqspi.Init.ClockMode = QSPI_CLOCK_MODE_0;
  hqspi.Init.DualFlash = QSPI_DUALFLASH_ENABLE;
  if (HAL_QSPI_Init(&hqspi) != HAL_OK)
  {
    Error_Handler();
  }

}

void HAL_QSPI_MspInit(QSPI_HandleTypeDef* qspiHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(qspiHandle->Instance==QUADSPI)
  {
  /* USER CODE BEGIN QUADSPI_MspInit 0 */

  /* USER CODE END QUADSPI_MspInit 0 */
    /* QUADSPI clock enable */
    __HAL_RCC_QSPI_CLK_ENABLE();
  
    __HAL_RCC_GPIOG_CLK_ENABLE();
    __HAL_RCC_GPIOF_CLK_ENABLE();
    __HAL_RCC_GPIOH_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**QUADSPI GPIO Configuration    
    PG9     ------> QUADSPI_BK2_IO2
    PG14     ------> QUADSPI_BK2_IO3
    PG6     ------> QUADSPI_BK1_NCS
    PF6     ------> QUADSPI_BK1_IO3
    PF7     ------> QUADSPI_BK1_IO2
    PF8     ------> QUADSPI_BK1_IO0
    PF9     ------> QUADSPI_BK1_IO1
    PH2     ------> QUADSPI_BK2_IO0
    PH3     ------> QUADSPI_BK2_IO1
    PB2     ------> QUADSPI_CLK 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_14;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_QUADSPI;
    HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF10_QUADSPI;
    HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_QUADSPI;
    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF10_QUADSPI;
    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_QUADSPI;
    HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_2;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_QUADSPI;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* QUADSPI interrupt Init */
    HAL_NVIC_SetPriority(QUADSPI_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(QUADSPI_IRQn);
  /* USER CODE BEGIN QUADSPI_MspInit 1 */

  /* USER CODE END QUADSPI_MspInit 1 */
  }
}

void HAL_QSPI_MspDeInit(QSPI_HandleTypeDef* qspiHandle)
{

  if(qspiHandle->Instance==QUADSPI)
  {
  /* USER CODE BEGIN QUADSPI_MspDeInit 0 */

  /* USER CODE END QUADSPI_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_QSPI_CLK_DISABLE();
  
    /**QUADSPI GPIO Configuration    
    PG9     ------> QUADSPI_BK2_IO2
    PG14     ------> QUADSPI_BK2_IO3
    PG6     ------> QUADSPI_BK1_NCS
    PF6     ------> QUADSPI_BK1_IO3
    PF7     ------> QUADSPI_BK1_IO2
    PF8     ------> QUADSPI_BK1_IO0
    PF9     ------> QUADSPI_BK1_IO1
    PH2     ------> QUADSPI_BK2_IO0
    PH3     ------> QUADSPI_BK2_IO1
    PB2     ------> QUADSPI_CLK 
    */
    HAL_GPIO_DeInit(GPIOG, GPIO_PIN_9|GPIO_PIN_14|GPIO_PIN_6);

    HAL_GPIO_DeInit(GPIOF, GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9);

    HAL_GPIO_DeInit(GPIOH, GPIO_PIN_2|GPIO_PIN_3);

    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_2);

    /* QUADSPI interrupt Deinit */
    HAL_NVIC_DisableIRQ(QUADSPI_IRQn);
  /* USER CODE BEGIN QUADSPI_MspDeInit 1 */

  /* USER CODE END QUADSPI_MspDeInit 1 */
  }
} 

/* USER CODE BEGIN 1 */
#define W25QXX_ENTER_QSPI()        QSPI_SendCmd(W25X_EnterQPIMode,QSPI_INSTRUCTION_1_LINE,0,0,0,0)
#define W25QXX_ENTER_4BYTEADDR()   QSPI_SendCmd(W25X_Enable4ByteAddr,QSPI_INSTRUCTION_4_LINES,0,0,0,0)
#define W25Q_WRITE_ENABLE()      QSPI_SendCmd(W25X_WriteEnable,QSPI_INSTRUCTION_4_LINES,0,0,0,0)

void QSPI_SendCmd(uint32_t cmd,uint32_t cmdMode,uint32_t addr,uint32_t addrMode,uint32_t addrSize,uint32_t dataMode)
{
    QSPI_CommandTypeDef s_command = {0};
    
    s_command.Instruction     = cmd;          //指令
    s_command.InstructionMode = cmdMode;	  //指令模式
    s_command.Address         = addr;         //地址
    s_command.AddressMode     = addrMode;     //地址模式
    s_command.AddressSize     = addrSize;     //地址长度
    s_command.DataMode        = dataMode;     //数据模式
    
    if (HAL_QSPI_Command(&hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        Error_Handler();
    }
}
void QSPI_Receive(uint8_t* buf,uint32_t len)
{
    hqspi.Instance->DLR = len - 1;                 //配置数据长度
    if(HAL_QSPI_Receive(&hqspi, buf, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        Error_Handler();
    }
}
 
uint8_t QSPI_Transmit(uint8_t* buf,uint32_t len)
{
    hqspi.Instance->DLR = len - 1;                            //配置数据长度
    if(HAL_QSPI_Transmit(&hqspi, buf, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        Error_Handler();
    }
}


//void W25QXX_SetQE(void)
//{
//    uint8_t value = 0x02;
//    /* 1.写使能 */
//    QSPI_SendCmd(W25X_WriteEnable,QSPI_INSTRUCTION_1_LINE,0,0,0,0);
//    /* 2.发送写状态寄存器2命令 */
//    QSPI_SendCmd(W25X_WriteStatusReg2,QSPI_INSTRUCTION_1_LINE,0,0,0,QSPI_DATA_1_LINE);
//    /* 3.发送数据 */
//    QSPI_Transmit(&value, 1);
//}
//void W25QXX_SetReadParam(void)
//{
//    uint8_t para = 3 << 4;
//    
//    /* 1.发送命令 */
//    QSPI_SendCmd(W25X_SetReadParam,QSPI_INSTRUCTION_4_LINES,0,0,0,QSPI_DATA_4_LINES);
//    /* 2.发送数据 */
//    QSPI_Transmit(&para, 1);
//}
//uint16_t W25QXX_ReadId(void)
//{
//    QSPI_CommandTypeDef s_command = {0};
//    
//    uint8_t pData[2];
// 
//    QSPI_SendCmd(W25X_ManufactDeviceID,QSPI_INSTRUCTION_4_LINES,
//                 0,QSPI_ADDRESS_4_LINES,QSPI_ADDRESS_24_BITS,QSPI_DATA_4_LINES);
//    QSPI_Receive(pData,2);
// 
//    return pData[1] | ( pData[0] << 8 );
//}
//void W25QXX_Init(void)
//{
//    uint16_t W25_ID = 0;
//    W25QXX_SetQE();
//    HAL_Delay(20);
//    W25QXX_ENTER_QSPI();
//    W25QXX_ENTER_4BYTEADDR();
//    W25QXX_SetParam();//设置读参数
//    W25_ID = W25QXX_ReadId();
//}



/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
