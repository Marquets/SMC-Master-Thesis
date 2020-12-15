/******************************************************************************
Midi_mode.ino

- This code is in charge of all the functionality made by the instrument when is working as 
a midi controller. 

Development environment specifics:
Arduino 1.6.7
Marco González Pérez
******************************************************************************/

//Mux 1 receiving the signal from the sensors. Defnitions of the control pins for analog signal (Sig_pin)
const int S0 = 0;
const int S1 = 1;  
const int S2 = 2;  
const int S3 = 3;  

// Mux 1 in "SIG" pin default
const int SIG_PIN = A0;  


//Mux 1 receiving the signal from the pots. Defnitions of the control pins for analog signal (Sig_pin)
const int W0 = 19;
const int W1 = 18;  
const int W2 = 17;  
const int W3 = 16;  

// Mux 2 in "SIG" pin default

const int WIG_PIN = A8;  

// Global variables

// Tonal systems pitchbend ranges
int just_intonation[] = {-7560, -6300, -5040, -3780, -2520, -1260, 0, 1260, 2520, 3780, 5040, 6300, 7560};

// Midi channels
const int midi_channel1 = 1;
const int midi_channel2 = 2;
const int midi_channel3 = 3;
const int midi_channel4 = 4;

// Thresholds
const int threshold_pot1 = 35; //
const int threshold_pot2 = 100; //
const int threshold_pot3 = 35; //
const int threshold_pot4 = 35; //

// Reference notes from each softpot.
const int refNote1 = 40; // E2 = 82.407 Hz
const int refNote2 = 45; // A2 = 110.0 Hz
const int refNote3 = 50; // D3 = 146.83 Hz
const int refNote4 = 55; // G2 = 196.00 Hz

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

elapsedMillis pitchUpdate;
const int MIDIdelay = 2; // will update MIDI only if this many milliseconds have passed

void setup() 
{
  Serial.begin(9600);
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);

  pinMode(W0, OUTPUT);
  pinMode(W1, OUTPUT);
  pinMode(W2, OUTPUT);
  pinMode(W3, OUTPUT);

  digitalWrite(S0, LOW);
  digitalWrite(S1, LOW);
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);

  digitalWrite(W0, LOW);
  digitalWrite(W1, LOW);
  digitalWrite(W2, LOW);
  digitalWrite(W3, LOW);

}

