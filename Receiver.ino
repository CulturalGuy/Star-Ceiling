/* ----- RECEIVER ----- */


unsigned long previousMillis = 0;        // will store last time LED was updated
const long interval = 1000;           // interval at which to blink (milliseconds)

int brightness1 = 4;
int brightness2 = 4;
int brightness3 = 4;


//______________PCA9685_______________________
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>


// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm1 = Adafruit_PWMServoDriver(0x40);
Adafruit_PWMServoDriver pwm2 = Adafruit_PWMServoDriver(0x41);
Adafruit_PWMServoDriver pwm3 = Adafruit_PWMServoDriver(0x42);
Adafruit_PWMServoDriver pwm4 = Adafruit_PWMServoDriver(0x43);
Adafruit_PWMServoDriver pwm5 = Adafruit_PWMServoDriver(0x44); 

//______________General variables_______________________

long Rvalue1, Gvalue1, Bvalue1;  
long Rvalue2, Gvalue2, Bvalue2; 
long Rvalue3, Gvalue3, Bvalue3;   
long Rvalue4, Gvalue4, Bvalue4;
long Rvalue5, Gvalue5, Bvalue5;  
long Rvalue6, Gvalue6, Bvalue6;  
long Rvalue7, Gvalue7, Bvalue7;  
long Rvalue8, Gvalue8, Bvalue8;  

long Bclass1, Gclass1, Rclass1;  
long Bclass2, Gclass2, Rclass2; 
long Bclass3, Gclass3, Rclass3; 
long Bclass4, Gclass4, Rclass4; 
long Bclass5, Gclass5, Rclass5; 


/*-----( NRF24L01 )-----*/
/*-----( Import needed libraries )-----*/
#include <SPI.h>   // Comes with Arduino IDE
#include "RF24.h"  // Download and Install (See above)
#include "printf.h" // Needed for "printDetails" Takes up some memory

/*-----( Declare Constants and Pin Numbers )-----*/
#define  CE_PIN  9   // The pins to be used for CE and SN
#define  CSN_PIN 7

/* NRF24L01 PINS:
  VCC  -> 3.3V
  CSN  -> 7
  MOSI -> 51
  IRQ  -> X
  CE   -> 9
  SCK  -> 52
  MISO -> 50
*/

/*-----( Declare objects )-----*/
/* Hardware configuration: Set up nRF24L01 radio on SPI bus plus (usually) pins 7 & 8 (Can be changed) */
RF24 radio(CE_PIN, CSN_PIN);

/*-----( Declare Variables )-----*/
byte addresses[][6] = {"1Node", "2Node"}; // These will be the names of the "Pipes"

struct dataStruct {

int IRcode; 
int red;
int green;
int blue; 
int spectrumRight1;
int spectrumRight2;
int spectrumRight3;
int spectrumRight4;
int spectrumRight5;
int spectrumRight6;
int spectrumRight7;

} myData;               


// defining the avaialble colors one by one
int BLACK_COLOR[3] = {0, 0, 0};
int RED_COLOR[3] = {255, 0, 0};
int GREEN_COLOR[3] = {0, 255, 0};
int BLUE_COLOR[3] =  {0, 0, 255};
int WHITE_COLOR[3] = {255, 255, 255};
int ORANGE_COLOR[3] = {30, 15, 0};
int TURQUOISE_COLOR[3] = {0, 255, 128};
int NAVY_COLOR[3] = {0, 76, 153};
int BROWN_COLOR[3] = {153, 76, 0};
int TEAL_COLOR[3] = {0, 30, 30};
int PURPLE_DARK_COLOR[3] = {30, 0, 15};
int ORANGE_LIGHT_COLOR[3] = {255, 153, 51};
int BLUE_LIGHT_COLOR[3] = {0, 255, 255};
int PINK_DARK_COLOR[3] = {255, 0, 128};
int YELLOW_COLOR[3] = {30, 30, 0};
int BLUE_BABY_COLOR[3] = {51, 153, 255};
int PINK_COLOR[3] = {255, 102, 178};

// defining all the available colors in an array
int AVAILABLE_COLORS[16][3] = {{255, 0, 0}, {0, 255, 0}, {0, 0, 255}, {255, 255, 255}, {255, 128, 0}, {0, 255, 128}, {0, 76, 153}, {153, 76, 0}, {0, 102, 102}, {102, 0, 51}, {255, 153, 51}, {0, 255, 255}, {255, 0, 127}, {255, 255, 0}, {51, 153, 255}, {255, 102, 158}} ;


void setup() {
//Serial.begin(9600);
//______________PCA9685_______________________
  pwm1.begin();
  pwm1.setPWMFreq(200);  // This is the maximum PWM frequency
  
  pwm2.begin();
  pwm2.setPWMFreq(200);  // maximum PWM frequency - (1600 ar 1000)

  pwm3.begin();
  pwm3.setPWMFreq(200);  // maximum PWM frequency - (1600 ar 1000)

  pwm4.begin();
  pwm4.setPWMFreq(200);  // maximum PWM frequency - (1600 ar 1000)

  pwm5.begin();
  pwm5.setPWMFreq(200);  // maximum PWM frequency - (1600 ar 1000)

         pwm1.setPWM(0, 0, 0);  
         pwm1.setPWM(1, 0, 0); 
         pwm1.setPWM(2, 0, 0);
         pwm1.setPWM(3, 0, 0);  
         pwm1.setPWM(4, 0, 0); 
         pwm1.setPWM(5, 0, 0);       
         pwm1.setPWM(6, 0, 0);
         pwm1.setPWM(7, 0, 0);
         pwm1.setPWM(8, 0, 0);
         pwm1.setPWM(9, 0, 0);
         pwm1.setPWM(10, 0, 0);
         pwm1.setPWM(11, 0, 0);
         pwm1.setPWM(12, 0, 0);
         pwm1.setPWM(13, 0, 0);
         pwm1.setPWM(14, 0, 0);
         pwm1.setPWM(15, 0, 0);  

         pwm2.setPWM(0, 0, 0);  
         pwm2.setPWM(1, 0, 0); 
         pwm2.setPWM(2, 0, 0);
         pwm2.setPWM(3, 0, 0);  
         pwm2.setPWM(4, 0, 0); 
         pwm2.setPWM(5, 0, 0);       
         pwm2.setPWM(6, 0, 0);
         pwm2.setPWM(7, 0, 0);
         pwm2.setPWM(8, 0, 0);
         pwm2.setPWM(9, 0, 0);
         pwm2.setPWM(10, 0, 0);
         pwm2.setPWM(11, 0, 0);
         pwm2.setPWM(12, 0, 0);
         pwm2.setPWM(13, 0, 0);
         pwm2.setPWM(14, 0, 0);
         pwm2.setPWM(15, 0, 0);  

         pwm3.setPWM(0, 0, 0);  
         pwm3.setPWM(1, 0, 0); 
         pwm3.setPWM(2, 0, 0);
         pwm3.setPWM(3, 0, 0);  
         pwm3.setPWM(4, 0, 0); 
         pwm3.setPWM(5, 0, 0);       
         pwm3.setPWM(6, 0, 0);
         pwm3.setPWM(7, 0, 0);
         pwm3.setPWM(8, 0, 0);
         pwm3.setPWM(9, 0, 0);
         pwm3.setPWM(10, 0, 0);
         pwm3.setPWM(11, 0, 0);
         pwm3.setPWM(12, 0, 0);
         pwm3.setPWM(13, 0, 0);
         pwm3.setPWM(14, 0, 0);
         pwm3.setPWM(15, 0, 0);  
      
         pwm4.setPWM(0, 0, 0);  
         pwm4.setPWM(1, 0, 0); 
         pwm4.setPWM(2, 0, 0);
         pwm4.setPWM(3, 0, 0);  
         pwm4.setPWM(4, 0, 0); 
         pwm4.setPWM(5, 0, 0);       
         pwm4.setPWM(6, 0, 0);
         pwm4.setPWM(7, 0, 0);
         pwm4.setPWM(8, 0, 0);
         pwm4.setPWM(9, 0, 0);
         pwm4.setPWM(10, 0, 0);
         pwm4.setPWM(11, 0, 0);
         pwm4.setPWM(12, 0, 0);
         pwm4.setPWM(13, 0, 0);
         pwm4.setPWM(14, 0, 0);
         pwm4.setPWM(15, 0, 0);    
        
         pwm5.setPWM(0, 0, 0);  
         pwm5.setPWM(1, 0, 0); 
         pwm5.setPWM(2, 0, 0);
         pwm5.setPWM(3, 0, 0);
         pwm5.setPWM(4, 0, 0);  
         pwm5.setPWM(5, 0, 0); 
         pwm5.setPWM(6, 0, 0);
         pwm5.setPWM(7, 0, 0);
         pwm5.setPWM(8, 0, 0);  
         pwm5.setPWM(9, 0, 0); 
         pwm5.setPWM(10, 0, 0);
         pwm5.setPWM(11, 0, 0);
         pwm5.setPWM(12, 0, 0);  
         pwm5.setPWM(13, 0, 0); 
         pwm5.setPWM(14, 0, 0);
         pwm5.setPWM(15, 0, 0); 
            
  /*-----( NRF24L01 )-----*/
  radio.begin();          // Initialize the nRF24L01 Radio
  radio.setChannel(108);  // 2.508 Ghz - Above most Wifi Channels
  radio.setDataRate(RF24_250KBPS); // Fast enough.. Better range

  // Set the Power Amplifier Level low to prevent power supply related issues since this is a
  // getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.
  // PALevelcan be one of four levels: RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH and RF24_PA_MAX
  radio.setPALevel(RF24_PA_LOW);
  //   radio.setPALevel(RF24_PA_MAX);

  // Open a writing and reading pipe on each radio, with opposite addresses
  radio.openWritingPipe(addresses[1]);
  radio.openReadingPipe(1, addresses[0]);

  // Start the radio listening for data
  radio.startListening();

}

