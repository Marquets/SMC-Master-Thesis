// Waveform Example - Create 2 waveforms with adjustable
// frequency and phase
//
// This example is meant to be used with 3 buttons (pin 0,
// 1, 2) and 2 knobs (pins 16/A2, 17/A3), which are present
// on the audio tutorial kit.
//   https://www.pjrc.com/store/audio_tutorial_kit.html
//
// Use an oscilloscope to view the 2 waveforms.
//
// Button0 changes the waveform shape
//
// Knob A2 changes the frequency of both waveforms
//   You should see both waveforms "stretch" as you turn
//
// Knob A3 changes the phase of waveform #1
//   You should see the waveform shift horizontally
//
// This example code is in the public domain.

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <ResponsiveAnalogRead.h>

// GUItool: begin automatically generated code

AudioSynthWaveform       waveform1;      //xy=392,118
AudioSynthWaveform       waveform2;      //xy=410,177
AudioMixer4              mixer3;    
AudioFilterStateVariable filter1;        //xy=758,136
AudioOutputI2S           i2s2;           //xy=931,198
AudioConnection          patchCord1(waveform1, 0, mixer3, 0);
AudioConnection          patchCord2(waveform2, 0, mixer3, 1);
AudioConnection          patchCord5(mixer3, 0, filter1, 0);
AudioConnection          patchCord6(filter1, 1, i2s2, 0);
AudioConnection          patchCord7(filter1, 1, i2s2, 1);


AudioControlSGTL5000     sgtl5000_1;     //xy=239,232

//Mux control pins for analog signal (Sig_pin)
const int S0 = 0;
const int S1 = 1;  
const int S2 = 2;  
const int S3 = 3;  

// Mux in "SIG" pin default
const int SIG_PIN = A0;  


//Mux 1 control pins for analog signal (Sig_pin)
const int W0 = 19;
const int W1 = 18;  
const int W2 = 17;  
const int W3 = 16;  

// Mux 1 in "SIG" pin default

const int WIG_PIN = 22;  

int current_waveform1 = 0;
int current_waveform2 = 0;
int waveforms[] = {WAVEFORM_SINE,WAVEFORM_SAWTOOTH, WAVEFORM_TRIANGLE, WAVEFORM_SQUARE,WAVEFORM_SAWTOOTH_REVERSE,WAVEFORM_PULSE};

float lowestNotes[] = {41.204 * 4,55 * 4,73.416 * 4,97.999 * 4};

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
  AudioMemory(20);

  // Comment these out if not using the audio adaptor board.
  // This may wait forever if the SDA & SCL pins lack
  // pullup resistors
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5); // caution: very loud - use oscilloscope only!

  current_waveform1 = WAVEFORM_SINE;
  waveform1.begin(current_waveform1);
  current_waveform2 = WAVEFORM_SINE;
  waveform2.begin(current_waveform2);


}

void loop() {
  // Read the buttons and knobs, scale knobs to 0-1.0



  float freq = 0.0;
  int i = 0;
  while( i < 4) {
    int index = map(readMux(0 + i*3), 0, 1023,0,21);
    int cut_off = (readMux(1 + i*3) / 1023.0) * 200.0;
    int cut_off2 = (readMux(2 + i*3) / 1023.0) * 1000.0;
    double pitchbend = map(readMux(2 + i*3), 500, 1023,0.000,21.000);

   // float general_vol = map(readMux2(0), 0, 1023, 0, 0.7);
    int wave = map(readMux2(0), 0, 1023, 0, 5);
    int wave2 = map(readMux2(7), 0, 1023, 0, 5);

    Serial.println(readMux2(1));
  
        
    freq = lowestNotes[i] * shruti[index];
    
    if (freq != lowestNotes[i]) {
      
      filter1.frequency(cut_off2);
      filter1.resonance(1);
      
      waveform1.begin(waveforms[wave]);
      waveform1.frequency(freq/2);
      waveform1.amplitude(1.0);

      waveform2.begin(waveforms[wave2]);
      waveform2.frequency(freq*2);
      waveform2.amplitude(1);

      //sgtl5000_1.volume(general_vol);
    } 
  
    else {
      
      waveform1.amplitude(0);
      waveform2.amplitude(0); 
      sgtl5000_1.disable();
      i++;
    }
  
  }




//  if (analog5.hasChanged()) {
//    waveform1.begin(waveforms[wave]);
//  }
//
//  if (analog6.hasChanged()) {
//  waveform2.begin(waveforms[wave2]);
//  }
//
//  if (analog7.hasChanged()) {
//  waveform1.phase(analog7.getValue() * 360.0);
//  }

  //AudioNoInterrupts();
  // use Knob A2 to adjust the frequency of both waveforms
  //waveform1.frequency(100.0 + knob_A2 * 900.0);
  //waveform2.frequency(100.0 + knob_A2 * 900.0);
  // use Knob A3 to adjust the phase of only waveform #1
  //waveform1.phase(knob_A3 * 360.0);
  //AudioInterrupts();

   //Serial.println(analog4.getValue());
   //Serial.println(readMux(3));

  delay(5);

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
    Serial.println(analogRead(WIG_PIN));

  //return the value
  return val;
}
