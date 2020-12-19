const int buttonPin = 2; // button pin
const int ledPin = 3; // button pin
int buttonState; // the current reading from the input pin
int lastButtonState = LOW; // the previous reading from the input pin
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers
int light = 0; // light value

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // baud rate
  pinMode(buttonPin, INPUT_PULLUP); // set up button pin
  pinMode(ledPin, OUTPUT); // led pin set up
}

void loop() {
  // put your main code here, to run repeatedly:

  light = analogRead(A0); // read light

  if (light < 230) { // If it is dim...
    digitalWrite(ledPin, HIGH); //turn led on
  }
  digitalWrite(ledPin, LOW);
  // read the button
  int reading = digitalRead(buttonPin);

  // If switch changed
  if (reading != lastButtonState) {
    // reset  debounce timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // debounc time delay to find actual state

    // if state changed
    if (reading != buttonState) {
      buttonState = reading;

      // toggle only if high
      if (buttonState == HIGH) {
        // put data on processing
        Serial.println(1);
      }
    }
  }
  // set as last read
  lastButtonState = reading;
}