void loop() {


  if ( radio.available())
 
  {
    while (radio.available())   // While there is data ready to be retrieved from the receive pipe
    {
      radio.read( &myData, sizeof(myData) );             // Get the data
/*
Serial.print(myData.IRcode);
Serial.print(" ");
Serial.print(myData.red);
Serial.print(" ");
Serial.print(myData.green);
Serial.print(" ");
Serial.print(myData.blue);
Serial.print(" ");
    Serial.print(myData.spectrumRight1  );
    Serial.print(" ");
    Serial.print(myData.spectrumRight2  );
    Serial.print(" ");
    Serial.print(myData.spectrumRight3  );
    Serial.print(" ");
    Serial.print(myData.spectrumRight4  );
    Serial.print(" ");
    Serial.print(myData.spectrumRight5  );
    Serial.print(" ");
    Serial.print(myData.spectrumRight6  );
    Serial.print(" ");
    Serial.println(myData.spectrumRight7);
*/

    }
  } // END radio available
  


  switch (myData.IRcode){


case 0xB08CB7DF:
//GREEN_CODE 
         pwm5.setPWM(8, 0, 0);  
         pwm5.setPWM(9, 0, 3); 
         pwm5.setPWM(10, 0, 6); 
               
         pwm5.setPWM(12, 0, 0);  
         pwm5.setPWM(13, 0, 3); 
         pwm5.setPWM(14, 0, 6);
         
sky2_1();

    break;

case 0x8503705D:
//INTENSITY_UP_CODE 
    break;
    
case 0xDEB0C861:
//INTENSITY_DN_CODE 
    break;
    
case 0xD4DD0381:
//ON_CODE  
//Išjungiam dangų 
 
    break;

    
case 0xCE1972FD:
//OFF_CODE  

         pwm1.setPWM(0, 0, 0);  
         pwm1.setPWM(1, 0, 0); 
         pwm1.setPWM(2, 0, 0);
         pwm1.setPWM(3, 0, 0);  
         pwm1.setPWM(4, 0, 0); 
         pwm1.setPWM(5, 0, 0);       
         pwm1.setPWM(6, 0, 0);
         pwm1.setPWM(7, 0, 0);
         pwm1.setPWM(8, 0, 0);
         pwm1.setPWM(9, 0, 0);
         pwm1.setPWM(10, 0, 0);
         pwm1.setPWM(11, 0, 0);
         pwm1.setPWM(12, 0, 0);
         pwm1.setPWM(13, 0, 0);
         pwm1.setPWM(14, 0, 0);
         pwm1.setPWM(15, 0, 0);  

         pwm2.setPWM(0, 0, 0);  
         pwm2.setPWM(1, 0, 0); 
         pwm2.setPWM(2, 0, 0);
         pwm2.setPWM(3, 0, 0);  
         pwm2.setPWM(4, 0, 0); 
         pwm2.setPWM(5, 0, 0);       
         pwm2.setPWM(6, 0, 0);
         pwm2.setPWM(7, 0, 0);
         pwm2.setPWM(8, 0, 0);
         pwm2.setPWM(9, 0, 0);
         pwm2.setPWM(10, 0, 0);
         pwm2.setPWM(11, 0, 0);
         pwm2.setPWM(12, 0, 0);
         pwm2.setPWM(13, 0, 0);
         pwm2.setPWM(14, 0, 0);
         pwm2.setPWM(15, 0, 0);  

         pwm3.setPWM(0, 0, 0);  
         pwm3.setPWM(1, 0, 0); 
         pwm3.setPWM(2, 0, 0);
         pwm3.setPWM(3, 0, 0);  
         pwm3.setPWM(4, 0, 0); 
         pwm3.setPWM(5, 0, 0);       
         pwm3.setPWM(6, 0, 0);
         pwm3.setPWM(7, 0, 0);
         pwm3.setPWM(8, 0, 0);
         pwm3.setPWM(9, 0, 0);
         pwm3.setPWM(10, 0, 0);
         pwm3.setPWM(11, 0, 0);
         pwm3.setPWM(12, 0, 0);
         pwm3.setPWM(13, 0, 0);
         pwm3.setPWM(14, 0, 0);
         pwm3.setPWM(15, 0, 0);  
      
         pwm4.setPWM(0, 0, 0);  
         pwm4.setPWM(1, 0, 0); 
         pwm4.setPWM(2, 0, 0);
         pwm4.setPWM(3, 0, 0);  
         pwm4.setPWM(4, 0, 0); 
         pwm4.setPWM(5, 0, 0);       
         pwm4.setPWM(6, 0, 0);
         pwm4.setPWM(7, 0, 0);
         pwm4.setPWM(8, 0, 0);
         pwm4.setPWM(9, 0, 0);
         pwm4.setPWM(10, 0, 0);
         pwm4.setPWM(11, 0, 0);
         pwm4.setPWM(12, 0, 0);
         pwm4.setPWM(13, 0, 0);
         pwm4.setPWM(14, 0, 0);
         pwm4.setPWM(15, 0, 0);    
        
         pwm5.setPWM(0, 0, 0);  
         pwm5.setPWM(1, 0, 0); 
         pwm5.setPWM(2, 0, 0);
         pwm5.setPWM(3, 0, 0);
         pwm5.setPWM(4, 0, 0);  
         pwm5.setPWM(5, 0, 0); 
         pwm5.setPWM(6, 0, 0);
         pwm5.setPWM(7, 0, 0);
         pwm5.setPWM(8, 0, 0);  
         pwm5.setPWM(9, 0, 0); 
         pwm5.setPWM(10, 0, 0);
         pwm5.setPWM(11, 0, 0);
         pwm5.setPWM(12, 0, 0);  
         pwm5.setPWM(13, 0, 0); 
         pwm5.setPWM(14, 0, 0);
         pwm5.setPWM(15, 0, 0); 
     
    break;
    
case 0xE85952E1:
//RED_CODE 
sky1();
    break;
    
case 0x78CDA4DD:
//GREEN_CODE 
sky2();
    break;
    
case 0xA2672345:
//BLUE_CODE 
constellations1();
    break;
    
case 0x9BA392C1:
//WHITE_CODE 
constellations2();
    break;
    
case 0xD3FD9A81:
//ORANGE_CODE 
RGBSTRIP();
    break;
    
case 0x6471EC7D:
//YELLOW_CODE 
RGBSTRIP();
    break;
    
case 0x9D52009D:
//TEAL_CODE 
RGBSTRIP();
    break;
    
case 0xDCC45BE1:
//PINK_DARK_CODE     
RGBSTRIP();
    break;
    
case 0x84044BBD:
//STROBE_CODE 
RGBSTRIP();
    break;
    
case 0x14789DB9:
//SMOOTH_CODE 
RGBSTRIP();
    break;

case 0x3E121C21:
//FADE_CODE 
RGBSTRIP();
    break;
   
case 0x374E8B9D:
//FLASH_CODE 
RGBSTRIP();
    break;

    
case 0xB0F9B3E1:
//MUSIC_CODE 
RGBnSTAR1();
    break;

case 0x416E05DD:
//MUSIC2_CODE2 
RGBnSTAR2();  
    break;
    
case 0x6A844445:
//MUSIC3_CODE3 
RGBnSTAR3();
    break;
    
case 0xB9C07541:
//MUSIC4_CODE4 
RGBnSTAR4();
    break;
  
  }
}   
   
   void RGBSTRIP() {
 
         pwm1.setPWM(0, 0, 0);  
         pwm1.setPWM(1, 0, 0); 
         pwm1.setPWM(2, 0, 0);
         pwm1.setPWM(3, 0, 0);  
         pwm1.setPWM(4, 0, 0); 
         pwm1.setPWM(5, 0, 0);       
         pwm1.setPWM(6, 0, 0);
         pwm1.setPWM(7, 0, 0);
         pwm1.setPWM(8, 0, 0);
         pwm1.setPWM(9, 0, 0);
         pwm1.setPWM(10, 0, 0);
         pwm1.setPWM(11, 0, 0);
         pwm1.setPWM(12, 0, 0);
         pwm1.setPWM(13, 0, 0);
         pwm1.setPWM(14, 0, 0);
         pwm1.setPWM(15, 0, 0);  

         pwm2.setPWM(0, 0, 0);  
         pwm2.setPWM(1, 0, 0); 
         pwm2.setPWM(2, 0, 0);
         pwm2.setPWM(3, 0, 0);  
         pwm2.setPWM(4, 0, 0); 
         pwm2.setPWM(5, 0, 0);       
         pwm2.setPWM(6, 0, 0);
         pwm2.setPWM(7, 0, 0);
         pwm2.setPWM(8, 0, 0);
         pwm2.setPWM(9, 0, 0);
         pwm2.setPWM(10, 0, 0);
         pwm2.setPWM(11, 0, 0);
         pwm2.setPWM(12, 0, 0);
         pwm2.setPWM(13, 0, 0);
         pwm2.setPWM(14, 0, 0);
         pwm2.setPWM(15, 0, 0);  

         pwm3.setPWM(0, 0, 0);  
         pwm3.setPWM(1, 0, 0); 
         pwm3.setPWM(2, 0, 0);
         pwm3.setPWM(3, 0, 0);  
         pwm3.setPWM(4, 0, 0); 
         pwm3.setPWM(5, 0, 0);       
         pwm3.setPWM(6, 0, 0);
         pwm3.setPWM(7, 0, 0);
         pwm3.setPWM(8, 0, 0);
         pwm3.setPWM(9, 0, 0);
         pwm3.setPWM(10, 0, 0);
         pwm3.setPWM(11, 0, 0);
         pwm3.setPWM(12, 0, 0);
         pwm3.setPWM(13, 0, 0);
         pwm3.setPWM(14, 0, 0);
         pwm3.setPWM(15, 0, 0);  
      
         pwm4.setPWM(0, 0, 0);  
         pwm4.setPWM(1, 0, 0); 
         pwm4.setPWM(2, 0, 0);
         pwm4.setPWM(3, 0, 0);  
         pwm4.setPWM(4, 0, 0); 
         pwm4.setPWM(5, 0, 0);       
         pwm4.setPWM(6, 0, 0);
         pwm4.setPWM(7, 0, 0);
         pwm4.setPWM(8, 0, 0);
         pwm4.setPWM(9, 0, 0);
         pwm4.setPWM(10, 0, 0);
         pwm4.setPWM(11, 0, 0);
         pwm4.setPWM(12, 0, 0);
         pwm4.setPWM(13, 0, 0);
         pwm4.setPWM(14, 0, 0);
         pwm4.setPWM(15, 0, 0);      
         
         pwm5.setPWM(8, 0, myData.red*15);  
         pwm5.setPWM(9, 0, myData.green*15); 
         pwm5.setPWM(10, 0, myData.blue*15); 
               
         pwm5.setPWM(12, 0, myData.red*15);  
         pwm5.setPWM(13, 0, myData.green*15); 
         pwm5.setPWM(14, 0, myData.blue*15);
      
    }


  void RGBnSTAR1() {
   
    int Mblue = (10);
    int Mgreen = (0);
    int Mred = (20 + myData.spectrumRight1 / 30);      

         
         pwm5.setPWM(8, 0, Mblue);  
         pwm5.setPWM(9, 0, Mgreen); 
         pwm5.setPWM(10, 0, Mred); 
               
         pwm5.setPWM(12, 0, Mblue);  
         pwm5.setPWM(13, 0, Mgreen); 
         pwm5.setPWM(14, 0, Mred);


    int Spek1 = 4*myData.spectrumRight1^2 / 1024^2 / 1024;
      if (Spek1 > 3500) 
  {
    Spek1 = 3500;
  }


    int Spek2 = 4*myData.spectrumRight2^2 / 1024^2 / 1024;
          if (Spek2 > 3500) 
  {
    Spek2 = 3500;
  }

    int Spek3 = 4*myData.spectrumRight3^2 / 1024^2 / 1024;
          if (Spek3 > 3500) 
  {
    Spek3 = 3500;
  }

    int Spek4 = 4*myData.spectrumRight4^2 / 1024^2 / 1024;
          if (Spek4 > 3500) 
  {
    Spek4 = 3500;
  }
 
    int Spek5 = 4*myData.spectrumRight5^2 / 1024^2 / 1024;
          if (Spek5 > 3500) 
  {
    Spek5 = 3500;
  }

    int Spek6 = 4*myData.spectrumRight6^2 / 1024^2 / 1024;
          if (Spek6 > 3800) 
  {
    Spek6 = 3800;
  }
 
    int Spek7 = 4*myData.spectrumRight7^2 / 1024^2 / 1024;
          if (Spek7 > 3800) 
  {
    Spek7 = 3800;
  }

        

         pwm1.setPWM(0, 0, Spek5);  
         pwm1.setPWM(1, 0, 0); 
         pwm1.setPWM(2, 0, Spek3);
         //pwm1.setPWM(3, 0, 0);  
         pwm1.setPWM(4, 0, 0); 
         pwm1.setPWM(5, 0, 0);       
         pwm1.setPWM(6, 0, Spek2);
         //pwm1.setPWM(7, 0, 0);
    //     pwm1.setPWM(8, 0, 0);
    //     pwm1.setPWM(9, 0, Spek2/2);
    //     pwm1.setPWM(10, 0, Spek2);
         //pwm1.setPWM(11, 0, 0);
         pwm1.setPWM(12, 0, Spek5);
         pwm1.setPWM(13, 0, 0);
         pwm1.setPWM(14, 0, Spek3);
         //pwm1.setPWM(15, 0, 0);  

         pwm2.setPWM(0, 0, Spek6);  
         pwm2.setPWM(1, 0, Spek7/2); 
         pwm2.setPWM(2, 0, Spek7/2);
         //pwm2.setPWM(3, 0, 0);  
         pwm2.setPWM(4, 0, Spek6); 
         pwm2.setPWM(5, 0, Spek7/2);       
         pwm2.setPWM(6, 0, Spek7/2);
         //pwm2.setPWM(7, 0, 0);
         pwm2.setPWM(8, 0, Spek7);
         pwm2.setPWM(9, 0, Spek7);
         pwm2.setPWM(10, 0, Spek7);
        //pwm2.setPWM(11, 0, 0);
    //     pwm2.setPWM(12, 0, 0);
    //     pwm2.setPWM(13, 0, 0);
    //     pwm2.setPWM(14, 0, Spek1);
         //pwm2.setPWM(15, 0, 0);  

         pwm3.setPWM(0, 0, 0);  
         pwm3.setPWM(1, 0, Spek2); 
         pwm3.setPWM(2, 0, Spek2);
         //pwm3.setPWM(3, 0, 0);  
         pwm3.setPWM(4, 0, 0); 
         pwm3.setPWM(5, 0, Spek2);       
         pwm3.setPWM(6, 0, Spek2);
         //pwm3.setPWM(7, 0, 0);
         pwm3.setPWM(8, 0, Spek4);
         pwm3.setPWM(9, 0, 0);
         pwm3.setPWM(10, 0, Spek3);
         //pwm3.setPWM(11, 0, 0);
         pwm3.setPWM(12, 0, Spek4);
         pwm3.setPWM(13, 0, 0);
         pwm3.setPWM(14, 0, Spek3);
         //pwm3.setPWM(15, 0, 0);  
      
         pwm4.setPWM(0, 0, Spek4);  
         pwm4.setPWM(1, 0, 0); 
         pwm4.setPWM(2, 0, Spek4);
         //pwm4.setPWM(3, 0, 0);  
         pwm4.setPWM(4, 0, 0); 
         pwm4.setPWM(5, 0, Spek2/2);       
         pwm4.setPWM(6, 0, Spek2);
         //pwm4.setPWM(7, 0, 0);
         pwm4.setPWM(8, 0, 0);
         pwm4.setPWM(9, 0, Spek2/2);
         pwm4.setPWM(10, 0, Spek2);
         //pwm4.setPWM(11, 0, 0);
    //     pwm4.setPWM(12, 0, 0);
    //     pwm4.setPWM(13, 0, Spek2/2);
    //     pwm4.setPWM(14, 0, Spek2);
         //pwm4.setPWM(15, 0, 0);  

    }


    void RGBnSTAR2() {
   
   
    int Mblue = (20 + myData.spectrumRight2 / 30);
    int Mgreen = (20 + myData.spectrumRight1 / 30);
    int Mred = (0);      

         
         pwm5.setPWM(8, 0, Mblue);  
         pwm5.setPWM(9, 0, Mgreen); 
         pwm5.setPWM(10, 0, Mred); 
               
         pwm5.setPWM(12, 0, Mblue);  
         pwm5.setPWM(13, 0, Mgreen); 
         pwm5.setPWM(14, 0, Mred);


    int Spek1 = 4*myData.spectrumRight1^2 / 1024^2 / 1024;
      if (Spek1 > 3500) 
  {
    Spek1 = 3500;
  }


    int Spek2 = 4*myData.spectrumRight2^2 / 1024^2 / 1024;
          if (Spek2 > 3500) 
  {
    Spek2 = 3500;
  }

    int Spek3 = 4*myData.spectrumRight3^2 / 1024^2 / 1024;
          if (Spek3 > 3500) 
  {
    Spek3 = 3500;
  }

    int Spek4 = 4*myData.spectrumRight4^2 / 1024^2 / 1024;
          if (Spek4 > 3500) 
  {
    Spek4 = 3500;
  }
 
    int Spek5 = 4*myData.spectrumRight5^2 / 1024^2 / 1024;
          if (Spek5 > 3500) 
  {
    Spek5 = 3500;
  }

    int Spek6 = 4*myData.spectrumRight6^2 / 1024^2 / 1024;
          if (Spek6 > 3800) 
  {
    Spek6 = 3800;
  }
 
    int Spek7 = 4*myData.spectrumRight7^2 / 1024^2 / 1024;
          if (Spek7 > 3800) 
  {
    Spek7 = 3800;
  }



         pwm1.setPWM(0, 0, Spek5);  
         pwm1.setPWM(1, 0, Spek3); 
         pwm1.setPWM(2, 0, 0);
         //pwm1.setPWM(3, 0, 0);  
         pwm1.setPWM(4, 0, Spek2); 
         pwm1.setPWM(5, 0, 0);       
         pwm1.setPWM(6, 0, 0);
         //pwm1.setPWM(7, 0, 0);
    //     pwm1.setPWM(8, 0, 0);
    //     pwm1.setPWM(9, 0, Spek2/2);
    //     pwm1.setPWM(10, 0, Spek2);
         //pwm1.setPWM(11, 0, 0);
         pwm1.setPWM(12, 0, Spek5);
         pwm1.setPWM(13, 0, Spek3);
         pwm1.setPWM(14, 0, 0);
         //pwm1.setPWM(15, 0, 0);  

         pwm2.setPWM(0, 0, 0);  
         pwm2.setPWM(1, 0, 0); 
         pwm2.setPWM(2, 0, Spek6);
         //pwm2.setPWM(3, 0, 0);  
         pwm2.setPWM(4, 0, Spek6/3); 
         pwm2.setPWM(5, 0, Spek7/3);       
         pwm2.setPWM(6, 0, Spek7);
         //pwm2.setPWM(7, 0, 0);
         pwm2.setPWM(8, 0, Spek7/3);
         pwm2.setPWM(9, 0, 0);
         pwm2.setPWM(10, 0, Spek7);
        //pwm2.setPWM(11, 0, 0);
    //     pwm2.setPWM(12, 0, 0);
    //     pwm2.setPWM(13, 0, 0);
    //     pwm2.setPWM(14, 0, Spek1);
         //pwm2.setPWM(15, 0, 0);  

         pwm3.setPWM(0, 0, Spek3);  
         pwm3.setPWM(1, 0, Spek3); 
         pwm3.setPWM(2, 0, Spek3);
         //pwm3.setPWM(3, 0, 0);  
         pwm3.setPWM(4, 0, Spek2); 
         pwm3.setPWM(5, 0, Spek2);       
         pwm3.setPWM(6, 0, 0);
         //pwm3.setPWM(7, 0, 0);
         pwm3.setPWM(8, 0, Spek4);
         pwm3.setPWM(9, 0, 0);
         pwm3.setPWM(10, 0, Spek3);
         //pwm3.setPWM(11, 0, 0);
         pwm3.setPWM(12, 0, Spek4);
         pwm3.setPWM(13, 0, 0);
         pwm3.setPWM(14, 0, Spek3);
         //pwm3.setPWM(15, 0, 0);  
      
         pwm4.setPWM(0, 0, Spek4);  
         pwm4.setPWM(1, 0, 0); 
         pwm4.setPWM(2, 0, Spek4);
         //pwm4.setPWM(3, 0, 0);  
         pwm4.setPWM(4, 0, Spek2); 
         pwm4.setPWM(5, 0, Spek2/2);       
         pwm4.setPWM(6, 0, 0);
         //pwm4.setPWM(7, 0, 0);
         pwm4.setPWM(8, 0, Spek2);
         pwm4.setPWM(9, 0, Spek2/2);
         pwm4.setPWM(10, 0, 0);
         //pwm4.setPWM(11, 0, 0);
    //     pwm4.setPWM(12, 0, 0);
    //     pwm4.setPWM(13, 0, Spek2/2);
    //     pwm4.setPWM(14, 0, Spek2);
         //pwm4.setPWM(15, 0, 0);  


      
    }

   

    void RGBnSTAR3() {
   
    int Mblue = (0);
    int Mgreen = (10);
    int Mred = (20 + myData.spectrumRight1 / 30);      

         
         pwm5.setPWM(8, 0, Mblue);  
         pwm5.setPWM(9, 0, Mgreen); 
         pwm5.setPWM(10, 0, Mred); 
               
         pwm5.setPWM(12, 0, Mblue);  
         pwm5.setPWM(13, 0, Mgreen); 
         pwm5.setPWM(14, 0, Mred);



    int Spek1 = 4*myData.spectrumRight1^2 / 1024^2 / 1024;
      if (Spek1 > 3500) 
  {
    Spek1 = 3500;
  }


    int Spek2 = 4*myData.spectrumRight2^2 / 1024^2 / 1024;
          if (Spek2 > 3500) 
  {
    Spek2 = 3500;
  }

    int Spek3 = 4*myData.spectrumRight3^2 / 1024^2 / 1024;
          if (Spek3 > 3500) 
  {
    Spek3 = 3500;
  }

    int Spek4 = 4*myData.spectrumRight4^2 / 1024^2 / 1024;
          if (Spek4 > 3500) 
  {
    Spek4 = 3500;
  }
 
    int Spek5 = 4*myData.spectrumRight5^2 / 1024^2 / 1024;
          if (Spek5 > 3500) 
  {
    Spek5 = 3500;
  }

    int Spek6 = 4*myData.spectrumRight6^2 / 1024^2 / 1024;
          if (Spek6 > 3800) 
  {
    Spek6 = 3800;
  }
 
    int Spek7 = 4*myData.spectrumRight7^2 / 1024^2 / 1024;
          if (Spek7 > 3800) 
  {
    Spek7 = 3800;
  }

      

         pwm1.setPWM(0, 0, 0);  
         pwm1.setPWM(1, 0, Spek5); 
         pwm1.setPWM(2, 0, Spek3);
         //pwm1.setPWM(3, 0, 0);  
         pwm1.setPWM(4, 0, 0); 
         pwm1.setPWM(5, 0, Spek2);       
         pwm1.setPWM(6, 0, 0);
         //pwm1.setPWM(7, 0, 0);
    //     pwm1.setPWM(8, 0, 0);
    //     pwm1.setPWM(9, 0, Spek2/2);
    //     pwm1.setPWM(10, 0, Spek2);
         //pwm1.setPWM(11, 0, 0);
         pwm1.setPWM(12, 0, 0);
         pwm1.setPWM(13, 0, Spek5);
         pwm1.setPWM(14, 0, Spek3);
         //pwm1.setPWM(15, 0, 0);  

         pwm2.setPWM(0, 0, Spek6);  
         pwm2.setPWM(1, 0, Spek7/2); 
         pwm2.setPWM(2, 0, Spek7/2);
         //pwm2.setPWM(3, 0, 0);  
         pwm2.setPWM(4, 0, Spek6); 
         pwm2.setPWM(5, 0, Spek7/2);       
         pwm2.setPWM(6, 0, Spek7/2);
         //pwm2.setPWM(7, 0, 0);
         pwm2.setPWM(8, 0, Spek7);
         pwm2.setPWM(9, 0, 0);
         pwm2.setPWM(10, 0, 0);
        //pwm2.setPWM(11, 0, 0);
    //     pwm2.setPWM(12, 0, 0);
    //     pwm2.setPWM(13, 0, 0);
    //     pwm2.setPWM(14, 0, Spek1);
         //pwm2.setPWM(15, 0, 0);  

         pwm3.setPWM(0, 0, 0);  
         pwm3.setPWM(1, 0, Spek2/2); 
         pwm3.setPWM(2, 0, Spek2);
         //pwm3.setPWM(3, 0, 0);  
         pwm3.setPWM(4, 0, 0); 
         pwm3.setPWM(5, 0, Spek2/2);       
         pwm3.setPWM(6, 0, Spek2);
         //pwm3.setPWM(7, 0, 0);
         pwm3.setPWM(8, 0, Spek4);
         pwm3.setPWM(9, 0, 0);
         pwm3.setPWM(10, 0, Spek3);
         //pwm3.setPWM(11, 0, 0);
         pwm3.setPWM(12, 0, Spek4);
         pwm3.setPWM(13, 0, 0);
         pwm3.setPWM(14, 0, Spek3);
         //pwm3.setPWM(15, 0, 0);  
      
         pwm4.setPWM(0, 0, 0);  
         pwm4.setPWM(1, 0, 0); 
         pwm4.setPWM(2, 0, Spek1);
         //pwm4.setPWM(3, 0, 0);  
         pwm4.setPWM(4, 0, 0); 
         pwm4.setPWM(5, 0, 0);       
         pwm4.setPWM(6, 0, Spek1);
         //pwm4.setPWM(7, 0, 0);
         pwm4.setPWM(8, 0, 0);
         pwm4.setPWM(9, 0, Spek1/2);
         pwm4.setPWM(10, 0, Spek1);
         //pwm4.setPWM(11, 0, 0);
    //     pwm4.setPWM(12, 0, 0);
    //     pwm4.setPWM(13, 0, Spek2/2);
    //     pwm4.setPWM(14, 0, Spek2);
         //pwm4.setPWM(15, 0, 0);  


      
    }

 
    void RGBnSTAR4() {
  

       
         pwm5.setPWM(8, 0, myData.blue);  
         pwm5.setPWM(9, 0, myData.green); 
         pwm5.setPWM(10, 0, myData.red); 
               
         pwm5.setPWM(12, 0, myData.blue);  
         pwm5.setPWM(13, 0, myData.green); 
         pwm5.setPWM(14, 0, myData.red);


    int Spek1 = 4*myData.spectrumRight1^2 / 1024^2 / 1024;
      if (Spek1 > 3500) 
  {
    Spek1 = 3500;
  }


    int Spek2 = 4*myData.spectrumRight2^2 / 1024^2 / 1024;
          if (Spek2 > 3500) 
  {
    Spek2 = 3500;
  }

    int Spek3 = 4*myData.spectrumRight3^2 / 1024^2 / 1024;
          if (Spek3 > 3500) 
  {
    Spek3 = 3500;
  }

    int Spek4 = 4*myData.spectrumRight4^2 / 1024^2 / 1024;
          if (Spek4 > 3500) 
  {
    Spek4 = 3500;
  }
 
    int Spek5 = 4*myData.spectrumRight5^2 / 1024^2 / 1024;
          if (Spek5 > 3500) 
  {
    Spek5 = 3500;
  }

    int Spek6 = 4*myData.spectrumRight6^2 / 1024^2 / 1024;
          if (Spek6 > 3800) 
  {
    Spek6 = 3800;
  }
 
    int Spek7 = 4*myData.spectrumRight7^2 / 1024^2 / 1024;
          if (Spek7 > 3800) 
  {
    Spek7 = 3800;
  }

        

         pwm1.setPWM(0, 0, 0);  
         pwm1.setPWM(1, 0, Spek5); 
         pwm1.setPWM(2, 0, Spek3);
         //pwm1.setPWM(3, 0, 0);  
         pwm1.setPWM(4, 0, 0); 
         pwm1.setPWM(5, 0, Spek2);       
         pwm1.setPWM(6, 0, 0);
         //pwm1.setPWM(7, 0, 0);
    //     pwm1.setPWM(8, 0, 0);
    //     pwm1.setPWM(9, 0, Spek2/2);
    //     pwm1.setPWM(10, 0, Spek2);
         //pwm1.setPWM(11, 0, 0);
         pwm1.setPWM(12, 0, 0);
         pwm1.setPWM(13, 0, Spek5);
         pwm1.setPWM(14, 0, Spek3);
         //pwm1.setPWM(15, 0, 0);  

         pwm2.setPWM(0, 0, Spek6);  
         pwm2.setPWM(1, 0, Spek7/2); 
         pwm2.setPWM(2, 0, Spek7/2);
         //pwm2.setPWM(3, 0, 0);  
         pwm2.setPWM(4, 0, Spek6); 
         pwm2.setPWM(5, 0, Spek7/2);       
         pwm2.setPWM(6, 0, Spek7/2);
         //pwm2.setPWM(7, 0, 0);
         pwm2.setPWM(8, 0, Spek7);
         pwm2.setPWM(9, 0, 0);
         pwm2.setPWM(10, 0, 0);
        //pwm2.setPWM(11, 0, 0);
    //     pwm2.setPWM(12, 0, 0);
    //     pwm2.setPWM(13, 0, 0);
    //     pwm2.setPWM(14, 0, Spek1);
         //pwm2.setPWM(15, 0, 0);  

         pwm3.setPWM(0, 0, 0);  
         pwm3.setPWM(1, 0, Spek2/2); 
         pwm3.setPWM(2, 0, Spek2);
         //pwm3.setPWM(3, 0, 0);  
         pwm3.setPWM(4, 0, 0); 
         pwm3.setPWM(5, 0, Spek2/2);       
         pwm3.setPWM(6, 0, Spek2);
         //pwm3.setPWM(7, 0, 0);
         pwm3.setPWM(8, 0, Spek4);
         pwm3.setPWM(9, 0, 0);
         pwm3.setPWM(10, 0, Spek3);
         //pwm3.setPWM(11, 0, 0);
         pwm3.setPWM(12, 0, Spek4);
         pwm3.setPWM(13, 0, 0);
         pwm3.setPWM(14, 0, Spek3);
         //pwm3.setPWM(15, 0, 0);  
      
         pwm4.setPWM(0, 0, 0);  
         pwm4.setPWM(1, 0, 0); 
         pwm4.setPWM(2, 0, Spek1);
         //pwm4.setPWM(3, 0, 0);  
         pwm4.setPWM(4, 0, 0); 
         pwm4.setPWM(5, 0, 0);       
         pwm4.setPWM(6, 0, Spek1);
         //pwm4.setPWM(7, 0, 0);
         pwm4.setPWM(8, 0, 0);
         pwm4.setPWM(9, 0, Spek1/2);
         pwm4.setPWM(10, 0, Spek1);
         //pwm4.setPWM(11, 0, 0);
    //     pwm4.setPWM(12, 0, 0);
    //     pwm4.setPWM(13, 0, Spek2/2);
    //     pwm4.setPWM(14, 0, Spek2);
         //pwm4.setPWM(15, 0, 0);  


      
    }


   

   





