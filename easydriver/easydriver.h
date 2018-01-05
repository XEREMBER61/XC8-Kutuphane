/*******************************************************************************
 * K�t�phane     : Easydriver Ad�m motor k�t�phanesi                           *
 * Yazar         : sigmoid                                                     *
 * Web           : http://www.gencmucitler.com                                 *
 * Ba�lang��     : 4 Ocak 2018                                                 *
 * Versiyon      : 0.2                                                         *
 *                                                                             *
 ******************************************************************************/

//pin tan�mlamalar�
#define step_DIR   LATB0
#define step_PULSE LATB1

//motor 360 derecelik tam turunu ka� ad�mda tamaml�yor8�
#define motorAdimi  1600

//motor y�n�
#define saatYonunde     0
#define saatTersYonunde 1
#define CW              0
#define CCW             1

//H�z ayarlar� - Hz olarak girilmeli
#define _maksimum_hiz    16000  //1 saniyedeki maksimum ad�m say�s� 
#define _minumum_hiz     800    //1 saniyedeki minumum ad�m say�s� 
#define _hizlanmaadimi   4    //ka� adim da bir h�zlanacak
#define _yavaslamaadimi  10    //ka� adim da bir yava�layacak

#define _sure          100000UL

#define C 3.141592/180.0

void adimMotor(unsigned int adimSayisi,char adimYonu);
void adimMotorDerece(unsigned int adimDerece,char adimYonu);
void step_bekle(unsigned int sure);
