#include <LedControl.h>  

 int DIN = 12;  
 int CS = 11;  
 int CLK = 10;  

 LedControl lc=LedControl(DIN,CLK,CS,0);  

 void setup(){  
  lc.shutdown(0,false);      
  lc.setIntensity(0,7);   //Adjust the brightness maximum is 15  
  lc.clearDisplay(0);    
 }  
 void loop(){   
   //Facial Expression  
   byte smile[8]=  {0x3C,0x42,0xA5,0x81,0xA5,0x99,0x42,0x3C};  
   byte neutral[8]= {0x3C,0x42,0xA5,0x81,0xBD,0x81,0x42,0x3C};  
   byte sad[8]=  {0x3C,0x42,0xA5,0x81,0x99,0xA5,0x42,0x3C}; 
   byte heart_shape_1[8]={  B01100110,  B11111111,  B11111111,  B11111111,  B01111110,  B00111100,  B00011000,  B00000000};
   byte heart_shape_2[8] = {0x60, 0x90, 0x88, 0x44, 0x44, 0x88, 0x90, 0x60};

 //Facial Expression    
   printByte(smile);  
   delay(1000);  
   printByte(neutral);  
   delay(1000);  
   printByte(sad);    
   delay(1000);  
  printByte(heart_shape_1);    
   delay(1000);
  printByte(heart_shape_2);    
   delay(1000);
 }  

 void printByte(byte character [])  
 {  
  int i = 0;  
  for(i=0;i<8;i++)  
  {  
   lc.setRow(0,i,character[i]);  
  }  
 }  
