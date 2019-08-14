#pragma once

#include "audio.h"

#ifndef RECORD
#include "patterns.h"
#include "gamma.h"
#include "day_time.h"
#include <OctoWS2811.h>

#define PIN_LEFT 33
#define PIN_RIGHT 34

size_t ledIndex = 0;
Color8bit color;

const int ledsPerStrip = 700;
const int numActiveAddresses = ledsPerStrip * 7;

DMAMEM int displayMemory[ledsPerStrip*6];
int drawingMemory[ledsPerStrip*6];

const int config = WS2811_GRB | WS2811_800kHz;

OctoWS2811 leds(ledsPerStrip, displayMemory, drawingMemory, config);

bool indicator = false;

ControllerState state;
Timer timer;

#ifdef FPS
unsigned long last_frame_micros = 0;
#endif

void setup() {
  timer.init();
  initializeTrigTables();

  leds.begin();

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(PIN_LEFT, INPUT_PULLUP);
  pinMode(PIN_RIGHT, INPUT_PULLUP);
#ifdef FPS
  Serial.begin(9600);
#endif
  setupSpectrum();
  delay(100);
}

void loop() {
  state.update(!digitalRead(PIN_LEFT), !digitalRead(PIN_RIGHT), freq_out, timer.now());
  for (ledIndex = 0; ledIndex < numActiveAddresses ; ledIndex++) {
    readFrequenciesTimed();
    if (mapping_config.isGoal(ledIndex)) {
      color = getGoalsColorPortable(ledIndex, state, freq_out);
      leds.setPixel(ledIndex, gamma8[color.r], gamma8[color.b], gamma8[color.g]);
    } else if (mapping_config.isLine(ledIndex)) {
      color = getLinesColorPortable(ledIndex, state, freq_out);
      leds.setPixel(ledIndex, gamma8[color.r], gamma8[color.b], gamma8[color.g]);
    } else {
      // skip inactive addresses
      ledIndex += mapping_config.leds_per_channel-1;
    }
  }
  leds.show();

#ifdef FPS
  Serial.println("Frame rate:");
  float fps = micros() - last_frame_micros;
  fps = 1000000.0 / fps;
  Serial.println(fps);
  last_frame_micros = micros();
  Time now = timer.now();
  Serial.print("Hour: ");
  Serial.println(now.hours);
  Serial.print("Minutes: ");
  Serial.println(now.minutes);
  Serial.print("Seconds: ");
  Serial.println(now.seconds);
#endif

  // slow indicator loop
  if (state.tick % 10 == 0) {
    digitalWrite(LED_BUILTIN, timer.seconds() % 2);
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