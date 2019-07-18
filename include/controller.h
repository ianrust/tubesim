
#include "audio.h"

#ifdef GOALS
const int ledsPerStrip = 300;
#define GET_COLOR getGoalsColorPortable
#endif
#ifdef LINES
const int ledsPerStrip = 600;
#define GET_COLOR getLinesColorPortable
#endif


int tick = 0;

#ifndef RECORD
#include "patterns.h"
#include <OctoWS2811.h>

int ledIndex = 0;
Color8bit color;

DMAMEM int displayMemory[ledsPerStrip*6];
int drawingMemory[ledsPerStrip*6];

const int config = WS2811_GRB | WS2811_800kHz;

OctoWS2811 leds(ledsPerStrip, displayMemory, drawingMemory, config);

bool indicator = false;

void setup() {
  leds.begin();

  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);

  setupSpectrum();
  delay(100);
}

void loop() {
  for (ledIndex = 0; ledIndex < leds.numPixels() ; ledIndex++) {
    readFrequenciesTimed();
    Color8bit color = GET_COLOR(ledIndex, tick, false, false, freq_out);
    leds.setPixel(ledIndex, color.r, color.g, color.b);
  }
  leds.show();
  tick++;

  // slow indicator loop
  if (tick % 10 == 0) {
    indicator = !indicator;
    digitalWrite(LED_BUILTIN, indicator);
    spectrumPlot();
  }
}
#else

uint64_t sample_period_micros = 3333; // 30 Hz
uint64_t last_micros_sample = 0;

char serialized_freq[14];

void setup() {
  Serial.begin(115200);
  delay(1000);
  setupSpectrum();
  delay(100);
}

void loop() {
  if (last_micros_sample == 0) {
    last_micros_sample = micros();
  }
  readFrequenciesTimed();
  if ((current_micros - last_micros_sample) > sample_period_micros) {
    last_micros_sample += sample_period_micros;
    memcpy(serialized_freq, freq_out, sizeof(freq_out));
    Serial.write(serialized_freq, sizeof(serialized_freq));
    Serial.write("\n");
  }
  tick++;
}

#endif