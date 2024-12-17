// Pin Definitions
const int button1Pin = 2;
const int button2Pin = 3;
const int potPin = A0;

const int successLEDPin = 4;
const int failureLEDPin = 5;


// Variables to track inputs
int currentStep = 0;
bool passwordCorrect = true;

void setup() {
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);
  pinMode(successLEDPin, OUTPUT);
  pinMode(failureLEDPin, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  // Step 1: Press Button 1
  if (currentStep == 0) {
    if (digitalRead(button1Pin) == HIGH) {
      Serial.println("Step 1: Button 1 Pressed");
      currentStep++;
      delay(300); // Debounce
    } else if (digitalRead(button2Pin) == HIGH) {  // Wrong input detected
      passwordCorrect = false;
      currentStep = 3; // Jump to password check
    }
  }

  // Step 2: Potentiometer in Middle Range
  else if (currentStep == 1) {
    int potValue = analogRead(potPin);
    if (potValue > 500 && potValue < 600) {  // Adjust range as needed
      Serial.println("Step 2: Potentiometer in Middle Range");
      currentStep++;
      delay(300); // Debounce
    } else if (digitalRead(button1Pin) == HIGH || digitalRead(button2Pin) == HIGH) {
      passwordCorrect = false;
      currentStep = 3;
    }
  }

  // Step 3: Press Button 2
  else if (currentStep == 2) {
    if (digitalRead(button2Pin) == HIGH) {
      Serial.println("Step 3: Button 2 Pressed");
      currentStep++;
      delay(300); // Debounce
    } else if (digitalRead(button1Pin) == HIGH) {  // Wrong input detected
      passwordCorrect = false;
      currentStep = 3;
    }
  }

  // Check Password
  if (currentStep == 3) {
    if (passwordCorrect) {
      digitalWrite(successLEDPin, HIGH);
      digitalWrite(failureLEDPin, LOW);
      Serial.println("Password Correct! Success!");
    } else {
      digitalWrite(successLEDPin, LOW);
      digitalWrite(failureLEDPin, HIGH);
      Serial.println("Password Incorrect! Failure!");
    }

    // Reset for next attempt
    delay(3000);
    digitalWrite(successLEDPin, LOW);
    digitalWrite(failureLEDPin, LOW);
    currentStep = 0;
    passwordCorrect = true; // Reset for next attempt
  }
}
