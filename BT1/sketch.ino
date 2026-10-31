#include <Arduino.h>
#define BUTTON_PIN 4
#define LED_PIN 2
volatile bool buttonPressed = false;

void IRAM_ATTR handleInterrupt() {
    buttonPressed = true;
}

void setup() {
    Serial.begin(115200);
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    ledcAttach(LED_PIN, 5000, 8);
    attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), 
                     handleInterrupt, FALLING);
}

void loop() {
    static int brightness = 0;
    static int step = 1;

    if (buttonPressed) {
        buttonPressed = false;
        Serial.println("Nut duoc nhan ");
        
        ledcWrite(LED_PIN, 0);   delay(80);
        ledcWrite(LED_PIN, 255); delay(80);
    }

    brightness += step;
    if (brightness <= 0 || brightness >= 255) {
        step = -step;
    }
    ledcWrite(LED_PIN, brightness);
    delay(10);
}