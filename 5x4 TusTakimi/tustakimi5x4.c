/*******************************************************************************
 * K�t�phane     : 5x4 Tu� Tak�m� Okuma K�t�phanesi                            *
 * Yazar         : sigmoid                                                     *
 * Web           : http://www.gencmucitler.com                                 *
 * Ba�lang��     : 18 Haziran 2017                                             *
 * Versiyon      : 0.1                                                         *
 *                                                                             *
 * 4x4 matriks tu� tak�m� k�t�phanesi                                          *
 ******************************************************************************/

//SATIRLAR ��k��, SUTUNLAR giri� yap�lmal�.  Giri� portlar� pull-up direnci 
//tak�lmal� veya internal pull-up aktif edilmelidir.

#include "mcc_generated_files/mcc.h"
#include "tustakimi5x4.h"
#include "zaman.h"

unsigned long butonSure, ciftTiklamaSure;
char butonNo, butonNo_kayit, oncekiButonNo;
bit uzunBasildi, kisaBasildi;
char satirno, sutunno;

//bas�lan tu�u oku

char tustakimi_oku(void) {
    //t�m sat�lar ��k�� olmal�
    SATIR1 = 0;
    SATIR2 = 0;
    SATIR3 = 0;
    SATIR4 = 0;
    SATIR5 =0 ;
    
    sutunno = 0;
    satirno=0;

    if (!SUTUN1)
        sutunno = 1;
    else if (!SUTUN2)
        sutunno = 2;
    else if (!SUTUN3)
        sutunno = 3;
    else if (!SUTUN4)
        sutunno = 4;


    //bir butona bas�ld�ysa bas�lan sat�r�da bul.
    if (sutunno) {
        for (satirno = 1; satirno <= 5; satirno++) {
            switch (satirno) {
                case 1:
                    SATIR1 = 0;
                    SATIR2 = 1;
                    SATIR3 = 1;
                    SATIR4 = 1;
                    SATIR5 = 1;
                    break;
                case 2:
                    SATIR1 = 1;
                    SATIR2 = 0;
                    SATIR3 = 1;
                    SATIR4 = 1;
                    SATIR5 = 1;
                    break;
                case 3:
                    SATIR1 = 1;
                    SATIR2 = 1;
                    SATIR3 = 0;
                    SATIR4 = 1;
                    SATIR5 = 1;
                    break;
                case 4:
                    SATIR1 = 1;
                    SATIR2 = 1;
                    SATIR3 = 1;
                    SATIR4 = 0;
                    SATIR5 = 1;
                    break;
                case 5:
                    SATIR1 = 1;
                    SATIR2 = 1;
                    SATIR3 = 1;
                    SATIR4 = 1;
                    SATIR5 = 0;                    
                    break;  
            }

            //bu sat�rda ki tu� mu bas�l� ?
            if (!SUTUN1)
                break;
            else if (!SUTUN2)
                break;
            else if (!SUTUN3)
                break;
            else if (!SUTUN4)
                break;                        
        }
    }

    
    //sat�r ve s�t�n bulundu mu?
    
    if(satirno && sutunno)
    {
        butonNo=tuslar[(satirno-1)*4+(sutunno-1)];
    }
    else
    {
        butonNo=0;
    }
    return buton_kontrol();
}


//Buton durumunu ve kontak s��ramas�n� test eder.
char buton_kontrol(void) {
    switch (butonDurumu) {
        case SERBEST: //ilk defa bas�ld���nda 
            if (butonNo) {
                butonSure = miliSaniye();
                butonDurumu = DEBOUNCE;
                butonNo_kayit = butonNo; //ButonNo yu kaydet, s�rekli butona 
                //bas�l�yor mu diye kontrol edilecek
                uzunBasildi = 0;
                kisaBasildi = 0;
            } else {
                butonNo_kayit = 0;
                return 0x00;
            }
            break;
            //------------------------------------------------------------------
        case DEBOUNCE:
            //ayn� butona bas�lmaya devam m� ediliyor?
            //kontak s��ramas�n� atla
            if (butonNo) {
                if (butonNo == butonNo_kayit) {
                    if (miliSaniye() - butonSure > debounce_suresi) {
                        butonDurumu = BASILDI; //bir defal�k pals �ret.
                        butonSure = miliSaniye();
                        return butonNo;
                    }
                }
                else {
                    //farkl� butona bas�lm��.
                    butonNo_kayit = butonNo;
                    butonSure = miliSaniye();
                }
            } else {
                //kontak anl�k 0'a d��t�yse veya b�rak�ld�ysa
                butonDurumu = SERBEST;
            }
            break;
            //------------------------------------------------------------------
        case BASILDI:
            if (butonNo) {
                butonDurumu = BASILI_TUTULUYOR;
                butonSure = miliSaniye();
                return butonNo;
            }
            break;
            //------------------------------------------------------------------
        case BASILI_TUTULUYOR:
            if (butonNo) {
                if (butonNo == butonNo_kayit) {
                    if (kisaBasildi == 0) {
                        if (miliSaniye() - butonSure > kisa_basma_suresi) {
                            kisaBasildi = 1;
                            butonDurumu = KISA_BASILDI;
                            return butonNo;
                        }
                    }
                    if (uzunBasildi == 0) {
                        if (miliSaniye() - butonSure > uzun_basma_suresi) {
                            uzunBasildi = 1;
                            butonDurumu = UZUN_BASILDI; //bir defal�k pals �ret.
                            return butonNo;
                        }
                    }

                    return butonNo;
                }
            } else {
                butonSure = miliSaniye();
                butonDurumu = DEBOUNCE2;
            }
            break;
            //------------------------------------------------------------------            
        case KISA_BASILDI:
        case UZUN_BASILDI:
            if (butonNo) {
                butonDurumu = BASILI_TUTULUYOR;
                return butonNo;
            }
            break;
            //------------------------------------------------------------------
        case DEBOUNCE2:
            //ayn� butona bas�lmaya devam m� ediliyor?
            //kontak s��ramas�n� atla
            if (butonNo == 0) {
                if (miliSaniye() - butonSure > debounce_suresi) {
                    butonDurumu = BIRAKILDI; //bir defal�k pals �ret.            
                    return butonNo_kayit;
                }
            } else {
                butonDurumu = BASILI_TUTULUYOR;
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
            if (butonNo_kayit == oncekiButonNo && miliSaniye() - ciftTiklamaSure < cift_tiklama_suresi) {
                butonDurumu = CIFT_TIKLAMA;
                return butonNo_kayit;
            }
            //bir sonraki t�klama i�in kaydet
            oncekiButonNo = butonNo_kayit;
            ciftTiklamaSure = miliSaniye();

            butonDurumu = SERBEST;
            return butonNo_kayit;
            break;
            //------------------------------------------------------------------
    }

    return 0x00;

}