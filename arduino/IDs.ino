#include <Wire.h>
#define NOOFLEDS 8
//I2C
const int ID = 4; // CHANGE ID FOR EACH SLAVE NODE

int ledPin[NOOFLEDS] = {5, 6, 7, 8, 9, 10, 11, 12};
//

unsigned long pTime2;
int interval2 = 20;


//PIN VARIABLES --- DO NOT USE 2 & 3 ON THE MICRO AS THEY ARE RESERVED OF SDA AND SCK
const int echoPin = A5; //BLUE
const int trigPin = A4; //WHITE

//DISTANCE VARIABLES
int avgDistance;
int total;

//THRESHOLDS
const int LOWTRESHOLD = 35;
const int UPPERTRESHOLD = 45;
const int MAXTRESHOLD = 80;

//OTHER VARIABLES
const int NOOFREADINGS = 10;

//COUNTERS
int counter = 0;

//STATE
boolean currentState;
boolean previousState;

//TIMERS
unsigned long cTime;
unsigned long pTime;
const int INTERVAL = 500; //THE SMALLER THE INTERVAL, THE HARDER THE GAME!!!

void setup() {
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);

  for (int i = 0; i < NOOFLEDS; i++) {
    pinMode(ledPin[i], OUTPUT);
  }

  //COMMUNICATIONS
  Serial.begin(9600);

  Wire.begin(ID);                // join i2c bus with address #ID
  Wire.onRequest(requestEvent); // register event

  Serial.print("ARDUINO MICRO ID:");
  Serial.println(ID);
  //delay(200);

  //STARTUP
  digitalWrite(trigPin, LOW); //JUST IN CASE
}

void loop() {

  checkSensors();

  //delay(5);
  stateCheck();

  counterUpdate();
  
  Serial.println(byte(counter));
  //delay(50);
  //  counter = int(map(counter, 0, 16, 0, NOOFLEDS ));
  counter = constrain(counter, 0, NOOFLEDS - 1 );

  digitalWrite(ledPin[counter], HIGH);

  for (int i = counter + 1; i < NOOFLEDS; i++) {
    digitalWrite(ledPin[i], LOW);
  }


}


void checkSensors() {
  total = 0;
  if (cTime - pTime2 >= interval2) {
    pTime2 = cTime;
    for (int i = 0; i < NOOFREADINGS; i++) {
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);
      int duration = pulseIn(echoPin, HIGH);
      int distance = duration / 59;
      total += distance;
      // delay(2); //TO REPLACE LATER
    }
  }

  avgDistance = total / NOOFREADINGS;

}

void stateCheck() {
    if (avgDistance <= LOWTRESHOLD && avgDistance != 0) {
      //HAND IN LOWER SECTION
      // Serial.println("LOWER SECTION");
      currentState = 0;
    }

    else if (avgDistance >= UPPERTRESHOLD && avgDistance <= MAXTRESHOLD) {
      // HAND IN UPPER SECTION
      // Serial.println("UPPER SECTION");
      currentState = 1;
    }

    else {
      // HAND OUT OF RANGE
      //  Serial.println("OUT OF RANGE");
    }
  }


  void counterUpdate() {
    if (currentState != previousState) {
      //ARMS ARE MOVING
      previousState = currentState;
      counter++;
    }

    cTime = millis();
    if (cTime - pTime >= INTERVAL) {
      //time has elapsed, let's reduce counter
      pTime = cTime;
      counter--;
    }
    counter = constrain(counter, 0, 100);
  }

  void requestEvent() {
    Wire.write(byte(counter));
  }

