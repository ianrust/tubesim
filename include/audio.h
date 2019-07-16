//Declare Spectrum Shield pin connections
#define STROBE 29
#define RESET 30
#define DC_One A12
#define DC_Two A13

uint16_t raw_left[7];
uint16_t raw_right[7];
uint16_t raw[7];

float lpf_alpha[7] = {0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1};
uint16_t lpf_output[7] = {0, 0, 0, 0, 0, 0, 0};

void setupSpectrum() {
  //Set spectrum Shield pin configurations
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
}