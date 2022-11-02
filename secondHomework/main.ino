const int carRedPin = 10;
const int carYellowPin = 9; 
const int carGreenPin = 8;
const int pedestrianRedPin = 4;
const int pedestrianGreenPin = 3;
const int buttonPin = 2;
const int buzzerPin = 5;

byte carRed = LOW;
byte carYellow = LOW;
byte carGreen = HIGH;

byte pedestrianRed = HIGH;
byte pedestrianGreen = LOW;

byte buttonState = HIGH;

bool start = false;     // when the light game start this variable will be true
int startProgram;              // time from the point when the button was pressed
int previousState;

void setup() {
  pinMode(carRedPin, OUTPUT);
  pinMode(carYellowPin, OUTPUT);
  pinMode(carGreenPin, OUTPUT);
  
  pinMode(pedestrianRedPin, OUTPUT);
  pinMode(pedestrianGreenPin, OUTPUT);
  
  pinMode(buttonPin, INPUT_PULLUP);
  
  Serial.begin(9600);
}

void firstState() {
  //green for cars
  carRed = LOW;
  carYellow = LOW;
  carGreen = HIGH;
  digitalWrite(carRedPin,carRed);
  digitalWrite(carYellowPin,carYellow);
  digitalWrite(carGreenPin,carGreen);

  //red for pedestrians
  pedestrianRed = HIGH;
  pedestrianGreen = LOW; 
  digitalWrite(pedestrianRedPin,pedestrianRed);
  digitalWrite(pedestrianGreenPin,pedestrianGreen);
}

void secondState() { 
  //yellow for cars
  carYellow = HIGH;
  carGreen = LOW;
  digitalWrite(carYellowPin,carYellow);
  digitalWrite(carGreenPin,carGreen);
}

void thirdState(int current) {
  //red for cars
  carRed = HIGH;
  carYellow = LOW;
  digitalWrite(carRedPin,carRed);
  digitalWrite(carYellowPin,carYellow);
  
  //green for pedestrians
  pedestrianRed = LOW;
  pedestrianGreen = HIGH;
  digitalWrite(pedestrianRedPin,pedestrianRed);
  digitalWrite(pedestrianGreenPin,pedestrianGreen);
  
  if (current - previousState > 1000){
    previousState = current;
    tone(buzzerPin, 200, 600); //durations for 0.6 seconds for beeping
  }
}

void fourthState(int current) { 
   //red for cars, green for people about to turn off, beepingn faster
  if (current - previousState > 600) {
  	previousState = current; 
    pedestrianGreen = !pedestrianGreen;
  	digitalWrite(pedestrianGreenPin,pedestrianGreen);
    tone(buzzerPin, 200, 250); //duration for 0.25 seconds
  }
}

void loop() {
  if (start == false) {
    
    firstState(); //first state if the button was not pressed
    buttonState =  digitalRead(buttonPin);
    if (buttonState == LOW){    // pressed
      start = true;
      startProgram = millis();  //time from the moment when the button was pressed
    }
  }else{ //when button was pressed

   int startTime = millis();  //current time, waiting 8 sec for the yelllow for cars

   if (startTime - startProgram >= 8000 && startTime - startProgram <= 11000) secondState();  //yellow for cars for 3 sec

   if (startTime - startProgram > 11000 && startTime - startProgram <= 19000) thirdState(startTime); //red for cars for 8 sec
    
   if (startTime - startProgram > 19000 && startTime - startProgram <= 23000) fourthState(startTime); //beeping for 4 sec

   //past 23 seconds, game can't continue
   if (startTime - startProgram > 23000) {
    noTone(buzzerPin);
    buttonState = HIGH;  //button is not pressed
    start = false; // the light game is stopped
   };
  }
}
