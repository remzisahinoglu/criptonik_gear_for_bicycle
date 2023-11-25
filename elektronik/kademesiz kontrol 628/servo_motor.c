/*
Project : servo kontrol buton ile bisiklet projesi
Version : 1.0
Date    : 24.09.2012
Author  : Remzi �AH�NO�LU
Comment : servo motor kullan�m�n� ogrenmek

periyod 20ms, duty 600us ile 2000us aras�nda de�i�ebilir.

long t�r�ndeki bir de�er ile �arpma i�lemi yap�l�rken sadece long t�r�ndeki bir de�er kullan�labilir.*****

duty    konum (derece)
----    -----
1000us  -90
1500us  0
2000us  +90

*/

#if defined (__PCM__)
#include <16F628A.h> 
#use delay(clock=4000000)
#fuses NOWDT,PUT,NOLVP,NOBROWNOUT,NOMCLR,INTRC_IO,NOPROTECT
#endif

#byte PORTB = 0x06
#byte PORTA = 0x05


signed long long periyod, doluluk, bosluk;     // periyod degeri 255 den b�y�k olduug i�in log olarak tan�mland�



void ee_write_long(unsigned int addr , signed long long *longptr)
{
unsigned char edata;
unsigned char I;
    for(I=0;I<4;I++){
      edata = *((unsigned char *)longptr+I);
      write_eeprom(addr+I,edata);
   }
}

void ee_read_long(unsigned int addr , signed long long *longptr)
{
unsigned char edata;
unsigned char I;
   for(I=0;I<4;I++){
      edata=read_eeprom(I+addr);   
        *((unsigned char *)longptr+I) = edata;
   }
}

void main()
{
   output_b(0);
                                              // pwm periyodu = 20ms olarak ayarlad�k fakat d�ng� i�inde i�lemler oldu�u i�in
   periyod = 19600;                           // periyod 20ms i a��yor. deneme yan�lma y�ntemi ile 20ms olmas� i�in bu de�er girildi
   doluluk = 1850;                            // doluluk oran�n� ilk olarak 1.viteste olmas� i�in 1.85ms olarak ayarland�
   bosluk = periyod - doluluk;                // bo�lu�u hesapla ilk enerji verildi�inde sorun ��kmas�n

   ee_read_long(0x01, &doluluk);
   bosluk = periyod - doluluk;

   while(TRUE)
   {
      if(bit_test(PORTA,0)==0)                      // vites d���r
      {
         delay_ms(25);                              // ark s�nd�r
         doluluk = doluluk + 50;                    // de�er kadar art
         if(doluluk > 1900){doluluk = 1900;}        // �st s�n�rda kal
         bosluk = periyod - doluluk;                // bosluk s�resini ayarla
         ee_write_long(0x01, &doluluk);
      }   

      if(bit_test(PORTA,1)==0)                      // vites artt�r
      {
         delay_ms(25);
         
         doluluk = doluluk - 50;                    // de�er kadar azal
         if(doluluk < 850){doluluk = 820;}          // alt s�n�rda kal
         bosluk = periyod - doluluk;                // bosluk s�resini ayarla 
         ee_write_long(0x01, &doluluk);
      }   
         
      // periyod
      output_high(PIN_B3);                          // PWM ��k�� PORTB nin 4. bitinden (RB3)
      delay_us(doluluk);                                           
      output_low(PIN_B3);
      delay_us(bosluk);                                                
                                                            
   }
}
