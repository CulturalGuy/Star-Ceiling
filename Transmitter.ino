
/*-----( MSGEQ7 )-----*/ 
int channelRight = A0;  
int ctrlReset = 4;
int ctrlStrobe = 3;

/*-----( NRF24L01 )-----*/
#include <SPI.h>   // Comes with Arduino IDE
#include "RF24.h"  // Download and Install (See above)
#include "printf.h" // Needed for "printDetails" Takes up some memory
/*-----( Declare Constants and Pin Numbers )-----*/
#define  CE_PIN  7   // The pins to be used for CE and SN
#define  CSN_PIN 8

/* NRF24L01 PINS:
  VCC  -> 3.3V
  CSN  -> 8
  MOSI -> 11
  IRQ  -> X
  CE   -> 7
  SCK  -> 13
  MISO -> 12
*/


/*-----( Declare objects )-----*/
/* Hardware configuration: Set up nRF24L01 radio on SPI bus plus (usually) pins 7 & 8 (Can be changed) */
RF24 radio(CE_PIN, CSN_PIN);

/*-----( Declare Variables )-----*/
byte addresses[][6] = {"1Node", "2Node"}; // These will be the names of the "Pipes"

unsigned long timeNow;  // Used to grab the current time, calculate delays
unsigned long started_waiting_at;
boolean timeout;       // Timeout? True or False

struct dataStruct {

int IRcode;                    // Array to store 7 bands of spectrum data from right channel;
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

} myData;                 // This can be accessed in the form:  myData.Xposition  etc.

float i = 0;   

/*----------------- */

#include <IRremote.h>
int recvPin = 2; // IR Receiver - Arduino Pin Number 2

int intensity = 10; // Intensity variable
int speedValue = 5; // Speed Variable
int currentColors[] = {0, 0, 0}; // Current Color outputed variable (black by default)
bool customLoop = false; // Variable telling us we are in a custom animation loop

unsigned long previousMillis = 0; // variable for the delay function
unsigned long previousMillis2 = 0; // variable for the delay function
unsigned long previousMillis3 = 0; // variable for the delay function

int redVal = 0;
int grnVal = 0;
int bluVal = 0;

int prevR = redVal;
int prevG = grnVal;
int prevB = bluVal;


IRrecv irrecv(recvPin);
decode_results results;

// Defining hex codes for the remote

#define INTENSITY_UP_CODE 0x8503705D
#define INTENSITY_DN_CODE 0xDEB0C861
#define ON_CODE  0xD4DD0381
#define OFF_CODE 0xCE1972FD
#define RED_CODE 0xE85952E1
#define GREEN_CODE 0x78CDA4DD
#define BLUE_CODE 0xA2672345
#define WHITE_CODE 0x9BA392C1
#define ORANGE_CODE 0xD3FD9A81   
#define YELLOW_CODE 0x6471EC7D   
#define TEAL_CODE 0x9D52009D
#define PINK_DARK_CODE 0xDCC45BE1   
#define STROBE_CODE 0x84044BBD
#define SMOOTH_CODE 0x14789DB9
#define FADE_CODE 0x3E121C21
#define FLASH_CODE 0x374E8B9D
#define MUSIC_CODE 0xB0F9B3E1
#define MUSIC2_CODE 0x416E05DD
#define MUSIC3_CODE 0x6A844445
#define MUSIC4_CODE 0xB9C07541

#define TURQUOISE_CODE 0x5B83B61B
#define NAVY_CODE 0xB5310E1F
#define BROWN_CODE 0x73CEC633
#define PURPLE_DARK_CODE 0xB08CB7DF
#define ORANGE_LIGHT_CODE 0x410109DB
#define BLUE_LIGHT_CODE 0x7EC31EF7


//Not used
#define BLUE_BABY_CODE 0xAAAAAFF
#define PINK_CODE 0xAAAAADD


// defining the avaialble colors one by one
int BLACK_COLOR[3] = {0, 0, 0};
int RED_COLOR[3] = {0, 0, 0};
int GREEN_COLOR[3] = {0, 0, 0};
int BLUE_COLOR[3] =  {0, 0, 0};
int WHITE_COLOR[3] = {0, 0, 0};
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

