/*******************************************************************************
 * K�t�phane     : PCF8574 I2C I/O Expander                                    *
 * Yazar         : sigmoid                                                     *
 * Web           : http://www.gencmucitler.com                                 *
 * Ba�lang��     : 4 Temmuz 2017                                               *
 * Versiyon      : 0.1                                                         *
 *                                                                             *
 * PCF8574 giri�/��k�� port �o�ullay�c�                                        *
 ******************************************************************************/

//pcf_adres de�eri ile chip in adres kodu girilmelidir. Adres bilgisi datasheetten 
//��renebilirsiniz. PCF8574 ile PCF8574A n�n adres kodlar� farkl�d�r. Bu sayede 
//ayn� hatta 8 adet PCF8574 ve 8 adet PCF8574A ba�lanabilir. B�ylece toplamda
//16 adet port �o�alt�c� ba�lan�labilinir.


#ifndef PCF8574_H
#define	PCF8574_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#ifndef pcf_adres
#define pcf_adres   0x3F    //entegrenin adresi
#endif

#define pcf_tekrar   10     //hatal� g�nderimde tekrar deneme say�s�

//fonksiyon prototipleri

void pcf8574_yaz(char veri);


#endif	/* PCF8574_H */

