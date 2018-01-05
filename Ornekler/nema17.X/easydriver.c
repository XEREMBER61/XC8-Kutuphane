/*******************************************************************************
 * K�t�phane     : Easydriver Ad�m motor k�t�phanesi                           *
 * Yazar         : sigmoid                                                     *
 * Web           : http://www.gencmucitler.com                                 *
 * Ba�lang��     : 4 Ocak 2018                                                 *
 * Versiyon      : 0.2                                                         *
 *                                                                             *
 ******************************************************************************/

#include "mcc_generated_files/mcc.h"
#include "easydriver.h"
#include <math.h>

void adimMotor(unsigned int adimSayisi, char adimYonu) {
    unsigned int i, j, adim;
    unsigned int maxAdimAdeti, hizlanmaAdimAdeti, yavaslamaAdimAdeti, yavaslamaadim;
    unsigned int minbekleme,maxbekleme,farkbekleme,bekleme;
    
    //h�zlanma yava�lama ve maksimum h�zda gidecek ad�m say�lar�n� hesapla.
    minbekleme=_sure/_minumum_hiz;      //minumum h�z i�in bekleme s�resini hesapla
    maxbekleme=_sure/_maksimum_hiz;     //maksimum h�z i�in bekleme s�resini hesapla
 
    //��k�� ve ini� rampalar�ndaki ad�m say�s�n� hesapla
    farkbekleme=minbekleme-maxbekleme;   
    
    hizlanmaAdimAdeti=farkbekleme*_hizlanmaadimi;
    yavaslamaAdimAdeti=farkbekleme*_yavaslamaadimi;

    //at�lacak ad�m say�s� maksimum h�za ula�mak i�in yeterli mi?
    if(adimSayisi<(hizlanmaAdimAdeti+yavaslamaAdimAdeti))
    {
        hizlanmaAdimAdeti=(unsigned int)(((unsigned long)adimSayisi*_hizlanmaadimi)/(_hizlanmaadimi+_yavaslamaadimi));
        yavaslamaAdimAdeti=adimSayisi-hizlanmaAdimAdeti;
        maxAdimAdeti=0;
    }
    else
    {
        
        maxAdimAdeti=adimSayisi-hizlanmaAdimAdeti-yavaslamaAdimAdeti;
    }
    
    

    //ad�m y�n�n� ayarla.
    step_DIR = adimYonu;

    adim = 0;
    bekleme=minbekleme;

    //hizlanma b�l�m�
    while (adim <hizlanmaAdimAdeti) {
        for (i = 0; i < _hizlanmaadimi; i++) {
            step_PULSE = 1;
            step_bekle(bekleme);
            step_PULSE = 0;
            step_bekle(bekleme);
            
            adim++;            
            if(adim>=hizlanmaAdimAdeti)
                break;   //d�ng�den ��k
        }
        
        bekleme--;  //bir kademe h�zlan.
        if(bekleme==maxbekleme)
            break;

    }

    //maksimum h�zda gidece�i b�l�m
    if (maxAdimAdeti > 0) {
        bekleme=maxbekleme;
        for (i = 0; i < maxAdimAdeti; i++) {
            step_PULSE = 1;
            step_bekle(bekleme);
            step_PULSE = 0;
            step_bekle(bekleme);
        }
        adim = adim + maxAdimAdeti;
    }

    //yava�lama b�l�m�
    yavaslamaadim=0;
    while (yavaslamaadim < yavaslamaAdimAdeti) {
        for (i = 0; i < _yavaslamaadimi; i++) {
            step_PULSE = 1;
            step_bekle(bekleme);
            step_PULSE = 0;
            step_bekle(bekleme);
            adim++;

            if (adim>=adimSayisi) //at�lacak ad�m adeti dolunca fonksiyondan ��k.
                return;
        }
        yavaslamaadim = yavaslamaadim + _yavaslamaadimi;
        bekleme++;
    }
}

//------------------------------------------------------------------------------

void adimMotorDerece(unsigned int adimDerece, char adimYonu) {
    unsigned int adimSayisiSonuc;    
    adimSayisiSonuc=(unsigned int)(((unsigned long)adimDerece*motorAdimi)/360);    
    adimMotor(adimSayisiSonuc,adimYonu);    
}

//------------------------------------------------------------------------------

void step_bekle(unsigned int sure) {
    unsigned int i;

    for (i = 0; i < sure; i++)
        __delay_us(10);
}