//----------------------------------------------------------------------       
//----------------------------------------------------------------------       



   void sky1() {



         pwm5.setPWM(0, 0, 0);  
         pwm5.setPWM(1, 0, 0); 
         pwm5.setPWM(2, 0, 0);
         pwm5.setPWM(3, 0, 0);
         pwm5.setPWM(4, 0, 0);  
         pwm5.setPWM(5, 0, 0); 
         pwm5.setPWM(6, 0, 0);
         pwm5.setPWM(7, 0, 0);
         pwm5.setPWM(11, 0, 0);
         pwm5.setPWM(15, 0, 0);
         
 
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

  }

Rvalue1 = (exp(sin(millis()/350.0*PI))-0.3678)*1500;
Gvalue1 = (exp(sin(millis()/350.0*PI))-0.3678)*1500;
Bvalue1 = (exp(sin(millis()/350.0*PI))-0.3678)*1500;

Rvalue2 = (exp(sin(millis()/500.0*PI))-0.3678)*1500;
Gvalue2 = (exp(sin(millis()/500.0*PI))-0.3678)*1500;
Bvalue2 = (exp(sin(millis()/500.0*PI))-0.3678)*1500;

Rvalue3 = (exp(sin(millis()/1300.0*PI))-0.3678)*1500;
Gvalue3 = (exp(sin(millis()/1300.0*PI))-0.3678)*1500;
Bvalue3 = (exp(sin(millis()/1300.0*PI))-0.3678)*1500;

