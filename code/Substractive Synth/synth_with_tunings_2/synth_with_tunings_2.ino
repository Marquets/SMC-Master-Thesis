 // Waveform Example - Create 2 waveforms with adjustable
// frequency and phase


#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <ResponsiveAnalogRead.h>

// GUItool: begin automatically generated code

AudioSynthWaveform       waveform1;      //xy=392,118
AudioSynthWaveform       waveform2;      //xy=410,177
AudioSynthWaveform       waveform3;      //xy=392,118
AudioSynthWaveform       waveform4;      //xy=410,177
AudioMixer4              mixer3;    
AudioFilterStateVariable filter1;        //xy=758,136
AudioOutputI2S           i2s2;           //xy=931,198
AudioConnection          patchCord1(waveform1, 0, mixer3, 0);
AudioConnection          patchCord2(waveform2, 0, mixer3, 1);
AudioConnection          patchCord3(waveform3, 0, mixer3, 2);
AudioConnection          patchCord4(waveform4, 0, mixer3, 3);
AudioConnection          patchCord5(mixer3, 0, filter1, 0);
AudioConnection          patchCord6(filter1, 1, i2s2, 0);
AudioConnection          patchCord7(filter1, 1, i2s2, 1);


AudioControlSGTL5000     sgtl5000_1;     //xy=239,232

//Mux control pins for analog signal (Sig_pin) ==> SENSORS
const int S0 = 0;
const int S1 = 1;  
const int S2 = 2;  
const int S3 = 3;  

// Mux in "SIG" pin default
const int SIG_PIN = A0;  


//Mux 1 control pins for analog signal (Sig_pin) ==> KNOBS
const int W0 = 19;
const int W1 = 18;  
const int W2 = 17;  
const int W3 = 16;  

// Mux 1 in "SIG" pin default

const int WIG_PIN = 22;  

int current_waveform1 = 0;
int current_waveform2 = 0;
int current_waveform3 = 0;
int current_waveform4 = 0;
int waveforms[] = {WAVEFORM_SINE,WAVEFORM_SAWTOOTH, WAVEFORM_TRIANGLE, WAVEFORM_SQUARE};

float lowestNotes[] = {(41.204 * 4), (55*4) , (73.416 * 4), (97.999 * 4)};

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


float just_intonation[] = {1,(float)256/243,(float)9/8,(float)32/27,(float)81/64,(float)4/3,(float)729/512,(float)3/2,(float)128/81,(float)27/16,(float)16/9,(float)243/128,2};

float shruti[] = {1,(float)256/243,(float)16/15,(float)10/9,(float)9/8,(float)32/27,(float)6/5,(float)5/4,(float)81/64,(float)4/3,(float)27/20,(float)45/32,(float)729/512,(float)3/2,
                  (float)128/81, (float)8/5, (float) 5/3, (float)27/16, (float)16/9, (float)9/5, (float)15/8, (float)243/128,2};


float quarter_tone[] = {1,(float)33/32,(float)17/16,(float)12/11,(float)9/8,(float)22/19,(float)19/16,(float)11/9,(float)24/19,(float) 22/17,(float)4/3,(float)11/8,(float)17/12,(float)16/11,
                  (float)3/2, (float)17/11, (float) 19/12, (float)18/11, (float)32/19, (float)16/9, (float)11/6, (float)33/17,2};

float equal[] ={1, (float) pow(2,1/12), (float) pow(2,3/12),(float) pow(2,4/12),(float)  pow(2,5/12),(float)  pow(2,6/12),(float)  pow(2,7/12),(float)  pow(2,8/12),(float) pow(2,9/12),(float) pow(2,10/12),(float) pow(2,11/12),2};

int tonal_index[] = {12,22,22,11};

void setup() {
  Serial.begin(9600);
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

  // Audio connections require memory to work.  For more
  // detailed information, see the MemoryAndCpuUsage example
  AudioMemory(30);


  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5); // caution: very loud - use oscilloscope only!

  current_waveform1 = WAVEFORM_SINE;
  waveform1.begin(current_waveform1);
  current_waveform2 = WAVEFORM_SINE;
  waveform2.begin(current_waveform2);
  current_waveform3 = WAVEFORM_SINE;
  waveform3.begin(current_waveform3);
  current_waveform4 = WAVEFORM_SINE;
  waveform4.begin(current_waveform4);


}

