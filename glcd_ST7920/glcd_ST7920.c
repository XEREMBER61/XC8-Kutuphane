/**********************************************************
*  Yazar 	: sigmoid
*  Web 		: http://www.gencmucitler.com
*  �lk		: Ocak 2018
*  D�zenleme: Yok 
*  Versiyon : 0.1
*  A��klama : ST7920 chipli 128x64 grafik lcd i�in seri haberle�me 
*  k�t�phanesi
***********************************************************/

#include "mcc_generated_files/mcc.h"
#include "lcd_ST7920.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
char display_kursor_blink;


/******************************************************************************
 * 8 bitlik veriyi seri olarak lcd'ye g�nderir.
 *****************************************************************************/
void lcd_seriverigonder(char veri)
{
    char i;
	for(i=0;i<8;i++)
	{
        LCD_CLK=1;
        __delay_us(5);
		veri=veri<<1;
		LCD_DI=CARRY;
        LCD_CLK=0;
        __delay_us(5);

	}	

    
}

/******************************************************************************
 * LCD ekran kullan�lmadan �nce bu fonksiyon ile �al��t�r�lmal�d�r.
 *****************************************************************************/
void lcd_baslat()
{
    LCD_CLK=0;
    LCD_CS=0;
    LCD_DI=0;
    __delay_ms(50);    
  
    lcd_komut(0x30);
    __delay_us(50);
    lcd_komut(0x30);
    __delay_us(50);   
    lcd_komut(0x0C);    //display a��k, k�rs�r ve blink kapal�.
    __delay_us(50);
    lcd_komut(0x01);    //ekran� sil
    __delay_ms(10);
    lcd_komut(0x06);    //entry mode, sa�a do�ru yaz�lacak.


    display_kursor_blink=0x0C;
}

/******************************************************************************
 * LCD ekrana 1 bytel�k veri g�ndermek i�in 3 bytel�k paketler kullan�l�r.
 * datasheet i�inde nas�l oldu�u a��klan�yor.
 * RS=1; ekrana yaz�lacak veri g�nderir.
 *****************************************************************************/
void lcd_harf(char harf)
{
    LCD_CS=1;
    lcd_seriverigonder(0b11111010);     //rs=1 harf g�nder.
    lcd_seriverigonder(harf & 0xF0);
    lcd_seriverigonder((harf<<4)&0xf0); 
    LCD_CS=0;
}

/******************************************************************************
 * LCD ekrana 1 bytel�k veri g�ndermek i�in 3 bytel�k paketler kullan�l�r.
 * datasheet i�inde nas�l oldu�u a��klan�yor.
 * RS=0; lcd ekran komutu g�nderir.
 *****************************************************************************/
void lcd_komut(char komut)
{
    LCD_CS=1;
    lcd_seriverigonder(0b11111000);     //rs=0 harf g�nder.
    lcd_seriverigonder(komut & 0xF0);
    lcd_seriverigonder((komut<<4)&0xf0); 
    LCD_CS=0;
    __delay_us(75);
}


/********************************************************************************
 * Lcdyi siler.                                                                 *
 * �rnek : lcd_sil();                                                           *
 *******************************************************************************/
void lcd_sil()
{
    lcd_komut(0x01);
}

/********************************************************************************
 * 1. sat�r 1. sutuna gider                                                     *
 *******************************************************************************/
void lcd_satirbasi()
{
    lcd_komut(0x02);
}

/*******************************************************************************
 * �stenilen pozisyona gider.                                                   *
 * �rnek: lcd_git(2,5);                                                         *
 *******************************************************************************/
void lcd_git(char satir, char sutun) {
    char temp;          
    switch (satir) {
        case 1:
            temp = sutun - 1 + 0x80;
            break;
        case 2:
            temp = sutun - 1 + 0x90;
            break;
        case 3:
            temp = (sutun - 1 + 0x88);
            break;
        case 4:
            temp = (sutun - 1 + 0x98);
            break;
    }
    lcd_komut(temp);
}

