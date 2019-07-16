#include <OctoWS2811.h>

//Declare Spectrum Shield pin connections
#define STROBE 29
#define RESET 30
#define DC_One A12
#define DC_Two A13

const int ledsPerStrip = 600;

DMAMEM int displayMemory[ledsPerStrip*8];
int drawingMemory[ledsPerStrip*8];

const int config = WS2811_GRB | WS2811_800kHz;

OctoWS2811 leds(ledsPerStrip, displayMemory, drawingMemory, config);

unsigned long last_spectrum_read_micros = 0;
unsigned long spectrum_read_period_micros = 15000;
unsigned long current_micros;

unsigned long last_micros = 0;

float max_band;

float dominant_bass;
float dominant_vocal;
bool  active_snare;
float bin_centroid;

//Define spectrum variables
int freq_amp;
int Frequencies_L[7];
int Frequencies_L_tare[7];
int Frequencies_R[7];
int Frequencies_R_tare[7];
float Frequencies_mixed[7];
float Frequencies_mixed_filtered[7];
int i;

// 63Hz, 160Hz, 400Hz, 1kHz, 2.5kHz, 6.25kHz, 16kHz
float Bands[7] = {63.0, 160.0, 400.0, 1000.0, 2500.0, 6250.0, 16000.0};

float filter_factor[7] = {0.15, 0.15, 0.15, 0.15, 0.25, 0.25, 0.25};

void setup() {
  leds.begin();
  leds.show();
  Serial.begin(9600);
  Init_Spectrum();
  Zero_Spectrum();
}

void loop() {
  for (i=0; i < leds.numPixels(); i++) {
    Read_Frequencies_Timed();
//    leds.setPixel(i, );
  }
//  Serial.print("i: ");
//  Serial.println(i);
  Serial.print("dominant_vocal");
  Serial.println(dominant_vocal);
  Serial.println((dominant_vocal-Bands[2])/(Bands[3]-Bands[2]));
  Serial.println(bin_centroid);
  Serial.print("fps: ");
  Serial.println(1000000.0/float(micros() - last_micros));
  last_micros = micros();

  Spectrum_Plot();
  leds.show();
}


void Init_Spectrum(){
  pinMode(STROBE, OUTPUT);
  pinMode(RESET, OUTPUT);
  pinMode(DC_One, INPUT);
  pinMode(DC_Two, INPUT);
  digitalWrite(STROBE, HIGH);
  digitalWrite(RESET, HIGH);

  //Initialize Spectrum Analyzers
  digitalWrite(STROBE, LOW);
  delay(1);
  digitalWrite(RESET, HIGH);
  digitalWrite(STROBE, HIGH);
  delay(1);
  digitalWrite(STROBE, LOW);
  delay(1);
  digitalWrite(RESET, LOW);
  digitalWrite(STROBE, HIGH);
  delay(1);

  last_spectrum_read_micros = micros();
}

void Zero_Spectrum() {
  Read_Frequencies();
  for (freq_amp = 0; freq_amp<7; freq_amp++) {
    Frequencies_L_tare[freq_amp] = Frequencies_L[freq_amp];
    Frequencies_R_tare[freq_amp] = Frequencies_R[freq_amp];
  }
}

void Spectrum_Plot() {
  for (freq_amp = 0; freq_amp<7; freq_amp++)
  {
    Serial.print(Frequencies_mixed[freq_amp]);
    Serial.print(" ");
  }
  Serial.println("");
  for (freq_amp = 0; freq_amp<7; freq_amp++)
  {
    Serial.print(Frequencies_mixed_filtered[freq_amp]);
    Serial.print(" ");
  }
  Serial.println("");
  for (int level_bin = 0; level_bin <= 1000; level_bin+=100) {
    for (freq_amp = 0; freq_amp<7; freq_amp++)
    {
      if (Frequencies_mixed_filtered[freq_amp] > level_bin) {
        Serial.print("@");
      } else{
        Serial.print(" ");
      }
    }
    Serial.println("");
  }
}


float Compute_Max() {
  int max_band_level = 0;
  float max_band;

  for (freq_amp = 0; freq_amp<7; freq_amp++) {
    if (Frequencies_mixed[freq_amp] > max_band_level) {
      max_band_level = Frequencies_mixed[freq_amp];
      max_band = Bands[freq_amp];
    }
  }
  return max_band;
}

float Compute_Bin_Centroid() {
  float numen = 0;
  float denom = 0;

  for (freq_amp = 0; freq_amp<7; freq_amp++) {
    numen += freq_amp * Frequencies_mixed_filtered[freq_amp];
    denom += Frequencies_mixed_filtered[freq_amp];
  }
  return numen/denom;
}

void Read_Frequencies_Timed() {
  current_micros = micros();
  if (current_micros - last_spectrum_read_micros > spectrum_read_period_micros) {
    last_spectrum_read_micros += spectrum_read_period_micros;
    Read_Frequencies();
    Filter_Frequencies();

    dominant_bass = (Frequencies_mixed_filtered[0] * Bands[0] + Frequencies_mixed_filtered[1] * Bands[1]) / (Frequencies_mixed_filtered[0] + Frequencies_mixed_filtered[1]);
    dominant_vocal = (Frequencies_mixed_filtered[2] * Bands[2] + Frequencies_mixed_filtered[3] * Bands[3]) / (Frequencies_mixed_filtered[2] + Frequencies_mixed_filtered[3]);
    active_snare = Frequencies_mixed[6] > 600 || Frequencies_mixed[5] > 600;
    bin_centroid = Compute_Bin_Centroid();
  }
}


void Filter_Frequencies() {

  for (freq_amp = 0; freq_amp<7; freq_amp++) {
    Frequencies_mixed_filtered[freq_amp] =  (1-filter_factor[freq_amp]) * Frequencies_mixed_filtered[freq_amp] + filter_factor[freq_amp] * Frequencies_mixed[freq_amp];
  }
}


/*******************Pull frquencies from Spectrum Shield********************/
void Read_Frequencies(){
  //Read frequencies for each band
  for (freq_amp = 0; freq_amp<7; freq_amp++)
  {
    digitalWrite(STROBE, LOW);
    delayMicroseconds(20);
    Frequencies_L[freq_amp] = analogRead(DC_One) - Frequencies_L_tare[freq_amp];
    Frequencies_R[freq_amp] = analogRead(DC_Two) - Frequencies_R_tare[freq_amp];
    Frequencies_mixed[freq_amp] = Frequencies_L[freq_amp]/2.0 + Frequencies_R[freq_amp]/2.0;
    digitalWrite(STROBE, HIGH);
  }
}