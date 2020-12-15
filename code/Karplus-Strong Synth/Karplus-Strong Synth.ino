#include <Audio.h>
#include <Wire.h>
#include <SD.h>
#include <SPI.h>
#include <SerialFlash.h>
#include "modularInterpInstrMIDI.h"
#include <ResponsiveAnalogRead.h>

modularInterpInstrMIDI karplus;
AudioOutputI2S out;
AudioControlSGTL5000 audioShield;
AudioAmplifier amp1;
AudioConnection patchCord0(karplus,0,amp1,0);
AudioConnection patchCord1(amp1,0,out,0);
AudioConnection patchCord2(amp1,0,out,1);

//Mux 1 control pins for analog signal (Sig_pin)
const int S0 = 0;
const int S1 = 1;  
const int S2 = 2;  
const int S3 = 3;  

// Mux 1 in "SIG" pin default
const int SIG_PIN = A0;  


//Mux 2 control pins for analog signal (Sig_pin)
const int W0 = 19;
const int W1 = 18;  
const int W2 = 17;  
const int W3 = 16;  

// Mux 2 in "SIG" pin default

const int WIG_PIN = 22;  

//Array of values for selecting the disered channel of the multiplexers
const boolean muxChannel[16][4] = {
  {0, 0, 0, 0}, //channel 0
  {1, 0, 0, 0}, //channel 1
  {0, 1, 0, 0}, //channel 2
  {1, 1, 0, 0}, //channel 3
  {0, 0, 1, 0}, //channel 4
  {1, 0, 1, 0}, //channel 5
  {0, 1, 1, 0}, //channel 6
  {1, 1, 1, 0}, //channel 7
  {0, 0, 0, 1}, //channel 8
  {1, 0, 0, 1}, //channel 9
  {0, 1, 0, 1}, //channel 10
  {1, 1, 0, 1}, //channel 11
  {0, 0, 1, 1}, //channel 12
  {1, 0, 1, 1}, //channel 13
  {0, 1, 1, 1}, //channel 14
  {1, 1, 1, 1} //channel 15
};

float lowestNotes[] = {41.204 * 4, 55 * 4 , 73.416 * 4 , 97.999 * 4};

float previous_note = 0;

float just_intonation[] = {1,(float)256/243,(float)9/8,(float)32/27,(float)81/64,(float)4/3,(float)729/512,(float)3/2,(float)128/81,(float)27/16,(float)16/9,(float)243/128,2};

float shruti[] = {1,(float)256/243,(float)16/15,(float)10/9,(float)9/8,(float)32/27,(float)6/5,(float)5/4,(float)81/64,(float)4/3,(float)27/20,(float)45/32,(float)729/512,(float)3/2,
                  (float)128/81, (float)8/5, (float) 5/3, (float)27/16, (float)16/9, (float)9/5, (float)15/8, (float)243/128,2};



float quarter_tone[] = {1,(float)33/32,(float)17/16,(float)12/11,(float)9/8,(float)22/19,(float)19/16,(float)11/9,(float)24/19,(float) 22/17,(float)4/3,(float)11/8,(float)17/12,(float)16/11,
                  (float)3/2, (float)17/11, (float) 19/12, (float)18/11, (float)32/19, (float)16/9, (float)11/6, (float)33/17,2};

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(9600);
  
  AudioMemory(15);

  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(SIG_PIN, INPUT);


  pinMode(W0, OUTPUT);
  pinMode(W1, OUTPUT);
  pinMode(W2, OUTPUT);
  pinMode(W3, OUTPUT);
  //pinMode(WIG_PIN, INPUT);
  
  digitalWrite(S0, LOW);
  digitalWrite(S1, LOW);
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);

  digitalWrite(W0, LOW);
  digitalWrite(W1, LOW);
  digitalWrite(W2, LOW);
  digitalWrite(W3, LOW);

  audioShield.enable();
  audioShield.volume(0.9);
  amp1.gain(0.5);
}

void loop() {
  // put your main code here, to run repeatedly:
  int i = 0;
  while( i < 4) {
    float freq = 0.0;

    // Reading values from sensors and knobs
    
    int index = map(readMux(0 + i*3), 0, 1023,0,12);
    float fsr = map(readMux(1 + i*3), 0, 1023, 1.0, 2.0);
    float fsr2 = map(readMux(2 + i*3), 0, 1023, -2.0, 1.0);
    float pluck = (float) readMux2(6) / 1023;
    float body_shape = (float) readMux2(7) / 1023;
    float body_scale = (float) readMux2(5) / 1023;
    int tonal =  map(readMux2(4), 0, 1023, 0, 4);

// Applying the corresponding ratios depending on the tonal system

    if ( tonal == 0) {
      int index = map(readMux(0 + i*3), 0, 1023,0,12);
      freq = lowestNotes[i] * just_intonation[index];
    }

    else if (tonal == 1) {
      int index = map(readMux(0 + i*3), 0, 1023,0,21);
      freq = lowestNotes[i] * shruti[index];
    }

    else if (tonal == 2) {
      int index = map(readMux(0 + i*3), 0, 1023,0,22);
      freq = lowestNotes[i] * quarter_tone[index];
    }


    else if (tonal == 3) {
      freq =  map(readMux(0 + i*3), 0, 1023,lowestNotes[i],lowestNotes[i] + (2 * 12)); 
    }

    else if (tonal == 4) {
      freq =  map(readMux(0 + i*3), 0, 1023,lowestNotes[i],lowestNotes[i] + (2 * 24)); 

    }


    if (freq > lowestNotes[i]) {
 
        karplus.setParamValue("gate",1);
        karplus.setParamValue("gain",0.5);
        karplus.setParamValue("pluckPosition",pluck);
        karplus.setParamValue("freq",freq);
        //karplus.setParamValue("bend",fsr2);
        karplus.setParamValue("shape",body_shape);
        karplus.setParamValue("scale",body_scale);
        //delay(20);
        
    }

    else {
      audioShield.disable();
      karplus.setParamValue("gain",0);
      karplus.setParamValue("gate",0);
      i++;
    }

  }
}



int readMux(byte channel){
  byte controlPin[] = {S0, S1, S2, S3};
  //byte controlPin2[] = {W0, W1, W2, W3};

  for(int i = 0; i < 4; i ++){
    digitalWrite(controlPin[i], muxChannel[channel][i]);
  }
  //read the value at the SIG pin

    delayMicroseconds(50);
    int val = analogRead(SIG_PIN);

  //return the value
  return val;
}

int readMux2(byte channel){
  byte controlPin[] = {W0, W1, W2, W3};

  for(int i = 0; i < 4; i ++){
    digitalWrite(controlPin[i], muxChannel[channel][i]);
    //Serial.println(muxChannel[channel][i]);
  }
  //read the value at the SIG pin

    delayMicroseconds(50);
    int val = analogRead(WIG_PIN);
    //Serial.println(val);


  //return the value
  return val;
}
