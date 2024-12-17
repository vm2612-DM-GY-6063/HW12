
const int LED_PINS[] = {2, 3, 4, 5, 6, 7}; 
const int NUM_LEDS = 6; 

void setup() {
  
  for (int i = 0; i < NUM_LEDS; i++) {
    pinMode(LED_PINS[i], OUTPUT);
  }
}

void loop() {

  int seconds = (millis() / 1000) % 60;

  for (int i = 0; i < NUM_LEDS; i++) {
    int bitValue = (seconds >> i) & 1; 
    digitalWrite(LED_PINS[i], bitValue); 
  }
}