// defining all the available remote codes in an array
int AVAILABLE_CODES[28] = {ON_CODE, OFF_CODE, INTENSITY_UP_CODE, INTENSITY_DN_CODE, RED_CODE, GREEN_CODE, BLUE_CODE, WHITE_CODE, ORANGE_CODE, TURQUOISE_CODE, NAVY_CODE, BROWN_CODE, TEAL_CODE, PURPLE_DARK_CODE, ORANGE_LIGHT_CODE, BLUE_LIGHT_CODE, PINK_DARK_CODE, YELLOW_CODE, BLUE_BABY_CODE, PINK_CODE, FLASH_CODE, FADE_CODE, SMOOTH_CODE, STROBE_CODE, MUSIC_CODE, MUSIC2_CODE, MUSIC3_CODE, MUSIC4_CODE};

// defining all the available colors in an array
int AVAILABLE_COLORS[5][3] = {{150, 0, 40}, {150, 40, 0}, {150, 15, 15}, {15, 30, 100}, {15, 100, 30}} ;

int randomNumber_2 = random(5);


void setup() {
//  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver

/*-----( MSGEG7 )-----*/

  pinMode(ctrlReset,OUTPUT);             // Define reset as output
  pinMode(ctrlStrobe,OUTPUT);            // Define strobe as output
  digitalWrite(ctrlReset,LOW);           // Pull the reset signal low
  digitalWrite(ctrlStrobe,HIGH);         // Drive the strobe signal high



/*-----( NRF24L01 )-----*/
  radio.begin();          // Initialize the nRF24L01 Radio
  radio.setChannel(108);  // Above most WiFi frequencies
  radio.setDataRate(RF24_250KBPS); // Fast enough.. Better range

  // Set the Power Amplifier Level low to prevent power supply related issues since this is a
  // getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.
  // PALevelcan be one of four levels: RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH and RF24_PA_MAX
  radio.setPALevel(RF24_PA_LOW);
  //  radio.setPALevel(RF24_PA_MAX);

  // Open a writing and reading pipe on each radio, with opposite addresses
  radio.openWritingPipe(addresses[0]);
  radio.openReadingPipe(1, addresses[1]);

  // Start the radio listening for data
  radio.startListening();

//  radio.printDetails(); //Uncomment to show LOTS of debugging information
}//--(end setup )---
  

// function for interpreting the incoming code and eighter setting a fixed color or starting a custom loop function
void interpretRemoteCode(int code) {
  int randomColor[3] = {random(256), random(256), random(256)};
  switch (code) {
    case ON_CODE: setColor(randomColor); break;
    case OFF_CODE: setColor(BLACK_COLOR); break;
    case INTENSITY_UP_CODE: raiseIntensity(); break;
    case INTENSITY_DN_CODE: lowerIntensity(); break;
    case RED_CODE: setColor(RED_COLOR); break;
    case GREEN_CODE: setColor(GREEN_COLOR); break;
    case BLUE_CODE: setColor(BLUE_COLOR); break;
    case WHITE_CODE: setColor(WHITE_COLOR); break;
    case ORANGE_CODE: setColor(ORANGE_COLOR); break;
    case TURQUOISE_CODE: setColor(TURQUOISE_COLOR); break;
    case NAVY_CODE: setColor(NAVY_COLOR); break;
    case BROWN_CODE: setColor(BROWN_COLOR); break;
    case TEAL_CODE: setColor(TEAL_COLOR); break;
    case PURPLE_DARK_CODE: setColor(PURPLE_DARK_COLOR); break;
    case ORANGE_LIGHT_CODE: setColor(ORANGE_LIGHT_COLOR); break;
    case BLUE_LIGHT_CODE: MUSIC(); break;
    case PINK_DARK_CODE: setColor(PINK_DARK_COLOR); break;
    case YELLOW_CODE: setColor(YELLOW_COLOR); break;
    case BLUE_BABY_CODE: setColor(BLUE_BABY_COLOR); break;
    case PINK_CODE: setColor(PINK_COLOR); break;
    case FLASH_CODE: flash(); break;
    case STROBE_CODE: strobe(); break;
    case FADE_CODE: fade(); break;
    case SMOOTH_CODE: crossFade(); break;
    case MUSIC_CODE: MUSIC(); break;
    case MUSIC2_CODE: MUSIC(); break;
    case MUSIC3_CODE: MUSIC(); break;
    case MUSIC4_CODE: MUSIC(); break;        
  }
}

// raise the intensity of light or the speed of animation
void raiseIntensity() {
  if (!customLoop) {
    if (intensity <= 9) {
      intensity++;
    }
  } else if (speedValue <= 9) {
    speedValue++;
  }
}

// lower the intensity of light or the speed of animation
void lowerIntensity() {
  if (!customLoop) {
    if (intensity >= 2) {
      intensity--;
    }
  } else if (speedValue >= 2) {
    speedValue--;
  }
}

