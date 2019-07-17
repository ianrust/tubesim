#include <OctoWS2811.h>
#include <audio.h>
#include <patterns.h>

const int ledsPerStrip = 450;

int tick = 0;
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
}

void loop() {
  digitalWrite(LED_BUILTIN, indicator);
  for (ledIndex = 0; ledIndex < leds.numPixels() ; ledIndex++) {
    color = getGoalsColorPortable(ledIndex, tick);
    readFrequenciedTimed();
    leds.setPixel(ledIndex, 255, 0.0, 0.0);
  }
  leds.show();
  tick++;
  indicator = !indicator;
  Serial.println(tick);
  delay(500);
  // audio::spectrumPlot();
}