
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
    Color8bit color = GET_COLOR(ledIndex, tick, freq_out);
    if (active_snare) {
      leds.setPixel(ledIndex, 255, 255, 255);
    } else {
      leds.setPixel(ledIndex, color.r, color.g, color.b);
    }
  }
  leds.show();
  tick++;

  // slow indicator loop
  if (tick % 5 == 0) {
    indicator = !indicator;
    digitalWrite(LED_BUILTIN, indicator);
    spectrumPlot();
  }
}
#else

int period = 10000;
char serialized_freq[14];

void setup() {
  delay(100);
  Serial.begin(9600);
  setupSpectrum();
  delay(100);
}

void loop() {
  readFrequenciesTimed();
  if (tick % period == 0) {
    memcpy(freq_out, serialized_freq, sizeof(freq_out));
    Serial.write(serialized_freq, sizeof(serialized_freq));
    Serial.write("\n");
  }
  tick++;
}

#endif