#ifndef __FT5206_H
#define __FT5206_H	
#ifdef __cplusplus
 extern "C" {
#endif
/**********************************************************************/
#include "main.h"
#include "stdbool.h"
/**********************************************************************/     
     
//����ݴ��������ӵ�оƬ����(δ����IIC����) 
//IO��������	  
#define FT_RST(x)				GPIO_Pin_Set(GPIOI,PIN8,x)		//FT5206��λ����
#define FT_INT					GPIO_Pin_Get(GPIOH,PIN7) 		//FT5206������	
   
//I2C��д����	
#define FT_CMD_WR 				0X70    	//д����
#define FT_CMD_RD 				0X71		//������
  
//FT5206 ���ּĴ������� 
#define FT_DEVIDE_MODE 			0x00   		//FT5206ģʽ���ƼĴ���
#define FT_REG_NUM_FINGER       0x02		//����״̬�Ĵ���

#define FT_TP1_REG 				0X03	  	//��һ�����������ݵ�ַ
#define FT_TP2_REG 				0X09		//�ڶ������������ݵ�ַ
#define FT_TP3_REG 				0X0F		//���������������ݵ�ַ
#define FT_TP4_REG 				0X15		//���ĸ����������ݵ�ַ
#define FT_TP5_REG 				0X1B		//��������������ݵ�ַ  
 

#define	FT_ID_G_LIB_VERSION		0xA1		//�汾		
#define FT_ID_G_MODE 			0xA4   		//FT5206�ж�ģʽ���ƼĴ���
#define FT_ID_G_THGROUP			0x80   		//������Чֵ���üĴ���
#define FT_ID_G_PERIODACTIVE	0x88   		//����״̬�������üĴ���


uint8_t FT5206_WR_Reg(uint16_t reg,uint8_t *buf,uint8_t len);
uint8_t FT5206_RD_Reg(uint16_t reg,uint8_t *buf,uint8_t len);
uint8_t FT5206_Init(void);
uint8_t FT5206_Scan(uint8_t mode);
bool FT5X06_Readpoint(uint16_t *_x_position,uint16_t *_y_position);


#ifdef __cplusplus
}
#endif


#endif





