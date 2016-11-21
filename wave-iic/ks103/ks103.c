#ifndef _C_KS103_
#define _C_KS103_
#include "all.h"
/*ģ��iicͨ��*/
u8 KS103_ReadOneByte(u8 address, u8 reg)
{
  u8 temp=0;
	
	IIC_Start_2();
	IIC_Send_Byte_2(address);            //���͵͵�ַ
	IIC_Wait_Ack_2();
	IIC_Send_Byte_2(reg);                //���͸ߵ�ַ
	IIC_Wait_Ack_2();
	IIC_Start_2();
	IIC_Send_Byte_2(address+1);          //�������ģʽ
	IIC_Wait_Ack_2();
	
	delay_us(200);
	temp=IIC_Read_Byte_2(0);    
	IIC_Stop_2();                        //����һ��ֹͣ����
	return temp;
}

void KS103_WriteOneByte(u8 address,u8 reg,u8 command)
{
  IIC_Start_2();
	IIC_Send_Byte_2(address);
	while(IIC_Wait_Ack_2());
	IIC_Send_Byte_2(reg);               //���͸ߵ�ַ
	IIC_Wait_Ack_2();
	IIC_Send_Byte_2(command);
	IIC_Wait_Ack_2();
	IIC_Stop_2();              
}

//u16 Wave_test(void)
//{
//	  static u16 range=0;
//		KS103_WriteOneByte(0xe8,0x02,0xb0);
//		delay_ms(80);
//		range=KS103_ReadOneByte(0xe8,0x02);
//		range<<=8; 
//		range+=KS103_ReadOneByte(0xe8,0x03);
//		return range;

//}

//u16 Get_Range(void)
//{		
//		if(only_one==0)
//		{
//			KS103_WriteOneByte(0xe8,0x02,0xb4);	//����̽������
//			only_one=1;
//			SCL_IN_2();
//		}
//		else
//		{			
//			if(READ_SCL_2)													
//			{	
//				SCL_OUT_2();
//				
//				range=KS103_ReadOneByte(0xe8,0x02);
//				range<<=8;
//				range+=KS103_ReadOneByte(0xe8,0x03); 
//			}			
//		}
//		return range;  
//}

u16 Get_Range(void)
{	
  	
		if(only_one==0)
		{
			KS103_WriteOneByte(0xe8,0x02,0xb4);	//����̽������
			delay_ms(1);
			only_one=1;
			SCL_IN_2();
			tim3_flag=0;
		}
		else
		{			
			if(tim3_flag<80)
				{
					if(READ_SCL_2)													
					{	
						SCL_OUT_2();
						
						range=KS103_ReadOneByte(0xe8,0x02);
						range<<=8;
						range+=KS103_ReadOneByte(0xe8,0x03); 
						only_one=0;
					}			
		    }
			else{
			   only_one=0;
			}
	   }
		return range;  
}

int Get_Barrier(void)
{
	u16 temp_range=Get_Range();
	if(temp_range<300)						// ����ܽ���⵽�ϰ��ﷵ��2
	{
		return 2;
	}
	else if(temp_range<1500)			// �����Զ��⵽�ϰ��ﷵ��1
	{
		return 1;
	}
	else												//  ����1500����0
	{
		return 0;
	}
}
#endif
