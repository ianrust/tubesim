#include <Arduino.h>
#include <goal_pattern.h>
#include <OctoWS2811.h>

const int ledsPerStrip = 450;

DMAMEM int displayMemory[ledsPerStrip*8];
int drawingMemory[ledsPerStrip*8];

const int config = WS2811_GRB | WS2811_800kHz;

OctoWS2811 leds(ledsPerStrip, displayMemory, drawingMemory, config);

void setup() {
  leds.begin();
}

void loop() {
  int tick = 0;
  for (int i = 0; i < leds.numPixels(); i++) {
    getGoalColorPortable(i, tick);
    Color8bit color = getGoalColorPortable(i, tick);
    leds.setPixel(i, color.r, color.g, color.b);
    tick++;
  }
  leds.show();
}