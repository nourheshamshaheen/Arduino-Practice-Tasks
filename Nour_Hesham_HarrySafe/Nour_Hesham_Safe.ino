const int greenLED = 5;

const int interrupt1A = 2;
const int interrupt1B = 3;
const int interrupt2A = 21;
const int interrupt2B = 20;
const int interrupt3A = 19;
const int interrupt3B = 18;

//prototype of interrupt functions
void ISR_1A();
void ISR_1B();
void ISR_2A();
void ISR_2B();
void ISR_3A();
void ISR_3B();

//number of pulses produced by the encoder within a revolution
const int PPR = 512;

//4 for 4x encoding - 2 interrupts->CHANGE
const int decodeNumber = 4;

volatile long int counter1 = 0L;
volatile long int counter2 = 0L;
volatile long int counter3 = 0L;
int angle_1 = 0;
int angle_2 = 0;
int angle_3 = 0;

void setup() {
  pinMode(greenLED, OUTPUT);
  pinMode(interrupt1A, INPUT_PULLUP);
  pinMode(interrupt1B, INPUT_PULLUP);
  pinMode(interrupt2A, INPUT_PULLUP);
  pinMode(interrupt2B, INPUT_PULLUP);
  pinMode(interrupt3A, INPUT_PULLUP);
  pinMode(interrupt3B, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interrupt1A), ISR_1A, CHANGE);
  attachInterrupt(digitalPinToInterrupt(interrupt1B), ISR_1B, CHANGE);
  attachInterrupt(digitalPinToInterrupt(interrupt2A), ISR_2A, CHANGE);
  attachInterrupt(digitalPinToInterrupt(interrupt2B), ISR_2B, CHANGE);
  attachInterrupt(digitalPinToInterrupt(interrupt3A), ISR_3A, CHANGE);
  attachInterrupt(digitalPinToInterrupt(interrupt3B), ISR_3B, CHANGE);
}
void loop() {
  angle_1 = ((counter1 * 360) / (PPR * decodeNumber)) % 360;
  angle_2 = ((counter2 * 360) / (PPR * decodeNumber)) % 360;
  angle_3 = ((counter3 * 360) / (PPR * decodeNumber)) % 360;
  if(angle_1 == 37 && angle_2 == 10 && angle_3 == 54)
    digitalWrite(greenLED, HIGH);
  else
    digitalWrite(greenLED, LOW);
}

void ISR_1A()
{
  if(digitalRead(interrupt1A) != digitalRead(interrupt1B))
    counter1++;
  else
    counter1--;
}
void ISR_1B()
{
  if(digitalRead(interrupt1A) == digitalRead(interrupt1B))
    counter1++;
  else
    counter1--;
}

void ISR_2A()
{
  if(digitalRead(interrupt2A) != digitalRead(interrupt2B))
    counter2++;
  else
    counter2--;
}
void ISR_2B()
{
  if(digitalRead(interrupt2A) == digitalRead(interrupt2B))
    counter2++;
  else
    counter2--;
}

void ISR_3A()
{
  if(digitalRead(interrupt3A) != digitalRead(interrupt3B))
    counter3++;
  else
    counter3--;
}
void ISR_3B()
{
  if(digitalRead(interrupt3A) == digitalRead(interrupt3B))
    counter3++;
  else
    counter3--;
}
