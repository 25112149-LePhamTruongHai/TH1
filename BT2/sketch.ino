#include <Arduino.h>

#define BUTTON_PIN 4
#define LED_PIN 2
#define DEBOUNCE_MS 50

volatile uint32_t debouncedCount = 0;
volatile uint32_t rawEdgeCount = 0;
volatile unsigned long lastInterruptTime = 0;

void IRAM_ATTR handleInterrupt() {
    rawEdgeCount++;
    unsigned long now = millis();
    
    if (now - lastInterruptTime >= DEBOUNCE_MS) {
        debouncedCount++;
        lastInterruptTime = now;
        digitalWrite(LED_PIN, !digitalRead(LED_PIN)); 
    }
}

void setup() {
    Serial.begin(115200);
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    pinMode(LED_PIN, OUTPUT);
    
    attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), handleInterrupt, FALLING);
    Serial.println("Bat dau Bai 2: Chong doi (Debounce)");
}

void loop() {
    Serial.print("rawEdgeCount (Tho): ");
    Serial.print(rawEdgeCount);
    Serial.print(" | debouncedCount (Da loc): ");
    Serial.println(debouncedCount);
    delay(500);
}