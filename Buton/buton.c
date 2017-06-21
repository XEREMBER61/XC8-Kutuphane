/*******************************************************************************
 * K�t�phane     : Geli�mi� Buton Okuma Fonksiyonu                             *
 * Yazar         : sigmoid                                                     *
 * Web           : http://www.gencmucitler.com                                 *
 * Ba�lang��     : 18 Haziran 2017                                             *
 * D�zenleme     : 22 Haziran 2017                                             *
 * Versiyon      : 0.2                                                         *
 *                                                                             *
 * Butonlar�n kontak s��rama durumlar�n�da dikkate alarak buton durumunu okur. *
 * Bu fonksiyon ile butona bas�lma, b�rak�lma, uzun bas�lma,bas�l� tutulma     *
 * durumlar� kolayca okunabilmektedir.                                         * 
 ******************************************************************************/
// v0.2 Bas�l� Tutuluyor kodu sonuna return butonNo eklendi.
//      �ift t�klama ve K�sa Basma durumlar� eklendi.
// v0.1 ilk d�zenleme.

#include "mcc_generated_files/mcc.h"
#include "buton.h"
#include "zaman.h"

unsigned long butonSure,ciftTiklamaSure;
char butonNo,butonNo_kayit,oncekiButonNo;
bit uzunBasildi,kisaBasildi;

//Bas�lan butonun numaras�n� d�nd�r�r. Hi� bir butona bas�lmad� ise 0x00 d�ner.
char buton_oku(void)
{
    butonNo=0;
    
    //bas�l� olan butonu bul.
    if(!buton1)
        butonNo=1;
//    else if(!buton2)
//        butonNo=2;
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
            if(butonNo) 
            {
                butonSure = miliSaniye();
                butonDurumu = DEBOUNCE;
                butonNo_kayit = butonNo;    //ButonNo yu kaydet, s�rekli butona 
                                            //bas�l�yor mu diye kontrol edilecek
                uzunBasildi=0;
                kisaBasildi=0;
            }
            else
            {
                butonNo_kayit=0;
                return 0x00;
            }
            break;
            //------------------------------------------------------------------
        case DEBOUNCE:
            //ayn� butona bas�lmaya devam m� ediliyor?
            //kontak s��ramas�n� atla
            if(butonNo) 
            {
                if (butonNo == butonNo_kayit) 
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
                    butonNo_kayit=butonNo;
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
            if(butonNo)
            {
                butonDurumu=BASILI_TUTULUYOR;
                butonSure=miliSaniye();
                return butonNo;
            }
            break;
            //------------------------------------------------------------------
        case BASILI_TUTULUYOR:
            if(butonNo)
            {
                if(butonNo==butonNo_kayit)
                {
                    if(kisaBasildi==0)
                    {
                        if(miliSaniye()-butonSure >kisa_basma_suresi)
                        {
                            kisaBasildi=1;
                            butonDurumu=KISA_BASILDI;
                            return butonNo;
                        }
                    }
                    if (uzunBasildi==0)
                    {
                        if(miliSaniye()-butonSure > uzun_basma_suresi)
                        {
                            uzunBasildi=1;
                            butonDurumu=UZUN_BASILDI;   //bir defal�k pals �ret.
                            return butonNo;
                        }
                    }
                    
                    return butonNo;
                }                
            }
            else
            {
                butonSure=miliSaniye();
                butonDurumu=DEBOUNCE2;
            }
            break;
            //------------------------------------------------------------------            
        case KISA_BASILDI:
        case UZUN_BASILDI:
            if(butonNo)
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
                    return butonNo_kayit;
                }                
            }
            else
            {
                butonDurumu=BASILI_TUTULUYOR;
            }
            break; 
            //------------------------------------------------------------------
        case CIFT_TIKLAMA:
            butonDurumu = SERBEST;
            return butonNo_kayit;     
            break;
            //------------------------------------------------------------------
        case BIRAKILDI:

            //�ift t�klamada kullan�lacak kodlar
            //�nceden de ayn� butona m� bas�ld�? �ki kere butona basma s�resi 
            //istenildi�i s�re kadar k�sa m�?
            if(butonNo_kayit==oncekiButonNo && miliSaniye()-ciftTiklamaSure<cift_tiklama_suresi)
            {
                butonDurumu=CIFT_TIKLAMA;
                return butonNo_kayit;
            }
            //bir sonraki t�klama i�in kaydet
            oncekiButonNo=butonNo_kayit;
            ciftTiklamaSure=miliSaniye();
            
            butonDurumu=SERBEST;
            return butonNo_kayit;
            break;    
            //------------------------------------------------------------------
    }
    
    return 0x00;
    
}