Rvalue4 = (exp(sin(millis()/1000.0*PI))-0.3678)*1500;
Gvalue4 = (exp(sin(millis()/1000.0*PI))-0.3678)*1500;
Bvalue4 = (exp(sin(millis()/1000.0*PI))-0.3678)*1500;

Rvalue5 = (exp(sin(millis()/700.0*PI))-0.3678)*1500;
Gvalue5 = (exp(sin(millis()/700.0*PI))-0.3678)*1500;
Bvalue5 = (exp(sin(millis()/700.0*PI))-0.3678)*1500;

Rvalue6 = (exp(sin(millis()/550.0*PI))-0.3678)*1500;
Gvalue6 = (exp(sin(millis()/550.0*PI))-0.3678)*1500;
Bvalue6 = (exp(sin(millis()/550.0*PI))-0.3678)*1500;

Rvalue3 = (exp(sin(millis()/500.0*PI))-0.3678)*1500;
Gvalue3 = 3400;
Bvalue3 = (exp(sin(millis()/400.0*PI))-0.3678)*1500;

Rvalue2 = 4000;
Gvalue2 = (exp(sin(millis()/400.0*PI))-0.3678)*1500;
Bvalue2 = (exp(sin(millis()/300.0*PI))-0.3678)*1500;


         pwm1.setPWM(0, 0, Bvalue6);  
         pwm1.setPWM(1, 0, Gvalue6); 
         pwm1.setPWM(2, 0, Rvalue6);
         //pwm1.setPWM(3, 0, 0);  
         pwm1.setPWM(4, 0, Bvalue6); 
         pwm1.setPWM(5, 0, Gvalue6);       
         pwm1.setPWM(6, 0, Rvalue6);
         //pwm1.setPWM(7, 0, 0);
         pwm1.setPWM(8, 0, 0);  //spare
         pwm1.setPWM(9, 0, 0);  //spare
         pwm1.setPWM(10, 0, 0); //spare
         //pwm1.setPWM(11, 0, 0);
         pwm1.setPWM(12, 0, Bvalue8);
         pwm1.setPWM(13, 0, Gvalue8);
         pwm1.setPWM(14, 0, Rvalue8);
         //pwm1.setPWM(15, 0, 0);  

         pwm2.setPWM(0, 0, Bvalue2);  
         pwm2.setPWM(1, 0, Gvalue2); 
         pwm2.setPWM(2, 0, Rvalue2);
         //pwm2.setPWM(3, 0, 0);  
         pwm2.setPWM(4, 0, Bvalue3); 
         pwm2.setPWM(5, 0, Gvalue3);       
         pwm2.setPWM(6, 0, Rvalue3);
         //pwm2.setPWM(7, 0, 0);
         pwm2.setPWM(8, 0, Bvalue3);
         pwm2.setPWM(9, 0, Gvalue3);
         pwm2.setPWM(10, 0, Rvalue3);
        //pwm2.setPWM(11, 0, 0);
         pwm2.setPWM(12, 0, 0); //spare
         pwm2.setPWM(13, 0, 0); //spare
         pwm2.setPWM(14, 0, 0); //spare
         //pwm2.setPWM(15, 0, 0);  

         pwm3.setPWM(0, 0, Bvalue4);  
         pwm3.setPWM(1, 0, Gvalue4); 
         pwm3.setPWM(2, 0, Rvalue4);
         //pwm3.setPWM(3, 0, 0);  
         pwm3.setPWM(4, 0, Bvalue5); 
         pwm3.setPWM(5, 0, Gvalue5);       
         pwm3.setPWM(6, 0, Rvalue5);
         //pwm3.setPWM(7, 0, 0);
         pwm3.setPWM(8, 0, Bvalue5);
         pwm3.setPWM(9, 0, Gvalue5);
         pwm3.setPWM(10, 0, Rvalue5);
         //pwm3.setPWM(11, 0, 0);
         pwm3.setPWM(12, 0, Bvalue1);
         pwm3.setPWM(13, 0, Gvalue1);
         pwm3.setPWM(14, 0, Rvalue1);
         //pwm3.setPWM(15, 0, 0);  
      
         pwm4.setPWM(0, 0, Bvalue4);  
         pwm4.setPWM(1, 0, Gvalue5); 
         pwm4.setPWM(2, 0, Rvalue5);
         //pwm4.setPWM(3, 0, 0);  
         pwm4.setPWM(4, 0, Bvalue2); 
         pwm4.setPWM(5, 0, Gvalue2);       
         pwm4.setPWM(6, 0, Rvalue2);
         //pwm4.setPWM(7, 0, 0);
         pwm4.setPWM(8, 0, Bvalue1);
         pwm4.setPWM(9, 0, Gvalue1);
         pwm4.setPWM(10, 0, Rvalue1);
         //pwm4.setPWM(11, 0, 0);
         pwm4.setPWM(12, 0, 0); //spare;
         pwm4.setPWM(13, 0, 0); //spare;
         pwm4.setPWM(14, 0, 0); //spare;
         //pwm4.setPWM(15, 0, 0);  

         pwm5.setPWM(8, 0, 7);  
         pwm5.setPWM(9, 0, 0); 
         pwm5.setPWM(10, 0, 15); 
               
         pwm5.setPWM(12, 0, 7);  
         pwm5.setPWM(13, 0, 0); 
         pwm5.setPWM(14, 0, 15);

         
   }


 void sky2() {


         pwm5.setPWM(0, 0, 0);  
         pwm5.setPWM(1, 0, 0); 
         pwm5.setPWM(2, 0, 0);
         pwm5.setPWM(3, 0, 0);
         pwm5.setPWM(4, 0, 0);  
         pwm5.setPWM(5, 0, 0); 
         pwm5.setPWM(6, 0, 0);
         pwm5.setPWM(7, 0, 0);
         pwm5.setPWM(8, 0, 0);  
         pwm5.setPWM(9, 0, 0); 
         pwm5.setPWM(10, 0, 0);
         pwm5.setPWM(11, 0, 0);
         pwm5.setPWM(12, 0, 0);  
         pwm5.setPWM(13, 0, 0); 
         pwm5.setPWM(14, 0, 0);
         pwm5.setPWM(15, 0, 0);

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    
brightness1 = random(3,5);
brightness2 = random(3,5);
brightness3 = random(3,5);


  }


