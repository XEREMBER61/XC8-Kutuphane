/*******************************************************************************
 * K�t�phane     : Geli�mi� Buton Okuma Fonksiyonu                             *
 * Yazar         : sigmoid                                                     *
 * Web           : http://www.gencmucitler.com                                 *
 * Ba�lang��     : 18 Haziran 2017                                             *
 * Versiyon      : 0.1                                                         *
 *                                                                             *
 * Butonlar�n kontak s��rama durumlar�n�da dikkate alarak buton durumunu okur. *
 * Bu fonksiyon ile butona bas�lma, b�rak�lma, uzun bas�lma,bas�l� tutulma     *
 * durumlar� kolayca okunabilmektedir.                                         * 
 ******************************************************************************/

#ifndef BUTON_H
#define	BUTON_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#define buton1 PORTBbits.RB0
#define buton2 PORTBbits.RB1
#define buton3 PORTBbits.RB2

#define debounce_suresi 20u         //20ms
#define uzun_basma_suresi   2000u   //2saniye

typedef enum _buton_durum_e
{
    SERBEST=0,          //buton bas�lmad���nda bo�ta ise.
    DEBOUNCE,           //buton bas�lma an�ndaki kontak s�cramas�(debounce) testi i�in
    BASILDI,            //1 kez �al���r
    BASILI_TUTULUYOR,   //butona bas�l�yor
    UZUN_BASILDI,       //buton belirtilen s�re boyunca bas�l�rsa 1 kez �al���r.
    DEBOUNCE2,          //buton b�rak�lma an�ndaki kontak s�cramas�(debounce) testi i�in
    BIRAKILDI           //1 kez �al���r.
}buton_durum_e;

//De�i�ken Tan�mlamalar�
buton_durum_e butonDurumu=SERBEST;

//fonksiyon prototipleri
char buton_oku(void);
char buton_kontrol(void);
#endif	/* BUTON_H */

