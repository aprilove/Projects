const int Lpin = 13;
const int Mpin = 12;
const int Hpin = 11;
const int LDR = A0;
const int Pump = 3;

int LpinState = 0;
int MpinState = 0;
int HpinState = 0;
int LDRValue = 0;

void setup()
{
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(Pump, OUTPUT);
    pinMode(Lpin, INPUT);
    pinMode(Mpin, INPUT);
    pinMode(Hpin, INPUT);
}

void loop()
{
    LpinState = digitalRead(Lpin);
    MpinState = digitalRead(Mpin);
    HpinState = digitalRead(Hpin);
    LDRValue = analogRead(LDR);

    //if bright
    if (LDRValue > 800)
    {
        //testing
        if (LpinState == HIGH || MpinState == HIGH)
            digitalWrite(Pump, HIGH);

        //internal LED button
        if (HpinState == HIGH)
            digitalWrite(LED_BUILTIN, LOW);
        else
            digitalWrite(LED_BUILTIN, HIGH);

        //delay 7 hours 
    delay(25200000UL);
    }
    delay(25200000UL);
    //note that 2 cycles will guarantee a trigger assuming that theres day time for ~12 hours in a day.
}