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

#include "mcc_generated_files/mcc.h"
#include "pcf8574.h"


void pcf8574_yaz(char veri) {

    I2C1_MESSAGE_STATUS status;
    uint8_t writeBuffer[1];
    uint16_t timeOut;

    writeBuffer[0] = veri;
    timeOut = 0;
    while (status != I2C1_MESSAGE_FAIL) {
        
        //1 byte g�nder
        I2C1_MasterWrite(writeBuffer,
                1,
                pcf_adres,
                &status);

        // veri g�nderilene kadar bekle.
        while (status == I2C1_MESSAGE_PENDING);

        //ba�ar�l� olarak g�nderildi isi ��k
        if (status == I2C1_MESSAGE_COMPLETE)
            break;

        //Veri g�nderilmediyse tekrar g�nder.
        //Ba�ar�s�z tekrar say�s�na ula��ld�ysa da ��k.
        if (timeOut == pcf_tekrar)
            break;
        else
            timeOut++;
    }

}

