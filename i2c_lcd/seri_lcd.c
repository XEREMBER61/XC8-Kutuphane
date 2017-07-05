/*******************************************************************************
 * K�t�phane     : I2C LCD                                                     *
 * Yazar         : sigmoid                                                     *
 * Web           : http://www.gencmucitler.com                                 *
 * Ba�lang��     : 05 Temmuz 2017                                              *
 * Versiyon      : 0.2                                                         *
 *                                                                             *
 * PCF8574 mod�l� ile I2C Lcd kullan�m k�t�phanesi                             *
 ******************************************************************************/
#include "mcc_generated_files/mcc.h"
#include "seri_lcd.h"
#include "pcf8574.h"

//De�i�kenler
char display_kursor_blink; //display,kursor ve blink a� kapat komutlar� i�in.

//PORT bilgisi
typedef union
{
    //bit d�zeyi
    struct{
        char P0:1;      //RS
        char P1:1;      //RW
        char P2:1;      //E
        char P3:1;      //arka ayd�nlatma
        char P4:1;      //D4
        char P5:1;      //D5
        char P6:1;      //D6
        char P7:1;      //D7
    }pin;
    //bit d�zeyi
    struct{
        char RS:1;      //RS
        char RW:1;      //RW
        char E:1;      //E
        char LED:1;      //arka ayd�nlatma
        char D4:1;      //D4
        char D5:1;      //D5
        char D6:1;      //D6
        char D7:1;      //D7       
    }lcd;
    //byte
    char port;
}_PCF_PORT;


_PCF_PORT pcf_port;

/*******************************************************************************
 *  PCF8574 �zerinden veriyi g�nderdikten sonra enable pinini high-low yapar.  *
 *******************************************************************************/
void pcf8574_yaz_wEnable() {

    I2C1_MESSAGE_STATUS status;
    uint8_t writeBuffer[3];
    uint16_t timeOut;

    writeBuffer[0] = lcd_data;
    pcf_port.lcd.E = 1;
    writeBuffer[1] = lcd_data;
    pcf_port.lcd.E = 0;
    writeBuffer[2] = lcd_data;
    
    timeOut = 0;
    while (status != I2C1_MESSAGE_FAIL) {
        
        //3 byte g�nder
        I2C1_MasterWrite(writeBuffer,
                3,
                pcf_adres,
                &status);

        // veri g�nderilene kadar bekle.
        while (status == I2C1_MESSAGE_PENDING);

        //ba�ar�l� olarak g�nderildi isi ��k
        if (status == I2C1_MESSAGE_COMPLETE)
            break;

        //Veri g�nderilmediyse tekrar g�nder.
        //Ba�ar�s�z tekrar say�s�na ula��ld�ysa da ��k.
        if (timeOut == pcf_tekrar)
            break;
        else
            timeOut++;
    }

}

/*******************************************************************************
 *  LCD ekran� �al��t�r�r. �lk �nce bu fonksiyon �al��t�r�lmal�d�r.             *
 *******************************************************************************/
void lcd_baslat(void) {

    pcf8574_yaz(0x00);
    lcd_data=0x00;

    lcd_data = 0x20 | (lcd_data & 0x0f); //4 bit mod

    pcf8574_yaz_wEnable();
    __delay_ms(5);
    
    lcd_komut(0x28);
    __delay_us(40);
    lcd_komut(0x0C); //display on
    __delay_us(40);
    lcd_komut(0x06); //cursor ileri
    __delay_ms(2);
        
    lcd_sil();
    lcd_aydinlatma_ac();
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
            temp = sutun - 1 + 0xc0;
            break;
        case 3:
            temp = (sutun - 1 + 0x94);
            break;
        case 4:
            temp = (sutun - 1 + 0xd4);
            break;
    }
    lcd_komut(temp);
    __delay_us(100);
}

/*******************************************************************************
 * �stenilen poziyonda ekrana yaz� yazar.                                       *
 * �rnek : lcd_mesajyaz(1,4,"Deneme");                                          *
 *******************************************************************************/
void lcd_mesajyaz(char satir, char sutun, const char *mesaj) {
    lcd_git(satir, sutun);
    do {
        lcd_harfyaz(*mesaj++);
    } while (*mesaj);
}

/*******************************************************************************
 * Lcd ekrana en son kald��� pozisyondan itibaren yaz� yazar.                   *
 * �rnek : lcd_mesajyaz_cp("deneme");                                           *
 *******************************************************************************/
