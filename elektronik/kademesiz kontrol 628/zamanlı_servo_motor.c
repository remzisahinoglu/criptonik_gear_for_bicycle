/*
Project : servo kontrol
Version : 1.0
Date    : 12.03.2011
Author  : Remzi ÞAHÝNOÐLU
Comment : servo motor kullanýmýný ogrenmek

periyod 20ms, duty 600us ile 2000us arasýnda deðiþebilir.

duty    konum (derece)
----    -----
600us   -90
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

char i=0;

void main()
{

   set_tris_a (0x03);
   set_tris_b (0x00);
   output_b(0);

   
   while(TRUE)
   {
      while(i<100)      // center
      {
         output_high(PIN_B3);
         delay_us(1500);
         output_low(PIN_B3);
         delay_us(18500);
         i++;
      }
      i=0;
      while(i<100)      // 30 degree left
      {
         output_high(PIN_B3);
         delay_us(1333);
         output_low(PIN_B3);
         delay_us(18667);
         i++;
      }
      i=0;
      while(i<100)      // 30 degree right
      {
         output_high(PIN_B3);
         delay_us(1667);
         output_low(PIN_B3);
         delay_us(18333);
         i++;
      }
      i=0;
      while(i<100)      // 45 degree left
      {
         output_high(PIN_B3);
         delay_us(1250);
         output_low(PIN_B3);
         delay_us(18750);
         i++;
      }
      i=0;
      while(i<100)      // 45 degree right
      {
         output_high(PIN_B3);
         delay_us(1750);
         output_low(PIN_B3);
         delay_us(18250);
         i++;
      }
      i=0;
      while(i<100)      // 60 degree left
      {
         output_high(PIN_B3);
         delay_us(1167);
         output_low(PIN_B3);
         delay_us(18833);
         i++;
      }
      i=0;
      while(i<100)      // 60 degree right
      {
         output_high(PIN_B3);
         delay_us(1833);
         output_low(PIN_B3);
         delay_us(18167);
         i++;
      }
      i=0;
   }  
}
