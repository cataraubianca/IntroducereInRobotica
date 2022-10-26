//pins of RGB led 
const int ledRedPin = 9;
const int ledGreenPin = 10;
const int ledBluePin = 11;

const int potRedPin = A0; 
const int potBluePin = A1; 
const int potGreenPin = A2; 

//maximum brightness and analog value
const int highBrightnessValue = 255;
const int highAnalogValue = 1023;

int signalRedValue;
int signalBlueValue;
int signalGreenValue;

int mappedLedRedValue;
int mappedLedBlueValue;
int mappedLedGreenValue;

void setup(){
  pinMode(potRedPin, INPUT);
  pinMode(potBluePin, INPUT);
  pinMode(potGreenPin, INPUT);

  pinMode(ledRedPin, OUTPUT);
  pinMode(ledBluePin, OUTPUT);
  pinMode(ledGreenPin, OUTPUT);
}

void loop(){

  //red potentiometer value
  signalRedValue = analogRead(potRedPin); 
  //map the red led value
  mappedLedRedValue = map(signalRedValue, 0, highAnalogValue, 0, highBrightnessValue);

  //blue potentiometer value
  signalBlueValue = analogRead(potBluePin);  
  //map the blue led value
  mappedLedBlueValue = map(signalBlueValue, 0, highAnalogValue, 0, highBrightnessValue);  

  //green potentiometer value
  signalGreenValue = analogRead(potGreenPin); 
  //map the green led value
  mappedLedGreenValue = map(signalGreenValue,0 , highAnalogValue, 0, highBrightnessValue);

 
  //set the colour based on mapped value
  analogWrite(ledRedPin, mappedLedRedValue);
  analogWrite(ledBluePin, mappedLedBlueValue);
  analogWrite(ledGreenPin, mappedLedGreenValue);
}