Rvalue1 = 5*3*(exp(sin(millis()/2000.0*PI))-0.36787944)*100;
Gvalue1 = 5*3*(exp(sin(millis()/5000.0*PI))-0.36787944)*100;
Bvalue1 = 5*3*(exp(sin(millis()/5000.0*PI))-0.36787944)*100;

Rvalue2 = brightness3*3*(exp(sin(millis()/3000.0*PI))-0.36787944)*100;
Gvalue2 = brightness2*3*(exp(sin(millis()/3000.0*PI))-0.36787944)*100;
Bvalue2 = brightness1*3*(exp(sin(millis()/7000.0*PI))-0.36787944)*100;

Rvalue3 = brightness3*3*(exp(sin(millis()/2000.0*PI))-0.36787944)*100;
Gvalue3 = brightness2*1*(exp(sin(millis()/2000.0*PI))-0.36787944)*100;
Bvalue3 = brightness2*2*(exp(sin(millis()/1000.0*PI))-0.36787944)*100;

Rvalue4 = brightness1*3*(exp(sin(millis()/10000.0*PI))-0.36787944)*100;
Gvalue4 = brightness2*2*(exp(sin(millis()/10000.0*PI))-0.36787944)*100;
Bvalue4 = brightness3*1*(exp(sin(millis()/1000.0*PI))-0.36787944)*100;

