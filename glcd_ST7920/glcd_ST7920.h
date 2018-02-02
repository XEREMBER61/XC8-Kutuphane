/**********************************************************
*  Yazar 	: sigmoid
*  Web 		: http://www.gencmucitler.com
*  �lk		: Ocak 2018
*  D�zenleme: �ubat 2018  
*  Versiyon : 0.11
*  A��klama : ST7920 chipli 128x64 grafik lcd i�in seri haberle�me 
*  k�t�phanesi
***********************************************************/
// v0.11 ufak hata d�zeltme

#define     LCD_CS      LATA3
#define     LCD_DI      LATD0
#define     LCD_CLK     LATC3

//printf fonksiyonu lcd'ye yazacak m�?
#define lcdprintf_aktif

void LCD_TEXT(unsigned char x,unsigned char y,const char *DATEN);

void lcd_seriverigonder(char veri);
void lcd_baslat();
void lcd_harf(char harf);
void lcd_komut(char komut);

void lcd_sil();
void lcd_satirbasi();
void lcd_git(char satir, char sutun);
void lcd_mesajyaz(char satir, char sutun, const char *mesaj);
void lcd_mesajyaz_cp(const char *mesaj);
void lcd_ekransagakaydir();
void lcd_ekransolakaydir();
void lcd_kursorsagakaydir();
void lcd_kursorsolakaydir();
void lcd_kursor_ac(void);
void lcd_kursor_kapat(void);
void lcd_display_ac(void);
void lcd_display_kapat(void);
void lcd_blink_ac(void);
void lcd_blink_kapat(void);
void lcd_temel_komutseti(void);
void lcd_gelismis_komutseti(void);
void lcd_satir_tersle(char satirno);
