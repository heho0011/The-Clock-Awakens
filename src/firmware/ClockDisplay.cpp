#include "ClockDisplay.h"
#include "Settings.h"

#define NEOPIXELS_PIN       2
#define NEOPIXELS_NUM       60

#define RED                 0xff0000
#define GREEN               0x00ff00
#define BLUE                0x0000ff

#define DEBUG               1

void onBrightnessUpdate(Key key, int value) {

    Serial.println("Brightness updated!");
    ClockDisplay.setBrightness(value);
}

ClockDisplayClass::ClockDisplayClass(int numPixels, int pin, int settings)
    : pixels(numPixels, pin, settings) { }

void ClockDisplayClass::begin() {

    pixels.begin();

    setBrightness(Settings.get(SET_BRIGHTNESS));
    Settings.registerObserver(SET_BRIGHTNESS, &onBrightnessUpdate);
}

void ClockDisplayClass::update() {

    displayTime(now());
}

void ClockDisplayClass::displayTime(time_t t) {

    static int lastSecond = 0;

    int currentSecond = second(t);
    int currentMinute = minute(t);
    int currentHour = hour(t);

    // Only update the strip when the time changes
    if (lastSecond != currentSecond) {

#ifdef DEBUG
        String message = String(currentHour);
        message += ":";
        message += String(currentMinute);
        message += ":";
        message += String(currentSecond);
        Serial.println(message);
#endif

        int hourPixel = (currentHour % 12) * 5 + currentMinute / 12;
        
        for (int i = 0; i < NEOPIXELS_NUM; i++) {

            uint32_t color = 0x000000;

            if (i == currentSecond) {
                color |= RED;
            }

            if (i == currentMinute) {
                color |= GREEN;
            }

            if (i == hourPixel) {
                color |= BLUE;
            }

            pixels.setPixelColor(i, color);
        }

        pixels.show();

        lastSecond = currentSecond;
    }
}

void ClockDisplayClass::setBrightness(int brightness) {

    // Make sure input is valid
    if (brightness < 0 || brightness > 100) {
        return;
    }

    // Scale the brightness 
    uint8_t scaledBrightness = brightness * 255 / 100;
    pixels.setBrightness(scaledBrightness);
}

ClockDisplayClass ClockDisplay(NEOPIXELS_NUM, NEOPIXELS_PIN, NEO_GRB + NEO_KHZ800);
