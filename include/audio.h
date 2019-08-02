#pragma once

#include "freq_buffer.h"

// 63Hz, 160Hz, 400Hz, 1kHz, 2.5kHz, 6.25kHz, 16kHz
float Bands[7] = {63.0, 160.0, 400.0, 1000.0, 2500.0, 6250.0, 16000.0};

//Declare Spectrum Shield pin connections
#define STROBE 29
#define RESET 30
#define DC_One A12
#define DC_Two A13

int16_t raw_left[7];
int16_t raw_right[7];
int16_t tare_left[7];
int16_t tare_right[7];
float raw_mixed[7];

float lpf_alpha[7] = {0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05};
float lpf_output[7] = {0, 0, 0, 0, 0, 0, 0};

int16_t freq_out[7];

uint8_t freq_amp;

// filtered variables
uint32_t last_spectrum_read_micros = 0;
uint32_t spectrum_read_period_micros = 10000;
uint32_t current_micros;


void spectrumPlot() {
    Serial.println("\nRawLeft");
    for (freq_amp = 0; freq_amp<7; freq_amp++)
    {
        Serial.print(raw_left[freq_amp]);
        Serial.print(" ");
    }
    Serial.println("\nRaw Right");
    for (freq_amp = 0; freq_amp<7; freq_amp++)
    {
        Serial.print(raw_right[freq_amp]);
        Serial.print(" ");
    }
    Serial.println("\nRaw mixed");
    for (freq_amp = 0; freq_amp<7; freq_amp++)
    {
        Serial.print(raw_mixed[freq_amp]);
        Serial.print(" ");
    }
    Serial.println("\nLPF");
    for (freq_amp = 0; freq_amp<7; freq_amp++)
    {
        Serial.print(lpf_output[freq_amp]);
        Serial.print(" ");
    }
    Serial.println("");
    for (int level_bin = 0; level_bin <= 1000; level_bin+=100) {
        for (freq_amp = 0; freq_amp<7; freq_amp++)
        {
        if (lpf_output[freq_amp] > level_bin) {
            Serial.print("@");
        } else{
            Serial.print(" ");
        }
        }
        Serial.println("");
    }
}

/*******************Pull frquencies from Spectrum Shield********************/
void readFrequencies() {
    //Read frequencies for each band
    for (freq_amp = 0; freq_amp<7; freq_amp++)
    {
        digitalWrite(STROBE, LOW);
        delayMicroseconds(20);
        raw_left[freq_amp] = analogRead(DC_One) - tare_left[freq_amp];
        raw_right[freq_amp] = analogRead(DC_Two) - tare_right[freq_amp];
        raw_mixed[freq_amp] = raw_right[freq_amp]/2.0 + raw_left[freq_amp]/2.0;
        digitalWrite(STROBE, HIGH);
    }
}

void filterFrequencies() {
    for (freq_amp = 0; freq_amp<7; freq_amp++) {
        lpf_output[freq_amp] = 
            (1.0-lpf_alpha[freq_amp]) * lpf_output[freq_amp] +
            lpf_alpha[freq_amp] * raw_mixed[freq_amp];
    }
}

void readFrequenciesTimed() {
    current_micros = micros();
    if (current_micros - last_spectrum_read_micros > spectrum_read_period_micros) {
        last_spectrum_read_micros += spectrum_read_period_micros;
        readFrequencies();
        filterFrequencies();
        freq_buffer.accumulate(freq_out);

        for (freq_amp = 0; freq_amp<7; freq_amp++) {
            freq_out[freq_amp] = lpf_output[freq_amp];
        }
    }
}

void zeroSpectrum() {
    readFrequencies();
    for (freq_amp = 0; freq_amp<7; freq_amp++) {
        tare_left[freq_amp] = raw_right[freq_amp];
        tare_right[freq_amp] = raw_right[freq_amp];
    }
}

void setupSpectrum() {
    // Set spectrum Shield pin configurations
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
    delay(100);
    
    zeroSpectrum();

    last_spectrum_read_micros = micros();
}