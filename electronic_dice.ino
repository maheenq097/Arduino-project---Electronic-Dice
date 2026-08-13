/*
  Electronic Dice
  Single 7-segment display (common cathode) + push button
  Press button -> rolls a random number 1-6 and shows it
*/

// Segment pins: a, b, c, d, e, f, g
const int segPins[7] = {2, 3, 4, 5, 6, 7, 8};
const int buttonPin = 9;

// Segment patterns for digits 1-6 (1 = ON, 0 = OFF)
// order: a, b, c, d, e, f, g
const byte digitPatterns[7][7] = {
  {0,0,0,0,0,0,0}, // 0 - unused, blank
  {0,1,1,0,0,0,0}, // 1
  {1,1,0,1,1,0,1}, // 2
  {1,1,1,1,0,0,1}, // 3
  {0,1,1,0,0,1,1}, // 4
  {1,0,1,1,0,1,1}, // 5
  {1,0,1,1,1,1,1}  // 6
};

int lastButtonState = HIGH;

void setup() {
  for (int i = 0; i < 7; i++) {
    pinMode(segPins[i], OUTPUT);
  }
  pinMode(buttonPin, INPUT_PULLUP); // button reads LOW when pressed
  randomSeed(analogRead(A0));       // seed randomness from a floating pin
  displayDigit(1);                  // show a starting face
}

void loop() {
  int buttonState = digitalRead(buttonPin);

  // detect press: HIGH -> LOW transition
  if (buttonState == LOW && lastButtonState == HIGH) {
    delay(30); // simple debounce
    if (digitalRead(buttonPin) == LOW) {
      rollDice();
    }
  }
  lastButtonState = buttonState;
}

void rollDice() {
  // quick flicker effect for a nicer "rolling" feel
  for (int i = 0; i < 8; i++) {
    int fakeRoll = random(1, 7);
    displayDigit(fakeRoll);
    delay(50);
  }
  int result = random(1, 7);
  displayDigit(result);
}

void displayDigit(int num) {
  for (int i = 0; i < 7; i++) {
    digitalWrite(segPins[i], digitPatterns[num][i]);
  }
}
