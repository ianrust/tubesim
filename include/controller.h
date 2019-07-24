
#include "audio.h"

#ifdef GOALS
#endif

#ifndef RECORD
#include "patterns.h"
#include <OctoWS2811.h>

#define PIN_LEFT 33
#define PIN_RIGHT 34

int ledIndex = 0;
Color8bit color;

const int ledsPerStrip = 700;
const int numActiveAddresses = ledsPerStrip * 6;

DMAMEM int displayMemory[ledsPerStrip*6];
int drawingMemory[ledsPerStrip*6];

const int config = WS2811_GRB | WS2811_800kHz;

OctoWS2811 leds(ledsPerStrip, displayMemory, drawingMemory, config);

bool indicator = false;

ControllerState state;

void setup() {
  leds.begin();

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(PIN_LEFT, INPUT_PULLUP);
  pinMode(PIN_RIGHT, INPUT_PULLUP);

  setupSpectrum();
  delay(100);
}

void loop() {
  state.update(!digitalRead(PIN_LEFT), !digitalRead(PIN_RIGHT), freq_out);
  for (ledIndex = 0; ledIndex < numActiveAddresses ; ledIndex++) {
    readFrequenciesTimed();
    if (mapping_config.isGoal(ledIndex)) {
      color = getGoalsColorPortable(ledIndex, state, freq_out);
      leds.setPixel(ledIndex, color.r, color.b, color.g);
    } else if (mapping_config.isGoal(ledIndex)) {
      color = getGoalsColorPortable(ledIndex, state, freq_out);
      leds.setPixel(ledIndex, color.r, color.b, color.g);
    }
  }
  leds.show();

  // slow indicator loop
  if (state.tick % 10 == 0) {
    indicator = !indicator;
    digitalWrite(LED_BUILTIN, indicator);
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