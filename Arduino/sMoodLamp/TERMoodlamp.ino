//define pins
int potPin = 5;
int segmentPins[] = {3,7,8,12,13};
int piezoPin = 5;
int red_light_pin= 11;
int green_light_pin = 10;
int blue_light_pin = 9;

int mood = 0;//states or "mood"
int val = 0;//potentiometer value
int red_value = 255;//red value
int blue_value = 255;// blue value
int green_value = 255;//green value
int mTime = 0;//variance in speaker output
int mFreq = 0;//frequencey of speaker
int buttonState2;// the current reading from the input pin
int lastButtonState2 = LOW;// the previous reading from the input pin
unsigned long lastDebounceTime2 = 0;// the last time the output pin was toggled
unsigned long debounceDelay = 50;// the debounce time; increase if the output flickers
int buttonState4;// the current reading from the input pin
int lastButtonState4 = LOW;// the previous reading from the input pin
unsigned long lastDebounceTime4 = 0;// the last time the output pin was toggled
int rVal = 254;//final led val
int gVal = 0;//final led val
int bVal = 126;//final led val
int rDir = -1;//fade direction
int gDir = 1;//fade direction
int bDir = -1;//fade direction
int ic=0;//increment for sine sound


void setup() {
  Serial.begin(9600);//baud rate
  //define buttons 
  pinMode(2, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  //define 7segment
  for (int i=0; i < 5; i++)
    pinMode(segmentPins[i],OUTPUT);
  //define rgb pins
  pinMode(red_light_pin, OUTPUT);
  pinMode(green_light_pin, OUTPUT);
  pinMode(blue_light_pin, OUTPUT);
  //start at mood 0 so turn on led for mood 0
  digitalWrite(segmentPins[0], HIGH);
}


void loop() {
  val = analogRead(potPin)/4;//read state of potentiometer (since it ranges from 0 - ~1000 divide by 4 to fit in led range (0 - ~250))
  int reading2 = digitalRead(2);//read state of switch
  int reading4 = digitalRead(4);//read state of switch
  
  if (reading2 != lastButtonState2) {//if switch changed
    lastDebounceTime2 = millis(); //reset timer
  }
  if ((millis() - lastDebounceTime2) > debounceDelay) { //no debounce stuff happening , 1 press
    if (reading2 != buttonState2) { //change in button state
      buttonState2 = reading2;
      if (buttonState2 == LOW) { 
        //changing mood so turn off previous pins 
        for (int i=0; i < 5; i++)
          digitalWrite(segmentPins[i], LOW);
        //adjust mood
        mood++;
        //make sure the mood stays in range
        if (mood > 4){
          mood = 4;
        }
        //show mood on 7segment
        digitalWrite(segmentPins[mood], HIGH);
      }
    }
  }

  if (reading4 != lastButtonState4) { 
    lastDebounceTime4 = millis();
  }
  if ((millis() - lastDebounceTime4) > debounceDelay) { 
    if (reading4 != buttonState4) {  
      buttonState4 = reading4;
      if (buttonState4 == LOW) { 
        for (int i=0; i < 5; i++)
        //changing mood so turn off previous pins 
          digitalWrite(segmentPins[i], LOW);
        //adjust mood
        mood--;
        ////make sure the mood stays in range
        if (mood < 0){
          mood = 0;
        }
        //show mood on 7segment
        digitalWrite(segmentPins[mood], HIGH);
      }
    }
  }
  //change button states for next loop
  lastButtonState4 = reading4;  
  lastButtonState2 = reading2;

  switch(mood){
    case 0: //change variance in speaker quality (sort of like static/white noise) with Potentiometer 
      mTime = val*2;
      break;
    case 1: //change frequency of speaker with Potentiometer 
      mFreq = val*40+mTime*sin(radians(ic));
      break;
    case 2: //change red values with potentiometer 
      red_value = 255 - val;
      break;
    case 3: //change green values with potentiometer 
      green_value = 255 - val;
      break;
    case 4: //change blue values with potentiometer 
      blue_value = 255 - val;
      break;
  }
  //rgb led
  RGB_color(rVal,gVal,bVal);
  //piezo speaker output
  tone(piezoPin, mFreq, 100);
  //fade up or down
  rVal = rVal + rDir;
  gVal = gVal + gDir;
  bVal = bVal + bDir;

  //change direction of fade if oor
  if (rVal >= red_value) {
    rDir = -1;
  }
  if (gVal >= green_value) {
    gDir = -1;
  }
  if (bVal >= blue_value) {
    bDir = -1;
  }
  if (rVal <= 0) {
    rDir = 1;
  }
  if (gVal <= 0) {
    gDir = 1;
  }
  if (bVal <= 0) {
    bDir = 1;
  }
  
  //increase increments
  ic++;
  //not too fast
  delay(10);
}

//rgb color 
void RGB_color(int red_light_value, int green_light_value, int blue_light_value)
 {
  //each rgb pin value
  analogWrite(red_light_pin, red_light_value);
  analogWrite(green_light_pin, green_light_value);
  analogWrite(blue_light_pin, blue_light_value);
}