Rvalue5 = brightness2*3*(exp(sin(millis()/15000.0*PI))-0.36787944)*100;
Gvalue5 = brightness1*1*(exp(sin(millis()/10000.0*PI))-0.36787944)*100;
Bvalue5 = brightness2*1*(exp(sin(millis()/15000.0*PI))-0.36787944)*100;

Rvalue5 = brightness2*3*(exp(sin(millis()/1000.0*PI))-0.36787944)*100;
Gvalue5 = 3000;
Bvalue5 = brightness2*1*(exp(sin(millis()/1000.0*PI))-0.36787944)*100;

Rvalue4 = 3400;
Gvalue4 = brightness2*2*(exp(sin(millis()/10000.0*PI))-0.36787944)*100;
Bvalue4 = brightness3*1*(exp(sin(millis()/10000.0*PI))-0.36787944)*100;

Rvalue8 = 3400;
Gvalue8 = 1000;
Bvalue8 = 1000;

         pwm1.setPWM(0, 0, Bvalue6);  
         pwm1.setPWM(1, 0, Gvalue6); 
         pwm1.setPWM(2, 0, Rvalue6);
         //pwm1.setPWM(3, 0, 0);  
         pwm1.setPWM(4, 0, Bvalue6); 
         pwm1.setPWM(5, 0, Gvalue6);       
         pwm1.setPWM(6, 0, Rvalue6);
         //pwm1.setPWM(7, 0, 0);
         pwm1.setPWM(8, 0, 0);  //spare
         pwm1.setPWM(9, 0, 0);  //spare
         pwm1.setPWM(10, 0, 0); //spare
         //pwm1.setPWM(11, 0, 0);
         pwm1.setPWM(12, 0, Bvalue8);
         pwm1.setPWM(13, 0, Gvalue8);
         pwm1.setPWM(14, 0, Rvalue8);
         //pwm1.setPWM(15, 0, 0);  

         pwm2.setPWM(0, 0, Bvalue2);  
         pwm2.setPWM(1, 0, Gvalue2); 
         pwm2.setPWM(2, 0, Rvalue2);
         //pwm2.setPWM(3, 0, 0);  
         pwm2.setPWM(4, 0, Bvalue3); 
         pwm2.setPWM(5, 0, Gvalue3);       
         pwm2.setPWM(6, 0, Rvalue3);
         //pwm2.setPWM(7, 0, 0);
         pwm2.setPWM(8, 0, Bvalue3);
         pwm2.setPWM(9, 0, Gvalue3);
         pwm2.setPWM(10, 0, Rvalue3);
        //pwm2.setPWM(11, 0, 0);
         pwm2.setPWM(12, 0, 0);  //spare
         pwm2.setPWM(13, 0, 0);  //spare
         pwm2.setPWM(14, 0, 0);  //spare
         //pwm2.setPWM(15, 0, 0);  

         pwm3.setPWM(0, 0, Bvalue4);  
         pwm3.setPWM(1, 0, Gvalue4); 
         pwm3.setPWM(2, 0, Rvalue4);
         //pwm3.setPWM(3, 0, 0);  
         pwm3.setPWM(4, 0, Bvalue5); 
         pwm3.setPWM(5, 0, Gvalue5);       
         pwm3.setPWM(6, 0, Rvalue5);
         //pwm3.setPWM(7, 0, 0);
         pwm3.setPWM(8, 0, Bvalue5);
         pwm3.setPWM(9, 0, Gvalue5);
         pwm3.setPWM(10, 0, Rvalue5);
         //pwm3.setPWM(11, 0, 0);
         pwm3.setPWM(12, 0, Bvalue1);
         pwm3.setPWM(13, 0, Gvalue1);
         pwm3.setPWM(14, 0, Rvalue1);
         //pwm3.setPWM(15, 0, 0);  
      
         pwm4.setPWM(0, 0, Bvalue4);  
         pwm4.setPWM(1, 0, Gvalue5); 
         pwm4.setPWM(2, 0, Rvalue5);
         //pwm4.setPWM(3, 0, 0);  
         pwm4.setPWM(4, 0, Bvalue2); 
         pwm4.setPWM(5, 0, Gvalue2);       
         pwm4.setPWM(6, 0, Rvalue2);
         //pwm4.setPWM(7, 0, 0);
         pwm4.setPWM(8, 0, Bvalue1);
         pwm4.setPWM(9, 0, Gvalue1);
         pwm4.setPWM(10, 0, Rvalue1);
         //pwm4.setPWM(11, 0, 0);
         pwm4.setPWM(12, 0, 0); //spare
         pwm4.setPWM(13, 0, 0); //spare
         pwm4.setPWM(14, 0, 0); //spare
         //pwm4.setPWM(15, 0, 0);  



   }



