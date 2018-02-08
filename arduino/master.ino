#define NOOFSLAVES 6
#define NOOFTEAMS 3
#include <Wire.h>

//I2C
const int SLAVEID[NOOFSLAVES] = {4, 5, 3, 2, 6, 7};
byte inByte[NOOFSLAVES];
const int ID = 1;


//STATE SETTING
boolean win[NOOFSLAVES];
boolean team[NOOFTEAMS] = {0, 0};

//TIMERS
unsigned long cTime;
unsigned long pTime;
int interval = 100;
int pLedTime;
int intervalLed = 500;

//WINNERS
int numWinners = 0;

//LEDs
const int redPin[3] = {5, 6, 11};
const int greenPin[3] = {10, 8, 13};
const int bluePin[3] = {9, 7, 12};

void setup() {
  Wire.begin(ID);        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output

  //LED OUTPUTS
  for (int i = 0; i < 3; i++) {
    pinMode (redPin[i], OUTPUT);
    pinMode (greenPin[i], OUTPUT);
    pinMode (bluePin[i], OUTPUT);

  }

}

void loop() {
 
 for (int i = 0; i < 3; i++) {  //check the RGB LED
    analogWrite(redPin[i], 255);
    analogWrite (greenPin[i],0);
    analogWrite (bluePin[i], 0);
  }
 
  cTime = millis();
  if (cTime - pTime >= interval) {
    pTime = cTime;
    for (int i = 0; i < NOOFSLAVES; i++) {
      Wire.requestFrom(SLAVEID[i], 1);
      if (Wire.available()) {
        inByte[i] = Wire.read();
        /*
          Serial.print("ID:");
          Serial.print(SLAVEID[i]);
          Serial.print(" ");
          Serial.print(inByte[i]);
          Serial.print("    ");
        */
      }

    }
    // Serial.println();
  }

  for (int i = 0; i < NOOFSLAVES; i++) {
    if (int(inByte[i]) == 7) {
      win[i] = 1;
    }

    else {
      win[i] = 0;
    }
  }

  team[0] = win[0] && win[1];
  team[1] = win[2] && win[3];
  team[2] = win[4] && win[5];

  if (team[0] || team[1]) {
    //SOMEBODY HAS WON THE GAME


    Serial.println("WINNER WINNER CHICKEN DINNER!");

    if (team[0] && team[1]) {
      //both A&B win
      ledDisplay(2);
      Serial.println("BOTH WIN");
      while (true) {
        //WAIT FOREVER
      }
    }
    else if (team[0]) {
      //team 0 has won!
      ledDisplay(0);
      Serial.println("TEAM A WINS!");
      /*while(true){
        //delay forever!
        }*/
      delay(3000);
    }

    else if (team[1]) {
      //team 1 has won!
      ledDisplay(1);
      Serial.println("TEAM B WINS!");
      /* while(true){
        //delay forever!
        }*/
      delay(3000);
    }




  }


  else if (team[2] || team[1]) {
    //STILL PLAYING

    //SOMEBODY HAS WON THE GAME

    Serial.println("WINNER WINNER CHICKEN DINNER!");

    if (team[2] && team[1]) {
      //both C&B win
      ledDisplay(4);
      Serial.println("BOTH WIN");
      while (true) {
        //WAIT FOREVER
      }
    }
    else if (team[2]) {
      //team 2 has won!
      ledDisplay(3);
      Serial.println("TEAM C WINS!");
      /*while(true){
        //delay forever!
        }*/
      delay(3000);
    }

    else if (team[1]) {
      //team 1 has won!
      ledDisplay(1);
      Serial.println("TEAM B WINS!");
      /* while(true){
        //delay forever!
        }*/
      delay(3000);
    }

  }

  else if (team[2] || team[0]) {
    //STILL PLAYING

    //SOMEBODY HAS WON THE GAME

    Serial.println("WINNER WINNER CHICKEN DINNER!");

    if (team[2] && team[0]) {
      //both C&B win
      ledDisplay(5);
      Serial.println("BOTH WIN");
      while (true) {
        //WAIT FOREVER
      }
    }
    else if (team[2]) {
      //team 2 has won!
      ledDisplay(3);
      Serial.println("TEAM C WINS!");
      /*while(true){
        //delay forever!
        }*/
      delay(3000);
    }

    else if (team[0]) {
      //team 1 has won!
      ledDisplay(0);
      Serial.println("TEAM A WINS!");
      /* while(true){
        //delay forever!
        }*/
      delay(3000);
    }

  }
  ledDisplay(99);

}





void ledDisplay(int x) {



  switch (x) {

    case 99:
      //GENERAL DISPLAY
      if (cTime - pLedTime >= intervalLed) {
        pLedTime = cTime;
        for (int i = 0; i < 3; i++) {
          analogWrite (redPin[i], random(0, 255));
          analogWrite (bluePin[i], random(0, 255));
          analogWrite (greenPin[i], random(0, 255));
        }
      }

      break;


    case 0:
      //DISPLAY FOR TEAM A
      for (int i = 0; i < 3; i++) {
        analogWrite (redPin[i], 190);
        analogWrite (bluePin[i], 64);
        analogWrite (greenPin[i], 190);
      }

      break;

    case 1:
      //DISPLAY FOR TEAM B
      for (int i = 0; i < 3; i++) {
        analogWrite (redPin[i], 250);
        analogWrite (bluePin[i], 68);
        analogWrite (greenPin[i], 54);
      }
      break;

    case 2:
      //DISPLAY FOR TEAM A&&B
      analogWrite(redPin[1], 190);
      analogWrite (bluePin[1], 64);
      analogWrite (greenPin[1], 190);
      analogWrite (redPin[2], 250);
      analogWrite (bluePin[2], 68);
      analogWrite (greenPin[2], 54);
      analogWrite (redPin[3], 150);
      analogWrite (bluePin[3], 150);
      analogWrite (greenPin[3], 150);
      break;

    case 3:
      //DISPLAY FOR TEAM C
      for (int i = 0; i < 3; i++) {
        analogWrite (redPin[i], 15);
        analogWrite (bluePin[i], 222);
        analogWrite (greenPin[i], 30);
      }
      break;

    case 4:
      //DISPLAY FOR TEAM C&&B
      analogWrite(redPin[1], 150);
      analogWrite (bluePin[1], 150);
      analogWrite (greenPin[1], 150);
      analogWrite (redPin[2], 250);
      analogWrite (bluePin[2], 68);
      analogWrite (greenPin[2], 54);
      analogWrite (redPin[3], 15);
      analogWrite (bluePin[3], 222);
      analogWrite (greenPin[3], 30);
      break;

    case 5:
      //DISPLAY FOR TEAM C&&A
      analogWrite(redPin[1], 190);
      analogWrite (bluePin[1], 64);
      analogWrite (greenPin[1], 190);
      analogWrite (redPin[2], 150);
      analogWrite (bluePin[2], 150);
      analogWrite (greenPin[2], 150);
      analogWrite (redPin[3], 15);
      analogWrite (bluePin[3], 222);
      analogWrite (greenPin[3], 30);
      break;
  }


}

