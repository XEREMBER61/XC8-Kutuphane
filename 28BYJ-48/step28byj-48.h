/*******************************************************************************
 * K�t�phane     : 28BYJ-48 Ad�m motor k�t�phanesi                             *
 * Yazar         : sigmoid                                                     *
 * Web           : http://www.gencmucitler.com                                 *
 * Ba�lang��     : 17 Aral�k  2017                                             *
 * Versiyon      : 0.1                                                         *
 *                                                                             *
 ******************************************************************************/

//pin tan�mlamalar�
#define motorPin_Turuncu    LATB0
#define motorPin_Sari       LATB1
#define motorPin_Pembe      LATB2
#define motorPin_Mavi       LATB3

//motor y�n�
#define saatYonunde     0
#define saatTersYonunde 1
#define CW              0
#define CCW             1


//motorun 360 derecelik�n�� i�in gereken ad�m say�s�
#define motorAdimi  4096

//fonksiyon prototipleri
void adimMotor(unsigned int adimSayisi,char adimYonu,unsigned int adimHizi);
void adimMotorDerece(unsigned int adimDerece,char adimYonu,unsigned int adimHizi);