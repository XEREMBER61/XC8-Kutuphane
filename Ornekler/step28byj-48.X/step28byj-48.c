/*******************************************************************************
 * K�t�phane     : 28BYJ-48 Ad�m motor k�t�phanesi                             *
 * Yazar         : sigmoid                                                     *
 * Web           : http://www.gencmucitler.com                                 *
 * Ba�lang��     : 17 Aral�k  2017                                             *
 * Versiyon      : 0.1                                                         *
 *                                                                             *
 ******************************************************************************/

#include "mcc_generated_files/mcc.h"
#include "step28byj-48.h"

char adim=0;
    
//ad�m motoru ka� ad�mla gidece�ini belirtir.
void adimMotor(unsigned int adimSayisi,char adimYonu,unsigned int adimHizi)
{
    unsigned int i,j;

    for (i = 0; i < adimSayisi; i++) {

        //1 ad�m at
        if (adimYonu == saatYonunde) {
            adim++;
            if (adim == 8)
                adim = 0;
        } else {
            adim--;
            if (adim == 0xFF)
                adim = 7;

        }

        switch (adim) {
            case 0:
                motorPin_Turuncu = 1;
                motorPin_Sari = 0;
                motorPin_Pembe = 0;
                motorPin_Mavi = 0;
                break;
            case 1:
                motorPin_Turuncu = 1;
                motorPin_Sari = 1;
                motorPin_Pembe = 0;
                motorPin_Mavi = 0;
                break;
            case 2:
                motorPin_Turuncu = 0;
                motorPin_Sari = 1;
                motorPin_Pembe = 0;
                motorPin_Mavi = 0;
                break;
            case 3:
                motorPin_Turuncu = 0;
                motorPin_Sari = 1;
                motorPin_Pembe = 1;
                motorPin_Mavi = 0;
                break;
            case 4:
                motorPin_Turuncu = 0;
                motorPin_Sari = 0;
                motorPin_Pembe = 1;
                motorPin_Mavi = 0;
                break;
            case 5:
                motorPin_Turuncu = 0;
                motorPin_Sari = 0;
                motorPin_Pembe = 1;
                motorPin_Mavi = 1;
                break;
            case 6:
                motorPin_Turuncu = 0;
                motorPin_Sari = 0;
                motorPin_Pembe = 0;
                motorPin_Mavi = 1;
                break;
            case 7:
                motorPin_Turuncu = 1;
                motorPin_Sari = 0;
                motorPin_Pembe = 0;
                motorPin_Mavi = 1;
                break;
        }

        for(j=0;j<adimHizi;j++)
                __delay_ms(1);
    }
}

//derece vererek kontrol sa�lan�r.  
void adimMotorDerece(unsigned int adimDerece,char adimYonu,unsigned int adimHizi)
{
    unsigned int adimSayisiSonuc;
    
    adimSayisiSonuc=(unsigned int)(((unsigned long)adimDerece*motorAdimi)/360);
    
    adimMotor(adimSayisiSonuc,adimYonu,adimHizi);
}