/*******************************************************************************
 * K�t�phane     : Geli�mi� Buton Okuma Fonksiyonu                             *
 * Yazar         : sigmoid                                                     *
 * Web           : http://www.gencmucitler.com                                 *
 * Ba�lang��     : 18 Haziran 2017                                             *
 * Versiyon      : 0.1                                                         *
 *                                                                             *
 * 4x4 matriks tu� tak�m� k�t�phanesi                                          *
 ******************************************************************************/

//Portun 0..3 ��k�� 4..7 giri� yap�lmal�. K�saca Sat�rlar ��k��, sut�nlar giri� 
//yap�lmal�. Giri� portlar� pull-up direnci tak�lmal� veya internal pull-up 
//aktif edilmelidir.

#define SATIR1  LATBbits.LATB0        //sat�rlar
#define SATIR2  LATBbits.LATB1
#define SATIR3  LATBbits.LATB2
#define SATIR4  LATBbits.LATB3

#define SUTUN1  PORTBbits.RB4        //s�tunlar
#define SUTUN2  PORTBbits.RB5
#define SUTUN3  PORTBbits.RB6
#define SUTUN4  PORTBbits.RB7


// tu� tak�m� patterni
const char tuslar[]={   '1','2','3','A',
                        '4','5','6','B',
                        '7','8','9','C',
                        '*','0','#','D'    
};

#define debounce_suresi 20u         // 20ms
#define cift_tiklama_suresi 250u    // iki kez t�klama i�in gereken maksimum s�re.
#define kisa_basma_suresi   300u    // k�sa basma s�resi �ift t�klama s�resinden 
                                    // uzun girilmeli.
#define uzun_basma_suresi   1500u   //2saniye

typedef enum _buton_durum_e
{
    SERBEST=0,          //buton bas�lmad���nda bo�ta ise.
    DEBOUNCE,           //buton bas�lma an�ndaki kontak s�cramas�(debounce) testi i�in
    BASILDI,            //1 kez �al���r
    BASILI_TUTULUYOR,   //butona bas�l�yor
    CIFT_TIKLAMA,       //iki kez pe� pe�e butona bas�l�p b�rak�l�nca tetiklenir.
    KISA_BASILDI,       //butona k�sa bir s�re bas�l�nca 1 kez tetiklenir.
    UZUN_BASILDI,       //buton belirtilen s�re boyunca bas�l�rsa 1 kez �al���r.
    DEBOUNCE2,          //buton b�rak�lma an�ndaki kontak s�cramas�(debounce) testi i�in
    BIRAKILDI           //1 kez �al���r.
}buton_durum_e;

//De�i�ken Tan�mlamalar�
buton_durum_e butonDurumu=SERBEST;

//fonksiyon prototipleri
char tustakimi_oku(void);
char buton_kontrol(void);
