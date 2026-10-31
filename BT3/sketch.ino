#include <Arduino.h>

#define ADC_PIN 34
#define LED_PIN 18
#define N 8

int buf[N]; 
int idx = 0;

int movingAverageFilter(int rawValue) {
    buf[idx] = rawValue;
    idx = (idx + 1) % N;
    
    long sum = 0;
    for (int i = 0; i < N; i++) {
        sum += buf[i];
    }
    return sum / N;
}

void setup() {
    Serial.begin(115200);
    ledcAttach(LED_PIN, 5000, 8);
}

void loop() {
    int rawValue = analogRead(ADC_PIN);           
    int filteredValue = movingAverageFilter(rawValue); 

    ledcWrite(LED_PIN, map(filteredValue, 0, 4095, 0, 255));

    Serial.print(">tho:"); 
    Serial.println(rawValue);
    Serial.print(">loc:"); 
    Serial.println(filteredValue);

    delay(20);
}