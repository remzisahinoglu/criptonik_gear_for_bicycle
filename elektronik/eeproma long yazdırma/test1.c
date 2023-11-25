/*
Project : servo kontrol buton ile bisiklet projesi
Version : 1.0
Date    : 24.09.2012
Author  : Remzi ÞAHÝNOÐLU
Comment : servo motor kullanýmýný ogrenmek

periyod 20ms, duty 600us ile 2000us arasýnda deðiþebilir.

long türündeki bir deðer ile çarpma iþlemi yapýlýrken sadece long türündeki bir deðer kullanýlabilir.*****

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


signed long long periyod, doluluk, bosluk;     // periyod degeri 255 den büyük olduug için log olarak tanýmlandý



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
                                              // pwm periyodu = 20ms olarak ayarladýk fakat döngü içinde iþlemler olduðu için
   periyod = 19600;                           // periyod 20ms i aþýyor. deneme yanýlma yöntemi ile 20ms olmasý için bu deðer girildi
   doluluk = 1850;                            // doluluk oranýný ilk olarak 1.viteste olmasý için 1.85ms olarak ayarlandý
   bosluk = periyod - doluluk;                // boþluðu hesapla ilk enerji verildiðinde sorun çýkmasýn

   ee_read_long(0x01, &doluluk);
   bosluk = periyod - doluluk;

   while(TRUE)
   {
      if(bit_test(PORTA,0)==0)                      // vites düþür
      {
         delay_ms(25);                              // ark söndür
         doluluk = doluluk + 50;                    // deðer kadar art
         if(doluluk > 1900){doluluk = 1900;}        // üst sýnýrda kal
         bosluk = periyod - doluluk;                // bosluk süresini ayarla
         ee_write_long(0x01, &doluluk);
      }   

      if(bit_test(PORTA,1)==0)                      // vites arttýr
      {
         delay_ms(25);
         
         doluluk = doluluk - 50;                    // deðer kadar azal
         if(doluluk < 850){doluluk = 820;}          // alt sýnýrda kal
         bosluk = periyod - doluluk;                // bosluk süresini ayarla 
         ee_write_long(0x01, &doluluk);
      }   
         
      // periyod
      output_high(PIN_B3);                          // PWM çýkýþ PORTB nin 4. bitinden (RB3)
      delay_us(doluluk);                                           
      output_low(PIN_B3);
      delay_us(bosluk);                                                
                                                            
   }
}
