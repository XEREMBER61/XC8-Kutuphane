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

#include "mcc_generated_files/mcc.h"
#include "buton.h"
#include "zaman.h"

unsigned long butonSure;
char butonNo,oncekiButon;
bit uzunBasildi;

//Bas�lan butonun numaras�n� d�nd�r�r. Hi� bir butona bas�lmad� ise 0x00 d�ner.
char buton_oku(void)
{
    butonNo=0;
    
    //bas�l� olan butonu bul.
    if(!buton1)
        butonNo=1;
    else if(!buton2)
        butonNo=2;
//    else if(!buton3)
//        butonNo=3;
                
    return buton_kontrol();
}


//Buton durumunu ve kontak s��ramas�n� test eder.
char buton_kontrol(void)
{
    switch(butonDurumu)
    {
        case SERBEST:   //ilk defa bas�ld���nda 
            if(butonNo>0) 
            {
                butonSure = miliSaniye();
                butonDurumu = DEBOUNCE;
                oncekiButon = butonNo;
                uzunBasildi=0;
            }
            else
            {
                oncekiButon=0;
                return 0x00;
            }
            break;
            //------------------------------------------------------------------
        case DEBOUNCE:
            //ayn� butona bas�lmaya devam m� ediliyor?
            //kontak s��ramas�n� atla
            if(butonNo>0) 
            {
                if (butonNo == oncekiButon) 
                {
                    if (miliSaniye() - butonSure > debounce_suresi) 
                    {
                        butonDurumu = BASILDI;      //bir defal�k pals �ret.
                        butonSure = miliSaniye();
                        return butonNo;
                    }
                } 
                else
                {
                    //farkl� butona bas�lm��.
                    oncekiButon=butonNo;
                    butonSure=miliSaniye();
                }
            }
            else
            {
                //kontak anl�k 0'a d��t�yse veya b�rak�ld�ysa
                butonDurumu=SERBEST;
            }
            break; 
            //------------------------------------------------------------------
        case BASILDI:   
            if(butonNo>0)
            {
                butonDurumu=BASILI_TUTULUYOR;
                butonSure=miliSaniye();
                return butonNo;
            }
            break;
            //------------------------------------------------------------------
        case BASILI_TUTULUYOR:
            if(butonNo>0)
            {
                if(butonNo==oncekiButon)
                {
                    if (uzunBasildi==0)
                    {
                        if(miliSaniye()-butonSure > uzun_basma_suresi)
                        {
                            uzunBasildi=1;
                            butonDurumu=UZUN_BASILDI;   //bir defal�k pals �ret.
                            return butonNo;
                        }
                    }
                }                
            }
            else
            {
                butonSure=miliSaniye();
                butonDurumu=DEBOUNCE2;
            }
            break;
            //------------------------------------------------------------------
        case UZUN_BASILDI:
            if(butonNo>0)
            {
                butonDurumu=BASILI_TUTULUYOR;
                return butonNo;
            }
            break;
            //------------------------------------------------------------------
        case DEBOUNCE2:
            //ayn� butona bas�lmaya devam m� ediliyor?
            //kontak s��ramas�n� atla
            if(butonNo==0) 
            { 
                if (miliSaniye() - butonSure > debounce_suresi) 
                {
                    butonDurumu = BIRAKILDI;        //bir defal�k pals �ret.            
                    return oncekiButon;
                }                
            }
            else
            {
                butonDurumu=BASILI_TUTULUYOR;
            }
            break; 
            //------------------------------------------------------------------
        case BIRAKILDI:
            butonDurumu=SERBEST;
            return oncekiButon;
            break;    
            //------------------------------------------------------------------
    }
    
    return 0x00;
    
}