void sky2_1() {


         pwm5.setPWM(0, 0, 0);  
         pwm5.setPWM(1, 0, 0); 
         pwm5.setPWM(2, 0, 0);
         pwm5.setPWM(3, 0, 0);
         pwm5.setPWM(4, 0, 0);  
         pwm5.setPWM(5, 0, 0); 
         pwm5.setPWM(6, 0, 0);
         pwm5.setPWM(7, 0, 0);
    //     pwm5.setPWM(8, 0, 0);  
    //     pwm5.setPWM(9, 0, 0); 
    //     pwm5.setPWM(10, 0, 0); 
         pwm5.setPWM(11, 0, 0);
   //      pwm5.setPWM(12, 0, 0);  
    //     pwm5.setPWM(13, 0, 0); 
    //     pwm5.setPWM(14, 0, 0);   
         pwm5.setPWM(15, 0, 0);

    int Mblue = (0);
    int Mgreen = (50);
    int Mred = (100);      

         
         pwm5.setPWM(8, 0, Mblue);  
         pwm5.setPWM(9, 0, Mgreen); 
         pwm5.setPWM(10, 0, Mred); 
         pwm5.setPWM(12, 0, Mblue);  
         pwm5.setPWM(13, 0, Mgreen); 
         pwm5.setPWM(14, 0, Mred);  




  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    
brightness1 = random(3,5);
brightness2 = random(3,5);
brightness3 = random(3,5);


  }


Rvalue1 = 5*3*(exp(sin(millis()/2000.0*PI))-0.36787944)*100;
Gvalue1 = 5*3*(exp(sin(millis()/5000.0*PI))-0.36787944)*100;
Bvalue1 = 5*3*(exp(sin(millis()/5000.0*PI))-0.36787944)*100;

Rvalue2 = brightness3*3*(exp(sin(millis()/3000.0*PI))-0.36787944)*100;
Gvalue2 = brightness2*3*(exp(sin(millis()/3000.0*PI))-0.36787944)*100;
Bvalue2 = brightness1*3*(exp(sin(millis()/7000.0*PI))-0.36787944)*100;

Rvalue3 = brightness3*3*(exp(sin(millis()/2000.0*PI))-0.36787944)*100;
Gvalue3 = brightness2*1*(exp(sin(millis()/2000.0*PI))-0.36787944)*100;
Bvalue3 = brightness2*2*(exp(sin(millis()/1000.0*PI))-0.36787944)*100;

Rvalue4 = brightness1*3*(exp(sin(millis()/10000.0*PI))-0.36787944)*100;
Gvalue4 = brightness2*2*(exp(sin(millis()/10000.0*PI))-0.36787944)*100;
Bvalue4 = brightness3*1*(exp(sin(millis()/1000.0*PI))-0.36787944)*100;

Rvalue5 = brightness2*3*(exp(sin(millis()/15000.0*PI))-0.36787944)*100;
Gvalue5 = brightness1*1*(exp(sin(millis()/10000.0*PI))-0.36787944)*100;
Bvalue5 = brightness2*1*(exp(sin(millis()/15000.0*PI))-0.36787944)*100;

Rvalue5 = brightness2*3*(exp(sin(millis()/1000.0*PI))-0.36787944)*100;
Gvalue5 = 3000;
Bvalue5 = brightness2*1*(exp(sin(millis()/1000.0*PI))-0.36787944)*100;

Rvalue4 = 3400;
Gvalue4 = brightness2*2*(exp(sin(millis()/10000.0*PI))-0.36787944)*100;
Bvalue4 = brightness3*1*(exp(sin(millis()/10000.0*PI))-0.36787944)*100;

Rvalue8 = 3400;
Gvalue8 = 1000;
Bvalue8 = 1000;
   

         pwm1.setPWM(0, 0, Bvalue6);  
         pwm1.setPWM(1, 0, Gvalue6); 
         pwm1.setPWM(2, 0, Rvalue6);
         //pwm1.setPWM(3, 0, 0);  
         pwm1.setPWM(4, 0, Bvalue6); 
         pwm1.setPWM(5, 0, Gvalue6);       
         pwm1.setPWM(6, 0, Rvalue6);
         //pwm1.setPWM(7, 0, 0);
         pwm1.setPWM(8, 0, 0);  //spare
         pwm1.setPWM(9, 0, 0);  //spare
         pwm1.setPWM(10, 0, 0); //spare
         //pwm1.setPWM(11, 0, 0);
         pwm1.setPWM(12, 0, Bvalue8);
         pwm1.setPWM(13, 0, Gvalue8);
         pwm1.setPWM(14, 0, Rvalue8);
         //pwm1.setPWM(15, 0, 0);  

         pwm2.setPWM(0, 0, Bvalue2);  
         pwm2.setPWM(1, 0, Gvalue2); 
         pwm2.setPWM(2, 0, Rvalue2);
         //pwm2.setPWM(3, 0, 0);  
         pwm2.setPWM(4, 0, Bvalue3); 
         pwm2.setPWM(5, 0, Gvalue3);       
         pwm2.setPWM(6, 0, Rvalue3);
         //pwm2.setPWM(7, 0, 0);
         pwm2.setPWM(8, 0, Bvalue3);
         pwm2.setPWM(9, 0, Gvalue3);
         pwm2.setPWM(10, 0, Rvalue3);
        //pwm2.setPWM(11, 0, 0);
         pwm2.setPWM(12, 0, 0); //spare
         pwm2.setPWM(13, 0, 0); //spare
         pwm2.setPWM(14, 0, 0); //spare
         //pwm2.setPWM(15, 0, 0);  

         pwm3.setPWM(0, 0, Bvalue4);  
         pwm3.setPWM(1, 0, Gvalue4); 
         pwm3.setPWM(2, 0, Rvalue4);
         //pwm3.setPWM(3, 0, 0);  
         pwm3.setPWM(4, 0, Bvalue5); 
         pwm3.setPWM(5, 0, Gvalue5);       
         pwm3.setPWM(6, 0, Rvalue5);
         //pwm3.setPWM(7, 0, 0);
         pwm3.setPWM(8, 0, Bvalue5);
         pwm3.setPWM(9, 0, Gvalue5);
         pwm3.setPWM(10, 0, Rvalue5);
         //pwm3.setPWM(11, 0, 0);
         pwm3.setPWM(12, 0, Bvalue1);
         pwm3.setPWM(13, 0, Gvalue1);
         pwm3.setPWM(14, 0, Rvalue1);
         //pwm3.setPWM(15, 0, 0);  
      
         pwm4.setPWM(0, 0, Bvalue4);  
         pwm4.setPWM(1, 0, Gvalue5); 
         pwm4.setPWM(2, 0, Rvalue5);
         //pwm4.setPWM(3, 0, 0);  
         pwm4.setPWM(4, 0, Bvalue2); 
         pwm4.setPWM(5, 0, Gvalue2);       
         pwm4.setPWM(6, 0, Rvalue2);
         //pwm4.setPWM(7, 0, 0);
         pwm4.setPWM(8, 0, Bvalue1);
         pwm4.setPWM(9, 0, Gvalue1);
         pwm4.setPWM(10, 0, Rvalue1);
         //pwm4.setPWM(11, 0, 0);
         pwm4.setPWM(12, 0, 0); //spare
         pwm4.setPWM(13, 0, 0); //spare
         pwm4.setPWM(14, 0, 0); //spare
         //pwm4.setPWM(15, 0, 0);  

 
         
         pwm5.setPWM(8, 0, Mblue);  
         pwm5.setPWM(9, 0, Mgreen); 
         pwm5.setPWM(10, 0, Mred); 
         pwm5.setPWM(12, 0, Mblue);  
         pwm5.setPWM(13, 0, Mgreen); 
         pwm5.setPWM(14, 0, Mred);  

   }

 
   
      void constellations1() {


         pwm5.setPWM(0, 0, 0);  
         pwm5.setPWM(1, 0, 0); 
         pwm5.setPWM(2, 0, 0);
         pwm5.setPWM(3, 0, 0);
         pwm5.setPWM(4, 0, 0);  
         pwm5.setPWM(5, 0, 0); 
         pwm5.setPWM(6, 0, 0);
         pwm5.setPWM(7, 0, 0);
         pwm5.setPWM(8, 0, 0);  
         pwm5.setPWM(9, 0, 0); 
         pwm5.setPWM(10, 0, 0);
         pwm5.setPWM(11, 0, 0);
         pwm5.setPWM(12, 0, 0);  
         pwm5.setPWM(13, 0, 0); 
         pwm5.setPWM(14, 0, 0);
         pwm5.setPWM(15, 0, 0);


Bclass1 = 3400;
Gclass1 = 3400;
Rclass1 = 3700;

Bclass2 = 2400;
Gclass2 = 2400;
Rclass2 = 2700;
   
Bclass3 = 2000;
Gclass3 = 2000;
Rclass3 = 2300;

Bclass4 = 1600;
Gclass4 = 1600;
Rclass4 = 1900;

Bclass5 = 1300;
Gclass5 = 1300;
Rclass5 = 1500;

         pwm3.setPWM(8, 0, 4000);
         pwm3.setPWM(9, 0, 4000);
         pwm3.setPWM(10, 0, 4000);
         //pwm3.setPWM(11, 0, 3000);
         pwm3.setPWM(12, 0, 3000);
         pwm3.setPWM(13, 0, 3000);
         pwm3.setPWM(14, 0, 3000);
         //pwm3.setPWM(15, 0, 0);  
      
         pwm4.setPWM(0, 0, 3000);  
         pwm4.setPWM(1, 0, 3000); 
         pwm4.setPWM(2, 0, 3000);
         //pwm4.setPWM(3, 0, 0);  
         pwm4.setPWM(4, 0, 3000); 
         pwm4.setPWM(5, 0, 3000);       
         pwm4.setPWM(6, 0, 3000);
         //pwm4.setPWM(7, 0, 0);
         pwm4.setPWM(8, 0, 3000);
         pwm4.setPWM(9, 0, 3000);
         pwm4.setPWM(10, 0, 3000);
         //pwm4.setPWM(11, 0, 0);


  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    
brightness1 = random(1,3);
brightness2 = random(1,3);
brightness3 = random(1,3);

  }


