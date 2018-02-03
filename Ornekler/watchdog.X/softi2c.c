/**********************************************************
*  Yazar 	: sigmoid
*  Web 		: http://www.gencmucitler.com
*  �lk		: 9 Temmuz 2017
*  D�zenleme: Yok 
*  Versiyon : 0.1
*  A��klama :  software i2c master mode
*  100KHz ba�lant� h�z�..
***********************************************************/
#include "mcc_generated_files/mcc.h"
#include "softi2c.h"



//di�er fonksiyonlar �al��t�r�lmadan �nce ilk olarak bu �al��t�r�lmal�
void __attribute__((optimize(0))) softi2c_kur(void)
{
	SOFT_SCL=1;
	SOFT_SDA=1;
	SOFT_SCL_TRIS=0;	//��k��
	SOFT_SDA_TRIS=1;	//high empedans - giri�
}	

//start sinyalini g�nderir
void __attribute__((optimize(0))) softi2c_baslat(void)
{
	SOFT_SCL=1;
	__delay_us(4);
	SOFT_SDA_TRIS=0;	//��k��
	SOFT_SDA=0;	// Clock high konumda iken 1 den 0 a d��.
	__delay_us(4);
	SOFT_SCL=0;
	SOFT_SDA_TRIS=1;	//giri�	
}
	
//stop sinyalini g�nderir
void __attribute__((optimize(0))) softi2c_durdur(void)
{
	SOFT_SDA_TRIS=0;
	SOFT_SDA=0;
	SOFT_SCL=1;
	__delay_us(4);
	SOFT_SDA_TRIS=1;	//Clock high konumunda iken 0 dan 1e ��k.
	__delay_us(4);
}

//restart sinyalini g�nderir	
void __attribute__((optimize(0))) softi2c_yenidenbaslat(void)
{
	SOFT_SCL=1;
	__delay_us(4);
	SOFT_SDA_TRIS=0;	//��k��
	SOFT_SDA=0;	// Clock high konumda iken 1 den 0 a d��.
	__delay_us(4);
	SOFT_SCL=0;
	SOFT_SDA_TRIS=1;	//giri�	
}

//1 byte veri g�nderir, ack sinyalini okur
char __attribute__((optimize(0))) softi2c_yaz(char veri)
{
	char i,temp;
	SOFT_SCL=0;
	for(i=8;i>0;i--)
	{
		veri=veri<<1;
		if(CARRY==0)
		{
			SOFT_SDA_TRIS=0;
			SOFT_SDA=0;
		}	
		else
		{
			SOFT_SDA_TRIS=1;
			SOFT_SDA=1;
		}	
		SOFT_SCL=1;
		__delay_us(4);
		SOFT_SCL=0;
		SOFT_SDA_TRIS=1;
	}	
	//0 d�nerse ack al�nm�� demektir.
		SOFT_SCL=0;
		SOFT_SDA_TRIS=1;
		__delay_us(4);
		SOFT_SCL=1;
		temp=SOFT_SDA;	//ack de�erini al.
		SOFT_SCL=0;
		
		return temp;
		
}

//1 byte veri okur, ack sinyali g�nderir.
char __attribute__((optimize(0))) softi2c_oku(char onay)
{
	char i,veri=0;
	SOFT_SCL=0;
	SOFT_SDA_TRIS=1;
	for(i=8;i>0;i--)
	{
		veri=veri<<1;
		SOFT_SCL=1;
		__delay_us(4);
		if(SOFT_SDA==1)
		{
			veri= veri | 0x01;
		}	
		SOFT_SCL=0;
        __delay_us(2);	
	}	
	//onay kodunu g�nder..
	if(onay==0)
	{
		SOFT_SDA_TRIS=0;
		SOFT_SDA=0;
	}	
	else
	{
		SOFT_SDA_TRIS=1;
		SOFT_SDA=1;
	}	
	SOFT_SCL=1;
	__delay_us(4);
	SOFT_SCL=0;
	SOFT_SDA_TRIS=1;
	
	return veri;
}
	
