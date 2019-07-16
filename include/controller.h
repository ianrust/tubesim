#include <Arduino.h>
#include <patterns.h>
#include <OctoWS2811.h>

#ifdef GOALS
const int ledsPerStrip = 450;
#define GET_COLOR getGoalsColorPortable
#endif
#ifdef LINES
const int ledsPerStrip = 600;
#define GET_COLOR getLinesColorPortable
#endif

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
    GET_COLOR(i, tick);
    Color8bit color = GET_COLOR(i, tick);
    leds.setPixel(i, color.r, color.g, color.b);
    tick++;
  }
  leds.show();
}