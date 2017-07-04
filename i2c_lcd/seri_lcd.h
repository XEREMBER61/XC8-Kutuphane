/*******************************************************************************
 * K�t�phane     : I2C LCD                                                     *
 * Yazar         : sigmoid                                                     *
 * Web           : http://www.gencmucitler.com                                 *
 * Ba�lang��     : 05 Temmuz 2017                                              *
 * Versiyon      : 0.1                                                         *
 *                                                                             *
 * PCF8574 mod�l� ile I2C Lcd kullan�m k�t�phanesi                             *
 ******************************************************************************/

/*      Standart LCD ayak ba�lant�lar�
1: Gnd  2: Vcc  3: Vee - Kontras aya��
4: RS   5: RW   6: E
7: D0   8: D1   9: D2   10: D3  11: D4  12: D5  13: D6  14: D7
15: Backlight Vcc       16: Backlight Gnd                                     */

/*PCF8574A entegresinin lcd ekran ba�lant�s�
 * 
 * P0: RS
 * P1: RW
 * P2: E
 * P3: ayd�nlatma
 * P4: D4
 * P5: D5
 * P6: D6
 * P7: D7
 */

#define pcf_adres   0x3F    //i2c entegrenin adresi

//#define LCDBIT8    //lcd ekrana 8bit mi eri�ilecek
#define LCDBIT4    //yoksa 4 bit mi?

#ifdef LCDBIT4
#define LCDustpin     //4bit eri�ilecekse hangi pinler kullan�lacak
//#define LCDaltpin
#endif

//RW pini PIC'e mi yoksa Topra�a m� ba�l�
//#define lcd_rw_aktif

//printf fonksiyonu lcd'ye yazacak m�?
#define lcdprintf_aktif

// kullan�lacak lcd ayaklar?
#define lcd_data	pcf_port.port
#define lcd_read    pcf_port.port
//#define lcd_tris	TRISB

#define lcd_rs          pcf_port.lcd.RS
//#define lcd_tris_rs     TRISA6
#define lcd_e           pcf_port.lcd.E
//#define lcd_tris_e      TRISA7

#ifdef lcd_rw_aktif
#define lcd_rw           pcf_port.lcd.RW
//#define lcd_tris_rw     TRISA1
#endif

//fonksiyon prototipleri
void lcd_baslat(void);
void lcd_git(char satir, char sutun);
void lcd_mesajyaz(char satir, char sutun, const char *mesaj);
void lcd_mesajyaz_cp(const char *mesaj);
#ifdef lcd_rw_aktif
    void lcd_mesgulmu(void);
    char lcd_harfoku(void);
#endif
void lcd_harfyaz(char harf);
void lcd_ozelkarakter(char karakterno,char patern[8]);
void lcd_komut(char komut);
void lcd_sil(void);
void lcd_satirbasi(void);
void lcd_kursor_ac(void);
void lcd_kursor_kapat(void);
void lcd_display_ac(void);
void lcd_display_kapat(void);
void lcd_blink_ac(void);
void lcd_blink_kapat(void);
void lcd_sola_kaydir(void);
void lcd_saga_kaydir(void);
void lcd_satir1(void);
void lcd_satir2(void);
void lcd_satir3(void);
void lcd_satir4(void);
void lcd_aydinlatma_ac(void);
void lcd_aydinlatma_kapat(void);
#ifdef lcdprintf_aktif
void putch(unsigned char byte);
#endif