/*******************************************************************************
 * �stenilen poziyonda ekrana yaz� yazar.                                       *
 * �rnek : lcd_mesajyaz(1,4,"Deneme");                                          *
 *******************************************************************************/
void lcd_mesajyaz(char satir, char sutun, const char *mesaj) {
    lcd_git(satir, sutun);
    do {
        lcd_harf(*mesaj++);
    } while (*mesaj);
    lcd_display_ac();
}


/*******************************************************************************
 * Lcd ekrana en son kald��� pozisyondan itibaren yaz� yazar.                   *
 * �rnek : lcd_mesajyaz_cp("deneme");                                           *
 *******************************************************************************/
void lcd_mesajyaz_cp(const char *mesaj) {
    do {
        lcd_harf(*mesaj++);
    } while (*mesaj);
    lcd_display_ac();
}


/*******************************************************************************
 * LCD ekran� sa�a kayd�r�r.                                                    *
 *******************************************************************************/
void lcd_ekransagakaydir()
{
    lcd_komut(0x1C);
}

/*******************************************************************************
 * LCD ekran� sola kayd�r�r.                                                    *
 *******************************************************************************/
void lcd_ekransolakaydir()
{
    lcd_komut(0x18);
}

/*******************************************************************************
 * K�rs�r� sa�a   kayd�r�r.                                                    *
 *******************************************************************************/
void lcd_kursorsagakaydir()
{
        lcd_komut(0x14);
}

/*******************************************************************************
 * K�rs�r� sola   kayd�r�r.                                                    *
 *******************************************************************************/
void lcd_kursorsolakaydir()
{    
        lcd_komut(0x10);
}


/*******************************************************************************
 * Kurs�r� aktif yapar                                                          *
 *******************************************************************************/
void lcd_kursor_ac(void) {
    display_kursor_blink |= 0x02;
    lcd_komut(display_kursor_blink);
}

/*******************************************************************************
 * K�rs�r� kapat�r.                                                             *
 *******************************************************************************/
void lcd_kursor_kapat(void) {
    display_kursor_blink &= 0xfd;
    lcd_komut(display_kursor_blink);
}

/*******************************************************************************
 * LCD Displayi a�ar.                                                           *
 *******************************************************************************/
void lcd_display_ac(void) {
    display_kursor_blink |= 0x04;
    lcd_komut(display_kursor_blink);

}

/*******************************************************************************
 * LCD Displayi kapat�r.                                                        *
 * nas�l �al��t���n� ��zmedim.
 *******************************************************************************/
void lcd_display_kapat(void) {
    display_kursor_blink &= 0xfb;
    lcd_komut(display_kursor_blink);
}

/*******************************************************************************
 * K�rs�r ekranda yan�p s�ner                                                   *
 *******************************************************************************/
void lcd_blink_ac(void) {
    display_kursor_blink |= 0x01;
    lcd_komut(display_kursor_blink);
}

/*******************************************************************************
 * K�rs�r�n ekranda yan�p s�nme �zelli�ini kapat�r.                             *
 *******************************************************************************/
void lcd_blink_kapat(void) {
    display_kursor_blink &= 0xfe;
    lcd_komut(display_kursor_blink);
}

/*******************************************************************************
 * 1. sat�r 1. sutuna gider                                                     *
 *******************************************************************************/
void lcd_satir1(void) {
    lcd_komut(0x80);
}

/*******************************************************************************
 * 2. sat�r 1. sutuna gider                                                     *
 *******************************************************************************/
void lcd_satir2(void) {
    lcd_komut(0x90);
}

/*******************************************************************************
 * 3. sat�r 1. sutuna gider                                                     *
 *******************************************************************************/
void lcd_satir3(void) {
    lcd_komut(0x88);
}

/*******************************************************************************
 * 4. sat�r 1. sutuna gider                                                     *
 *******************************************************************************/
void lcd_satir4(void) {
    lcd_komut(0x98);
}

/*******************************************************************************
 * printf fonksiyonu i�in                                                       *
 *******************************************************************************/
#ifdef lcdprintf_aktif

void putch(unsigned char byte) {
    lcd_harfyaz(byte);
}
#endif