void loop() 
{
  
  // Read in the softpot's  and FSR ADC value
  
  int softPotADC1 = readMux(0, true);
  int fsr_1 = readMux(1, true);
  int fsr2_1 = readMux(2, true);
  
  int softPotADC2 = readMux(3 , true);
  int fsr_2 = readMux(4, true);
  int fsr2_2 = readMux(5, true);

  int softPotADC3 = readMux(6, true);
  int fsr_3 = readMux(7, true);
  int fsr2_3 = readMux(8, true);

  int softPotADC4 = readMux(9, true);
  int fsr_4 = readMux(10, true);
  int fsr2_4 = readMux(11, true);

  int knob1 = map(readMux(0, false), 0, 1023, 0, 127);
  int knob2 = map(readMux(1, false), 0, 1023, 0, 127);
  int knob3 = map(readMux(2, false), 0, 1023, 0, 127);
  int knob4 = map(readMux(3, false), 0, 1023, 0, 127);
  int knob5 = map(readMux(4, false), 0, 1023, 0, 127);
  int knob6 = map(readMux(5, false), 0, 1023, 0, 127);
  int knob7 = map(readMux(6, false), 0, 1023, 0, 127);
  int knob8 = map(readMux(7, false), 0, 1023, 0, 127);

  Serial.println(softPotADC2);
  
  int vel1 = map(fsr_1, 800, 1023,0, 127); 
  int pitch1 = map(softPotADC1, 0, 1023,-8192, 8192);
  int fsr_control1 = map(fsr2_1, 700, 1023,0, 127);  

  int vel2 = map(fsr_2, 800, 1023,0, 127); 
  int pitch2 = map(softPotADC2, 0, 1023,-8192, 8192);
  int fsr_control2 = map(fsr2_2, 700, 1023,0, 127);  


  int vel3 = map(fsr_3, 800, 1023,0, 127); 
  int pitch3 = map(softPotADC3, 0, 1023,-8192, 8192);
  int fsr_control3 = map(fsr2_3, 700, 1023,0, 127);  

  int vel4 = map(fsr_4, 800, 1023,0, 127); 
  int pitch4 = map(softPotADC4, 0, 1023,-8192, 8192);
  int fsr_control4 = map(fsr2_4, 700, 1023,0, 127);  
 
  if (softPotADC1 > threshold_pot1) {
   
      usbMIDI.sendNoteOn(refNote1, vel1, midi_channel1);
      usbMIDI.sendPitchBend(pitch1, midi_channel1); // pitch bend down 0 - 8192 // pitch bend up 16383
      
  } else{
      usbMIDI.sendNoteOff(refNote1, 0, midi_channel1);
  }

 
  if (softPotADC2 > threshold_pot2) {
   
      usbMIDI.sendNoteOn(refNote2, vel2, midi_channel2);
      usbMIDI.sendPitchBend(pitch2, midi_channel2); // pitch bend down 0 - 8192 // pitch bend up 16383
      
  } else{
      usbMIDI.sendNoteOff(refNote2, 0, midi_channel2);
  }


 if (softPotADC3 > threshold_pot3) {
   
      usbMIDI.sendNoteOn(refNote3, vel3, midi_channel3);
      usbMIDI.sendPitchBend(pitch3, midi_channel3); // pitch bend down 0 - 8192 // pitch bend up 16383
      
  } else{
      usbMIDI.sendNoteOff(refNote3, 0, midi_channel3);
  }

 if (softPotADC4 > threshold_pot4) {
   
      usbMIDI.sendNoteOn(refNote4, vel4, midi_channel4);
      usbMIDI.sendPitchBend(pitch4, midi_channel4); // pitch bend down 0 - 8192 // pitch bend up 16383
      
  } else{
      usbMIDI.sendNoteOff(refNote4, 0, midi_channel4);
  }

  // SOFTPOT 1 Control change messages produced by moving the knobs
  
  usbMIDI.sendControlChange(101, 0, midi_channel1);
  usbMIDI.sendControlChange(100, 0, midi_channel1);
  usbMIDI.sendControlChange(66, 12, midi_channel1);
  usbMIDI.sendControlChange(1, knob1, midi_channel1);
  usbMIDI.sendControlChange(2, knob2, midi_channel1);
  usbMIDI.sendControlChange(7, knob3, midi_channel1); //*
  usbMIDI.sendControlChange(11, knob4, midi_channel1);
  usbMIDI.sendControlChange(71, knob5, midi_channel1);
  usbMIDI.sendControlChange(74, knob6, midi_channel1);
  usbMIDI.sendControlChange(75, knob7, midi_channel1);
  usbMIDI.sendControlChange(76, knob8, midi_channel1);
  usbMIDI.sendControlChange(79, fsr_control1, midi_channel1);

  // SOFTPOT 2 Control change messages produced by moving the knobs
  
  usbMIDI.sendControlChange(101, 0, midi_channel2);
  usbMIDI.sendControlChange(100, 0, midi_channel2);
  usbMIDI.sendControlChange(66, 12, midi_channel2);
  usbMIDI.sendControlChange(1, knob1, midi_channel2);
  usbMIDI.sendControlChange(2, knob2, midi_channel2);
  usbMIDI.sendControlChange(7, knob3, midi_channel2); 
  usbMIDI.sendControlChange(11, knob4, midi_channel2);
  usbMIDI.sendControlChange(71, knob5, midi_channel2);
  usbMIDI.sendControlChange(74, knob6, midi_channel2);
  usbMIDI.sendControlChange(75, knob7, midi_channel2);
  usbMIDI.sendControlChange(76, knob8, midi_channel2);
  usbMIDI.sendControlChange(79, fsr_control1, midi_channel2);
  
  // SOFTPOT 3 Control change messages produced by moving the knobs
  
  usbMIDI.sendControlChange(101, 0, midi_channel3);
  usbMIDI.sendControlChange(100, 0, midi_channel3);
  usbMIDI.sendControlChange(66, 12, midi_channel3);
  usbMIDI.sendControlChange(1, knob1, midi_channel3);
  usbMIDI.sendControlChange(2, knob2, midi_channel3);
  usbMIDI.sendControlChange(7, knob3, midi_channel3); 
  usbMIDI.sendControlChange(11, knob4, midi_channel3);
  usbMIDI.sendControlChange(71, knob5, midi_channel3);
  usbMIDI.sendControlChange(74, knob6, midi_channel3);
  usbMIDI.sendControlChange(75, knob7, midi_channel3);
  usbMIDI.sendControlChange(76, knob8, midi_channel3);
  usbMIDI.sendControlChange(79, fsr_control1, midi_channel3);
    
  // SOFTPOT 4
  
  usbMIDI.sendControlChange(101, 0, midi_channel4);
  usbMIDI.sendControlChange(100, 0, midi_channel4);
  usbMIDI.sendControlChange(66, 12, midi_channel4);
  usbMIDI.sendControlChange(1, knob1, midi_channel4);
  usbMIDI.sendControlChange(2, knob2, midi_channel4);
  usbMIDI.sendControlChange(7, knob3, midi_channel4); 
  usbMIDI.sendControlChange(11, knob4, midi_channel4);
  usbMIDI.sendControlChange(71, knob5, midi_channel4);
  usbMIDI.sendControlChange(74, knob6, midi_channel4);
  usbMIDI.sendControlChange(75, knob7, midi_channel4);
  usbMIDI.sendControlChange(76, knob8, midi_channel4);
  usbMIDI.sendControlChange(79, fsr_control1, midi_channel4);


  //Serial.println(touchRead(1));
  while (usbMIDI.read()) {} //  ignore all incoming messages
  delay(5);


}

// This function reads the ADC value from the channels of the multiplexer.

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
  delayMicroseconds(50);
  int val = 0;
  //read the value at the SIG pin
  if (mux) {
    val = analogRead(SIG_PIN);
  }
  else {
    val = analogRead(WIG_PIN);
  }
  
  return val;
}
