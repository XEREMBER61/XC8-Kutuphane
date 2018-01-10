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

#define SATIR1  LATCbits.LATC7        //sat�rlar
#define SATIR2  LATDbits.LATD4
#define SATIR3  LATDbits.LATD5
#define SATIR4  LATDbits.LATD6
#define SATIR5  LATDbits.LATD7

#define SUTUN1  PORTBbits.RB3        //s�tunlar
#define SUTUN2  PORTBbits.RB2
#define SUTUN3  PORTBbits.RB1
#define SUTUN4  PORTBbits.RB0


// tu� tak�m� patterni
const char tuslar[]={   'Q','W','#','*',    //F1   F2  #    *   
                        '1','2','3','Y',    //1    2   3     Yukar�
                        '4','5','6','A',    //4    5   6     A�a��
                        '7','8','9','C',    //7    8   9     ��k�� /ESC
                        'L','0','R','G'     //Left 0   Right Giri�/Enter
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
