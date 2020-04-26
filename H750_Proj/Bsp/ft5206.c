#include "ft5206.h"
#include "i2c.h"


 
//��FT5206д��һ������
//reg:��ʼ�Ĵ�����ַ
//buf:���ݻ�������
//len:д���ݳ���
//����ֵ:0,�ɹ�;1,ʧ��.
uint8_t FT5206_WR_Reg(uint16_t reg,uint8_t *buf,uint8_t len)
{
	uint8_t ret=0;
    
    if(HAL_I2C_Mem_Write(&hi2c2,FT_CMD_WR,reg,I2C_MEMADD_SIZE_16BIT,buf,len,100) != HAL_OK)
    {
        ret = 1;
    }
	return ret; 
}
//��FT5206����һ������
//reg:��ʼ�Ĵ�����ַ
//buf:���ݻ�������
//len:�����ݳ���			  
uint8_t FT5206_RD_Reg(uint16_t reg,uint8_t *buf,uint8_t len)
{
 	
    if(HAL_I2C_Mem_Read(&hi2c2,FT_CMD_WR,reg,I2C_MEMADD_SIZE_16BIT,buf,len,100) != HAL_OK)
    {
        return 1;
    }
    return 0;
} 
//��ʼ��FT5206������
//����ֵ:0,��ʼ���ɹ�;1,��ʼ��ʧ�� 
uint8_t FT5206_Init(void)
{
	uint8_t temp[2]; 
	
	temp[0]=0;
	FT5206_WR_Reg(FT_DEVIDE_MODE,temp,1);	//������������ģʽ 
	FT5206_WR_Reg(FT_ID_G_MODE,temp,1);		//��ѯģʽ 
	temp[0]=22;								//������Чֵ��22��ԽСԽ����	
	FT5206_WR_Reg(FT_ID_G_THGROUP,temp,1);	//���ô�����Чֵ
	temp[0]=12;								//�������ڣ�����С��12�����14
	FT5206_WR_Reg(FT_ID_G_PERIODACTIVE,temp,1); 
	//��ȡ�汾�ţ��ο�ֵ��0x3003
	FT5206_RD_Reg(FT_ID_G_LIB_VERSION,&temp[0],2);  
	if((temp[0]==0X30&&temp[1]==0X03)||temp[1]==0X01||temp[1]==0X02)//�汾:0X3003/0X0001/0X0002
	{
		//printf("CTP ID:%x\r\n",((u16)temp[0]<<8)+temp[1]);
		return 0;
	}  
	return 1;
}
const uint16_t FT5206_TPX_TBL[5]={FT_TP1_REG,FT_TP2_REG,FT_TP3_REG,FT_TP4_REG,FT_TP5_REG};




/**************************************************************
������ȡһ�������㺯�� touchgfx ����
***********************************************************/
bool FT5X06_Readpoint(uint16_t *_x_position,uint16_t *_y_position)
{
    uint8_t res = 0;
    uint8_t buf[7] = {0};
    
    res = FT5206_RD_Reg(0x00,buf,7);
    if( res != 0 )
    {
        return false;
    }
    if( buf[2] != 1 )
    {
        return false;
    }
    
    *_x_position = buf[3] &0x0F;
    *_y_position = buf[5] &0x0F;
    
    *_x_position = (*_x_position << 8) | buf[4];
    *_y_position = (*_y_position << 8) | buf[6];
    return true;
}



//ɨ�败����(���ò�ѯ��ʽ)
//mode:0,����ɨ��.
//����ֵ:��ǰ����״̬.
//0,�����޴���;1,�����д���
uint8_t FT5206_Scan(uint8_t mode)
{/*
	uint8_t buf[4];
	uint8_t i=0;
	uint8_t res=0;
	uint16_t temp;
	static uint8_t t=0;//���Ʋ�ѯ���,�Ӷ�����CPUռ����   
	t++;
	if((t%10)==0||t<10)//����ʱ,ÿ����10��CTP_Scan�����ż��1��,�Ӷ���ʡCPUʹ����
	{
		FT5206_RD_Reg(FT_REG_NUM_FINGER,&mode,1);//��ȡ�������״̬  
		if((mode&0XF)&&((mode&0XF)<6))
		{
			temp=0XFFFF<<(mode&0XF);//����ĸ���ת��Ϊ1��λ��,ƥ��tp_dev.sta���� 
			tp_dev.sta=(~temp)|TP_PRES_DOWN|TP_CATH_PRES; 
			for(i=0;i<5;i++)
			{
				if(tp_dev.sta&(1<<i))		//������Ч?
				{
					FT5206_RD_Reg(FT5206_TPX_TBL[i],buf,4);	//��ȡXY����ֵ 
					if(tp_dev.touchtype&0X01)//����
					{
						tp_dev.y[i]=((u16)(buf[0]&0X0F)<<8)+buf[1];
						tp_dev.x[i]=((u16)(buf[2]&0X0F)<<8)+buf[3];
					}else
					{
						tp_dev.x[i]=lcddev.width-(((u16)(buf[0]&0X0F)<<8)+buf[1]);
						tp_dev.y[i]=((u16)(buf[2]&0X0F)<<8)+buf[3];
					}  
					if((buf[0]&0XF0)!=0X80)tp_dev.x[i]=tp_dev.y[i]=0;//������contact�¼�������Ϊ��Ч
					//printf("x[%d]:%d,y[%d]:%d\r\n",i,tp_dev.x[i],i,tp_dev.y[i]);
				}			
			} 
			res=1;
			if(tp_dev.x[0]==0 && tp_dev.y[0]==0)mode=0;	//���������ݶ���0,����Դ˴�����
			t=0;		//����һ��,��������������10��,�Ӷ����������
		}
	}
	if((mode&0X1F)==0)//�޴����㰴��
	{ 
		if(tp_dev.sta&TP_PRES_DOWN)		//֮ǰ�Ǳ����µ�
		{
			tp_dev.sta&=~TP_PRES_DOWN;	//��ǰ����ɿ�
		}else							//֮ǰ��û�б�����
		{ 
			tp_dev.x[0]=0xffff;
			tp_dev.y[0]=0xffff;
			tp_dev.sta&=0XE000;			//�������Ч���	
		}	 
	} 	
	if(t>240)t=10;//���´�10��ʼ����
	return res;
    */
    return 1;
}
 



























