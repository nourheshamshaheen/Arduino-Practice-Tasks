#include <Timer.h>

const int redLED = 4;
const int greenLED = 5;
const int whiteLED = 6;
const int buttonPin = 7;

//variables
int buttonState = 0;
int flag = 0;
unsigned long previousMillis = 0;
unsigned long currentMillis = 0;

Timer potionsTimer;

void setup() {
  Serial.begin(9600);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  while(flag == 0)
  {
    buttonState = digitalRead(buttonPin);
    if(buttonState == LOW)
      flag = 1;
  }
  potionsTimer.pulse(redLED, 15 * 60 * 1000UL, LOW); 
  potionsTimer.every(2*60*1000UL,greenFunc);
  potionsTimer.after(5*60*1000UL,whiteFunc);
  potionsTimer.after(8*60*1000UL,whiteFunc);
}
void loop() { 
  potionsTimer.update();
}


void greenFunc()
{
    potionsTimer.oscillate(whiteLED, 100, LOW,50); // repeatcounts is time required/time of one toggle  
}
void whiteFunc()
{
    potionsTimer.oscillate(whiteLED,100, LOW, 100); // repeatcounts is time required / time of one toggle 
}

//another method for greenFunc and whiteFunc using delay 
//(not sure of this one, since delay will probably mess up the multitasking ??

/*
void greenFunc()
{
  previousMillis = millis();
  currentMillis = millis();
  while(currentMillis - previousMillis < 5000)
  {
    digitalWrite(greenLED, HIGH);
    delay(100);
    digitalWrite(greenLED, LOW);    
  }  
}
void whiteFunc()
{
  previousMillis = millis();
  currentMillis = millis();
  while(currentMillis - previousMillis < 10000)
  {
    digitalWrite(whiteLED, HIGH);
    delay(100);
    digitalWrite(whiteLED, LOW);    
  } 
}
*/