void loop() {

int tonal = map(readMux(4,false), 0, 1023, 0, 3); 
int freq_s1 = 0, freq_s2 = 0, freq_s3 = 0, freq_s4 = 0;   

Serial.println(tonal);

// SOFTPOT 1
    int cut_off_s1 = (readMux(1,true) / 1023.0) * 100.0;
    int cut_off2_s1 = (readMux(2,true) / 1023.0) * 1000.0;
    int index_s1 = map(readMux(0,true), 0, 1023,0,tonal_index[tonal]);


// SOFTPOT 2

    int cut_off_s2 = (readMux(4,true) / 1023.0) * 100.0;
    int cut_off2_s2 = (readMux(5,true) / 1023.0) * 1000.0;
    int index_s2 = map(readMux(3,true), 100, 1023,0,tonal_index[tonal]);

//
//    Serial.println(readMux(3,true));

// SOFTPOT 3

    int cut_off_s3 = (readMux(7,true) / 1023.0) * 100.0;
    int cut_off2_s3 = (readMux(8,true) / 1023.0) * 1000.0;
    int index_s3 = map(readMux(6,true), 90, 1023,0,tonal_index[tonal]);


//// SOFTPOT 4
//
//    int cut_off_s4 = (readMux(10,true) / 1023.0) * 100.0;
//    int cut_off2_s4 = (readMux(11,true) / 1023.0) * 1000.0;
//    int index_s4 = map(readMux(9,true), 90, 1023,0,12);


    if (tonal == 0) {
      freq_s1 = lowestNotes[0] * shruti[index_s1];
      freq_s2 = lowestNotes[1] * shruti[index_s2];
      freq_s3 = lowestNotes[2] * shruti[index_s3];
    }

    if (tonal == 1) {
      freq_s1 = lowestNotes[0] * just_intonation[index_s1];
      freq_s2 = lowestNotes[1] * just_intonation[index_s2];
      freq_s3 = lowestNotes[2] * just_intonation[index_s3];
    }

    if (tonal == 2) {
      freq_s1 = lowestNotes[0] * quarter_tone[index_s1];
      freq_s2 = lowestNotes[1] * quarter_tone[index_s2];
      freq_s3 = lowestNotes[2] * quarter_tone[index_s3];
    }  

    if (tonal == 3) {
      freq_s1 = lowestNotes[0] * equal[index_s1];
      freq_s2 = lowestNotes[1] * equal[index_s2];
      freq_s3 = lowestNotes[2] * equal[index_s3];
    }
      
   
    int wave = map(readMux(0, false), 0, 1023, 0, 3);
    int wave2 = map(readMux(1, false), 0, 1023, 0, 3);

    Serial.println(readMux(4,false));
    
    if (freq_s1 > lowestNotes[0]) {
      
      waveform1.begin(waveforms[wave]);
      waveform1.frequency(freq_s1);
      waveform1.amplitude(1.0);
      delay(20);
      //sgtl5000_1.volume(general_vol);
    } 

    else {
      waveform1.amplitude(0);
      sgtl5000_1.disable();
      
    }

    if (freq_s2 > lowestNotes[1]) {


      waveform2.begin(waveforms[wave2]);
      waveform2.frequency(freq_s2);
      waveform2.amplitude(1);

      delay(20);
      //sgtl5000_1.volume(general_vol);
    } 
    else {
      
      waveform2.amplitude(0); 
      sgtl5000_1.disable();
      
    }

    if (freq_s3 > lowestNotes[3]) {


      waveform3.begin(waveforms[wave]);
      waveform3.frequency(freq_s3);
      waveform3.amplitude(1);

      delay(20);
      //sgtl5000_1.volume(general_vol);
    } 

    else {
      
      waveform3.amplitude(0); 
      sgtl5000_1.disable();
      
    }

    

 
  delay(5);

}

int readMux(byte channel, bool mux){
  byte controlPin[] = {S0, S1, S2, S3};
  byte controlPin2[] = {W0, W1, W2, W3};
  if (mux) {
    for(int i = 0; i < 4; i ++){
      digitalWrite(controlPin[i], muxChannel[channel][i]);
    }

  }
  else {
    for(int i = 0; i < 4; i ++){
      digitalWrite(controlPin2[i], muxChannel[channel][i]);
    }
  }
  //analog.update();
  //loop through the 4 sig
  delayMicroseconds(50);
  int val = 0;
  //read the value at the SIG pin
  if (mux) {
    val = analogRead(SIG_PIN);
  }
  else {
    val = analogRead(WIG_PIN);
  }
  

  //return the value
  return val;
}