void lcd_mesajyaz_cp(const char *mesaj) {
    do {
        lcd_harfyaz(*mesaj++);
    } while (*mesaj);
}

/*******************************************************************************
 * Lcd me�gul oldu�u s�rece bu fonksiyon i�inde bekler..                        *
 * Lcd_komut ve lcd_harfyaz fonksiyonlar� bu fonksiyonu kullan�r.               *
 *******************************************************************************/
void lcd_mesgulmu(void) {
    __delay_us(100); //bekle.
}

/*******************************************************************************
 * Lcd ekrana tek bir harf yazar.                                               *
 * �rnek : lcd_harfyaz('A');                                                    *
 *******************************************************************************/
void lcd_harfyaz(char harf) {
    lcd_mesgulmu();
    lcd_rs = 1;     //harf

    lcd_data = (lcd_data & 0x0f) | (harf & 0xf0); //high verisini g�nder.
    pcf8574_yaz_wEnable();
    __delay_us(200);

    lcd_data = (lcd_data & 0x0f) | (harf << 4); //low verisini g�nder.
    pcf8574_yaz_wEnable();
    __delay_us(200);
}


/*******************************************************************************
 * Lcd komutlar�n� g�nderir.                                                    *
 *******************************************************************************/
void lcd_komut(char komut) {
    lcd_mesgulmu();
    lcd_rs = 0;     //komut

    lcd_data = (lcd_data & 0x0f) | (komut & 0xf0); //high verisini g�nder.
    pcf8574_yaz_wEnable();
    __delay_ms(5);
    
    lcd_data = (lcd_data & 0x0f) | (komut << 4); //low verisini g�nder.
    pcf8574_yaz_wEnable();
    __delay_ms(5);
}

/*******************************************************************************
 * Lcd ekranda �zel karakter olu�turur.                                         *
 * �rnek:
 * char kalp[8]={
 * 0b00000,
 * 0b01010,
 * 0b10101,
 * 0b10001,
 * 0b01010,
 * 0b00100,
 * 0b00000,
 * 0b00000};
 * 
 * lcd_ozelkarakter(0,kalp);   //kalp sembol� lcd ekrana tan�mlar
 * lcd_harfyaz(0); // kalp semb�l�n� �iz..
 *******************************************************************************/
void lcd_ozelkarakter(char karakterno, char patern[8]) {
    char temp, i;
    temp = 0x40 | (karakterno << 3);
    lcd_komut(temp);

    for (i = 0; i < 8; i++) {
        lcd_harfyaz(patern[i]);
    }
    lcd_satirbasi();
}

/*******************************************************************************
 * Lcdyi siler.                                                                 *
 * �rnek : lcd_sil();                                                           *
 *******************************************************************************/
void lcd_sil(void) {
    lcd_komut(0x01);
}

/*******************************************************************************
 * 1. sat?r 1. sutuna gider                                                     *
 *******************************************************************************/
void lcd_satirbasi(void) {
    lcd_komut(0x02);
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
 * LCD ekran� sola kayd�r�r.                                                    *
 *******************************************************************************/
void lcd_sola_kaydir(void) {
    lcd_komut(0x18);
}

/*******************************************************************************
 * LCD ekran� sa�a kayd�r�r.                                                    *
 *******************************************************************************/
void lcd_saga_kaydir(void) {
    lcd_komut(0x1C);
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
    lcd_komut(0xc0);
}

/*******************************************************************************
 * 3. sat�r 1. sutuna gider                                                     *
 *******************************************************************************/
void lcd_satir3(void) {
    lcd_komut(0x94);
}

/*******************************************************************************
 * 4. sat�r 1. sutuna gider                                                     *
 *******************************************************************************/
void lcd_satir4(void) {
    lcd_komut(0xd4);
}

/*******************************************************************************
 * printf fonksiyonu i�in                                                       *
 *******************************************************************************/
#ifdef lcdprintf_aktif

void putch(unsigned char byte) {
    lcd_harfyaz(byte);
}
#endif

/*******************************************************************************
 * LCD arkaplan ayd�nlatmay� a�                                                *
 *******************************************************************************/
void lcd_aydinlatma_ac(void)
{
    pcf_port.lcd.LED=1;
    pcf8574_yaz(pcf_port.port);
}

/*******************************************************************************
 * LCD arkaplan ayd�nlatmay� kapat                                             *
 *******************************************************************************/
void lcd_aydinlatma_kapat(void)
{
    pcf_port.lcd.LED=0;
    pcf8574_yaz(pcf_port.port);
}