// helper function to check if a value is present in an array
int existsInArray(int compareValue, int arrayName[], int arraySize) {
  for (int x = 0; x < arraySize; x = x + 1) {
    if (arrayName[x] == compareValue) {
      return true;
    }
  }
  return false;
}

// set the currentColors variable
void setColor(int colors[]) {
  currentColors[0] = colors[0];
  currentColors[1] = colors[1];
  currentColors[2] = colors[2];
}

// calculate the intensity and send the current color out via the output pins
void sendColor(){
  
  if (customLoop == false) {
    int red = currentColors[0];
    int green = currentColors[1];
    int blue = currentColors[2];

    int mappedIntensity = map(intensity, 0, 10, 0, 255);
    int redComputed = map(red, 0, 255, 0, mappedIntensity);
    int blueComputed = map(blue, 0, 255, 0, mappedIntensity);
    int greenComputed = map(green, 0, 255, 0, mappedIntensity);

myData.red = redComputed;
myData.green = greenComputed;
myData.blue = blueComputed;

      if (!radio.write( &myData, sizeof(myData) )) {            // Send data, checking for error ("!" means NOT)
}


  }
}


void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= 100) {
    previousMillis = currentMillis;
    findCode();
   }
}

// decode remote controll code and if found in the array of available codes interpret it
void findCode() {
   radio.stopListening();                                    // First, stop listening so we can talk (NRF24L01)
  if (irrecv.decode(&results)) {
    
    myData.IRcode = results.value;
    if (!radio.write( &myData, sizeof(myData) )) {            // Send data, checking for error ("!" means NOT)
  // Serial.println(F("Transmit failed "));
  }
  // Send again after delay. When working OK, change to something like 100
  //  delay(100);
Serial.print(results.value, HEX);
Serial.print(" ");
Serial.println(myData.IRcode);

    if (existsInArray(results.value, AVAILABLE_CODES, 28)) {
      Serial.println("Code Found");
      interpretRemoteCode(results.value);
      
      if (results.value != FLASH_CODE && results.value != STROBE_CODE && results.value != FADE_CODE && results.value != SMOOTH_CODE && results.value != MUSIC_CODE) {
        customLoop = false;
        sendColor();
      }
    } else {
      Serial.println("Invalid Code");
    }
    irrecv.resume();
  }
}


void flash() {
crossFade();
}

void strobe() {
crossFade();
}

void fade() {
crossFade();
}



void crossFade() {
 customLoop = true;
  randomNumber_2 = random(5);
  int R = map(AVAILABLE_COLORS[randomNumber_2][0], 0, 150, 0, 60);
  int G = map(AVAILABLE_COLORS[randomNumber_2][1], 0, 150, 0, 60);
  int B = map(AVAILABLE_COLORS[randomNumber_2][2], 0, 150, 0, 60);

unsigned long previousMillis3 = 0;
unsigned long previousMillis2 = 0;


  while (customLoop) { // while we are still in the custom animation loop
    if (irrecv.decode(&results)) {
      if (existsInArray(results.value, AVAILABLE_CODES, 28) && results.value != INTENSITY_UP_CODE && results.value !=  INTENSITY_DN_CODE && results.value != SMOOTH_CODE) {
        Serial.println("return break");
        return; break;
        interpretRemoteCode(results.value);
      } else if (results.value == INTENSITY_UP_CODE) {
        raiseIntensity();
      } else if (results.value == INTENSITY_DN_CODE) {
        lowerIntensity();
      }
      irrecv.resume();
    }


int mappedSpeed = map(speedValue, 10, 1, 1000, 50000);
int crossfadespeed = 10;  
    unsigned long currentMillis3 = millis();
    unsigned long currentMillis2 = millis();


 if ( redVal == R && grnVal == G && bluVal == B && (currentMillis2 - previousMillis2 >= mappedSpeed)){
      previousMillis2 = currentMillis2;
    
   randomNumber_2 = random(5);
  R = AVAILABLE_COLORS[randomNumber_2][0];
  G = AVAILABLE_COLORS[randomNumber_2][1];
  B = AVAILABLE_COLORS[randomNumber_2][2]; 

   }


    if (currentMillis3 - previousMillis3 >= crossfadespeed) {
      previousMillis3 = currentMillis3;
    
   
if ( redVal < R ){
  redVal += 1;
}
   else if ( redVal > R ){
  redVal -= 1;    
   }  

if ( bluVal < B ){
  bluVal+= 1;
}
   else if ( bluVal > B ){
  bluVal-= 1;    
   }  

if ( grnVal < G ){
  grnVal+= 1;
}
   else if ( grnVal > G ){
  grnVal-= 1;    
   }  
}


myData.blue =  bluVal;
myData.green = grnVal;
myData.red = redVal;  

      if (!radio.write( &myData, sizeof(myData) )) {            // Send data, checking for error ("!" means NOT)
}
}
}





