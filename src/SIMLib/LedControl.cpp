#include "LedControl.h"
#include <FastLED.h>

LedControl::LedControl() {
    // Initialize on instancing. Probably never used, but still.
    init();
}

#define NUM_LEDS 28

CRGB leds_R[NUM_LEDS];
CRGB leds_L[NUM_LEDS];

int xL = 0;
int xR = 0;

void LedControl::init() {
    const byte offset = NUM_LEDS >> 2;
    
    FastLED.addLeds<WS2812B, PIN_LEDR, GRB>(leds_R, NUM_LEDS);
    FastLED.addLeds<WS2812B, PIN_LEDL, GRB>(leds_L, NUM_LEDS);
    for (byte r = 0; r < NUM_LEDS * 2; r++) {
        byte g = (r + offset) % NUM_LEDS;
        byte b = (g + offset) % NUM_LEDS;
        byte w = (b + offset) % NUM_LEDS;
        
        both(r % 28, CRGB::Red);
        both(g, CRGB::Green);
        both(b, CRGB::Blue);
        both(w, CRGB::White);
        FastLED.show();
        delay(25);
        both(r % 28, CRGB::Black);
        both(g, CRGB::Black);
        both(b, CRGB::Black);
        both(w, CRGB::Black);
    }
    FastLED.show();
}

void LedControl::both(int pos, CRGB color) {
    leds_R[pos] = color;
    leds_L[pos] = color;
}

void LedControl::flood(CRGB color) {
    for (int i = 0; i < NUM_LEDS; i++) {
        both(i, color);
    }
    FastLED.show();
}

void LedControl::error() {
    for (int i = 0; i < NUM_LEDS; i++) {
        if (i & 1) {
            both(i, CRGB::OrangeRed);
        } else {
            both(i, CRGB::DarkRed);
        }
    }
    FastLED.show();
}

void LedControl::showSpeedLeft(int speed) {
    for (int i = 0; i < 28; i++) {
        leds_L[i] = CRGB::Black;
    }
    for (int i = 12; i < 16; i++) {
        leds_L[i] = CRGB::Green;
    }
    int ledsOn = max(0, (speed >> 4) - 4);
    if (speed > 0) {
        for (int i = 16; i < 16 + ledsOn; i++) {
            leds_L[i] = CRGB::Green;
        }
    } else {
        for (int i = 11; i >= 12 - ledsOn; i--) {
            leds_L[i] = CRGB::Green;
        }
    }
    FastLED.show();
}

void LedControl::showSpeedRight(int speed) {
    for (int i = 0; i < 28; i++) {
        leds_R[i] = CRGB::Black;
    }
    for (int i = 12; i < 16; i++) {
        leds_R[i] = CRGB::Green;
    }
    int ledsOn = max(0, abs(speed) / 16 - 4);
    if (speed > 0) {
        for (int i = 16; i < 16 + ledsOn; i++) {
            leds_R[i] = CRGB::Green;
        }
    } else {
        for (int i = 11; i >= 12 - ledsOn; i--) {
            leds_R[i] = CRGB::Green;
        }
    }
    FastLED.show();
}
void LedControl::clear() {
    flood(CRGB::Black);
}

void LedControl::pause() {
    clear();
    for (int i = 0; i < 28; i += 6) {
        for (int j = 0; j < 4; j++) {
            both(i + j, CRGB::Blue);
        }
        FastLED.show();
        delay(1000);
    }
    clear();
}

void LedControl::stop() {
    flood(CRGB::Red);
}