Rvalue1 = 3*(exp(sin(millis()/5000.0*PI))-0.36787944)*100;
Gvalue1 = 3*(exp(sin(millis()/5000.0*PI))-0.36787944)*100;
Bvalue1 = 3*(exp(sin(millis()/5000.0*PI))-0.36787944)*100;

Rvalue2 = brightness3*(exp(sin(millis()/7000.0*PI))-0.36787944)*100;
Gvalue2 = brightness2*(exp(sin(millis()/7000.0*PI))-0.36787944)*100;
Bvalue2 = brightness1*(exp(sin(millis()/7000.0*PI))-0.36787944)*100;

Rvalue3 = brightness3*(exp(sin(millis()/2000.0*PI))-0.36787944)*100;
Gvalue3 = brightness2*(exp(sin(millis()/2000.0*PI))-0.36787944)*100/2;
Bvalue3 = brightness2*(exp(sin(millis()/2000.0*PI))-0.36787944)*100/2;

Rvalue4 = brightness1*(exp(sin(millis()/10000.0*PI))-0.36787944)*100;
Gvalue4 = brightness2*(exp(sin(millis()/10000.0*PI))-0.36787944)*100;
Bvalue4 = brightness3*(exp(sin(millis()/10000.0*PI))-0.36787944)*100;

Rvalue5 = brightness2*(exp(sin(millis()/15000.0*PI))-0.36787944)*100;
Gvalue5 = brightness1*(exp(sin(millis()/15000.0*PI))-0.36787944)*100/2;
Bvalue5 = brightness2*(exp(sin(millis()/15000.0*PI))-0.36787944)*100/2;


         pwm1.setPWM(0, 0, Bvalue1);  
         pwm1.setPWM(1, 0, Gvalue1); 
         pwm1.setPWM(2, 0, Rvalue1);
         //pwm1.setPWM(3, 0, 0);  
         pwm1.setPWM(4, 0, Bvalue2); 
         pwm1.setPWM(5, 0, Gvalue2);       
         pwm1.setPWM(6, 0, Rvalue2);
         //pwm1.setPWM(7, 0, 0);
         pwm1.setPWM(8, 0, 0);  //spare
         pwm1.setPWM(9, 0, 0);  //spare
         pwm1.setPWM(10, 0, 0); //spare
         //pwm1.setPWM(11, 0, 0);
         pwm1.setPWM(12, 0, Bvalue3);
         pwm1.setPWM(13, 0, Gvalue3);
         pwm1.setPWM(14, 0, Rvalue3);
         //pwm1.setPWM(15, 0, 0);  

         pwm2.setPWM(0, 0, Bvalue4);  
         pwm2.setPWM(1, 0, Gvalue4); 
         pwm2.setPWM(2, 0, Rvalue4);
         //pwm2.setPWM(3, 0, 0);  
         pwm2.setPWM(4, 0, Bvalue5); 
         pwm2.setPWM(5, 0, Gvalue5);       
         pwm2.setPWM(6, 0, Rvalue5);
         //pwm2.setPWM(7, 0, 0);
         pwm2.setPWM(8, 0, Bvalue3);
         pwm2.setPWM(9, 0, Gvalue3);
         pwm2.setPWM(10, 0, Rvalue3);
        //pwm2.setPWM(11, 0, 0);
         pwm2.setPWM(12, 0, 0); //spare
         pwm2.setPWM(13, 0, 0); //spare
         pwm2.setPWM(14, 0, 0); //spare
         //pwm2.setPWM(15, 0, 0);  

         pwm3.setPWM(0, 0, Bvalue5);  
         pwm3.setPWM(1, 0, Gvalue5); 
         pwm3.setPWM(2, 0, Rvalue5);
         //pwm3.setPWM(3, 0, 0);  
  }
   void constellations2() {

         pwm5.setPWM(0, 0, 0);  
         pwm5.setPWM(1, 0, 0); 
         pwm5.setPWM(2, 0, 0);
         pwm5.setPWM(3, 0, 0);
         pwm5.setPWM(4, 0, 0);  
         pwm5.setPWM(5, 0, 0); 
         pwm5.setPWM(6, 0, 0);
         pwm5.setPWM(7, 0, 0);
         pwm5.setPWM(8, 0, 0);  
         pwm5.setPWM(9, 0, 0); 
         pwm5.setPWM(10, 0, 0);
         pwm5.setPWM(11, 0, 0);
         pwm5.setPWM(12, 0, 0);  
         pwm5.setPWM(13, 0, 0); 
         pwm5.setPWM(14, 0, 0);
         pwm5.setPWM(15, 0, 0);

         

Bclass1 = 3400;
Gclass1 = 3400;
Rclass1 = 3700;

Bclass2 = 2400;
Gclass2 = 2400;
Rclass2 = 2700;
   
Bclass3 = 2000;
Gclass3 = 2000;
Rclass3 = 2300;

Bclass4 = 1600;
Gclass4 = 1600;
Rclass4 = 1900;

Bclass5 = 1300;
Gclass5 = 1300;
Rclass5 = 1500;



         pwm3.setPWM(8, 0, Bclass1);
         pwm3.setPWM(9, 0, Gclass1);
         pwm3.setPWM(10, 0, Rclass1);
         //pwm3.setPWM(11, 0, 0);

         pwm3.setPWM(12, 0, Bclass2);
         pwm3.setPWM(13, 0, Gclass2);
         pwm3.setPWM(14, 0, Rclass2);
         //pwm3.setPWM(15, 0, 0);  

         pwm4.setPWM(0, 0, Bclass4);  
         pwm4.setPWM(1, 0, Gclass4); 
         pwm4.setPWM(2, 0, Rclass4);
         //pwm4.setPWM(3, 0, 0);  

         pwm4.setPWM(4, 0, Bclass3); 
         pwm4.setPWM(5, 0, Bclass3);       
         pwm4.setPWM(6, 0, Bclass3);
         //pwm4.setPWM(7, 0, 0);
         
         pwm4.setPWM(8, 0, Bclass5);
         pwm4.setPWM(9, 0, Gclass5);
         pwm4.setPWM(10, 0, Rclass5);
         //pwm4.setPWM(11, 0, 0);




  }