// MSGEQ7
void MUSIC() {


  customLoop = true;

  int R = map(AVAILABLE_COLORS[randomNumber_2][0], 0, 150, 0, 60);
  int G = map(AVAILABLE_COLORS[randomNumber_2][1], 0, 150, 0, 60);
  int B = map(AVAILABLE_COLORS[randomNumber_2][2], 0, 150, 0, 60);

unsigned long previousMillis3 = 0;
unsigned long previousMillis2 = 0;


  while (customLoop) { // while we are still in the custom animation loop
    if (irrecv.decode(&results)) { // check for incomming ir code and if found exit the loop and interpret the code
      if (existsInArray(results.value, AVAILABLE_CODES, 28) && results.value != INTENSITY_UP_CODE && results.value !=  INTENSITY_DN_CODE && results.value != MUSIC_CODE && results.value != MUSIC2_CODE && results.value != MUSIC3_CODE && results.value != MUSIC4_CODE) {
        Serial.println("return break");
        return; break;
        interpretRemoteCode(results.value);
      } else if (results.value == INTENSITY_UP_CODE) { // if the code is to raise or lower the speed
        raiseIntensity();                               // raise the speed
      } else if (results.value == INTENSITY_DN_CODE) {
        lowerIntensity();                               // or lower the speed
      }
      irrecv.resume();
    }


  //-----( MSGEG7 )-----

// Read the seven spectrum bands from the two MSGEQ7 chips
// ______________________ 1 ___________________________
 digitalWrite(ctrlReset, HIGH);                     // Pulse the reset signal
  digitalWrite(ctrlReset, LOW);                      // Causes MSGEQ7s to latch spectrum values
  delayMicroseconds(75);                             // Delay to meet minimum reset-to-strobe time

    digitalWrite(ctrlStrobe,LOW);                    // Read current band (then increment to next band)
    delayMicroseconds(50);                           // Wait for outputs to settle
     
    myData.spectrumRight1 = analogRead(channelRight) ; // Store current values from left & right channels. Divide 0-1023 by 4 to give 0-255
    
    if (myData.spectrumRight1 < 270) myData.spectrumRight1 = 0; // Filter out the noise at the bottom if there is no signal worth looking at
    
    digitalWrite(ctrlStrobe,HIGH);
    delayMicroseconds(50);                           // Delay to meet minimum strobe-to-strobe time
// ______________________ 2 ___________________________


    digitalWrite(ctrlStrobe,LOW);                    // Read current band (then increment to next band)
    delayMicroseconds(50);                           // Wait for outputs to settle
     
    myData.spectrumRight2 = analogRead(channelRight) ; // Store current values from left & right channels. Divide 0-1023 by 4 to give 0-255
    
    if (myData.spectrumRight2 < 270) myData.spectrumRight2 = 0; // Filter out the noise at the bottom if there is no signal worth looking at
    
    digitalWrite(ctrlStrobe,HIGH);
    delayMicroseconds(50);                           // Delay to meet minimum strobe-to-strobe time
// ______________________ 3 ___________________________
  

    digitalWrite(ctrlStrobe,LOW);                    // Read current band (then increment to next band)
    delayMicroseconds(50);                           // Wait for outputs to settle
     
    myData.spectrumRight3 = analogRead(channelRight) ; // Store current values from left & right channels. Divide 0-1023 by 4 to give 0-255
    
    if (myData.spectrumRight3 < 270) myData.spectrumRight3 = 0; // Filter out the noise at the bottom if there is no signal worth looking at
    
    digitalWrite(ctrlStrobe,HIGH);
    delayMicroseconds(50);                           // Delay to meet minimum strobe-to-strobe time
// ______________________ 4 ___________________________
  

    digitalWrite(ctrlStrobe,LOW);                    // Read current band (then increment to next band)
    delayMicroseconds(50);                           // Wait for outputs to settle
     
    myData.spectrumRight4 = analogRead(channelRight) ; // Store current values from left & right channels. Divide 0-1023 by 4 to give 0-255
    
    if (myData.spectrumRight4 < 270) myData.spectrumRight4 = 0; // Filter out the noise at the bottom if there is no signal worth looking at
    
    digitalWrite(ctrlStrobe,HIGH);
    delayMicroseconds(50);                           // Delay to meet minimum strobe-to-strobe time
// ______________________ 5 ___________________________
 

    digitalWrite(ctrlStrobe,LOW);                    // Read current band (then increment to next band)
    delayMicroseconds(50);                           // Wait for outputs to settle
     
    myData.spectrumRight5 = analogRead(channelRight) ; // Store current values from left & right channels. Divide 0-1023 by 4 to give 0-255
    
    if (myData.spectrumRight5 < 270) myData.spectrumRight5 = 0; // Filter out the noise at the bottom if there is no signal worth looking at
    
    digitalWrite(ctrlStrobe,HIGH);
    delayMicroseconds(50);                           // Delay to meet minimum strobe-to-strobe time
    // ______________________ 6 ___________________________
  

    digitalWrite(ctrlStrobe,LOW);                    // Read current band (then increment to next band)
    delayMicroseconds(50);                           // Wait for outputs to settle
     
    myData.spectrumRight6 = analogRead(channelRight) ; // Store current values from left & right channels. Divide 0-1023 by 4 to give 0-255
    
    if (myData.spectrumRight6 < 270) myData.spectrumRight6 = 0; // Filter out the noise at the bottom if there is no signal worth looking at
    
    digitalWrite(ctrlStrobe,HIGH);
    delayMicroseconds(50);                           // Delay to meet minimum strobe-to-strobe time
        // ______________________ 7 ___________________________


    digitalWrite(ctrlStrobe,LOW);                    // Read current band (then increment to next band)
    delayMicroseconds(50);                           // Wait for outputs to settle
     
    myData.spectrumRight7 = analogRead(channelRight) ; // Store current values from left & right channels. Divide 0-1023 by 4 to give 0-255
    
    if (myData.spectrumRight7 < 270) myData.spectrumRight7 = 0; // Filter out the noise at the bottom if there is no signal worth looking at
    
    digitalWrite(ctrlStrobe,HIGH);
    delayMicroseconds(50);                           // Delay to meet minimum strobe-to-strobe time


if ( myData.spectrumRight1 > 0){
 myData.spectrumRight1 = map(myData.spectrumRight1, 270, 1024, 0, 1024);
}
if ( myData.spectrumRight2 > 0){ 
 myData.spectrumRight2 = map(myData.spectrumRight2, 270, 1024, 0, 1024);
 }
if ( myData.spectrumRight3 > 0){ 
 myData.spectrumRight3 = map(myData.spectrumRight3, 270, 1024, 0, 1024);
 }
 if ( myData.spectrumRight4 > 0){ 
 myData.spectrumRight4 = map(myData.spectrumRight4, 270, 1024, 0, 1024);
 }
 if ( myData.spectrumRight5 > 0){ 
 myData.spectrumRight5 = map(myData.spectrumRight5, 270, 1024, 0, 1024);
 }
 if ( myData.spectrumRight6 > 0){ 
 myData.spectrumRight6 = map(myData.spectrumRight6, 270, 1024, 0, 1024);
 }
 if ( myData.spectrumRight7 > 0){ 
 myData.spectrumRight7 = map(myData.spectrumRight7, 270, 1024, 700, 900);
 }




int mappedSpeed = map(speedValue, 10, 1, 1000, 50000);
int crossfadespeed = 10;  
    unsigned long currentMillis3 = millis();
    unsigned long currentMillis2 = millis();


 if ( redVal == R && grnVal == G && bluVal == B && (currentMillis2 - previousMillis2 >= mappedSpeed)){
      previousMillis2 = currentMillis2;
    
   randomNumber_2 = random(5);
  R = AVAILABLE_COLORS[randomNumber_2][0];
  G = AVAILABLE_COLORS[randomNumber_2][1];
  B = AVAILABLE_COLORS[randomNumber_2][2]; 

   }

    if (currentMillis3 - previousMillis3 >= crossfadespeed) {
      previousMillis3 = currentMillis3;
       
if ( redVal < R ){
  redVal += 1;
}
   else if ( redVal > R ){
  redVal -= 1;    
   }  

if ( bluVal < B ){
  bluVal+= 1;
}
   else if ( bluVal > B ){
  bluVal-= 1;    
   }  

if ( grnVal < G ){
  grnVal+= 1;
}
   else if ( grnVal > G ){
  grnVal-= 1;    
   }  
}

myData.blue =  bluVal/4 + myData.spectrumRight6/60;
myData.green = grnVal/4;
myData.red = redVal/4 + myData.spectrumRight1/40;  

      if (!radio.write( &myData, sizeof(myData) )) {         
    }

}
}
