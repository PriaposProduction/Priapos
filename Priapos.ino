#include <Adafruit_NeoPixel.h>
#include <Servo.h>

unsigned long startTime;
unsigned long currentTime;
unsigned long timeinterval;

//the following lines define the standard pins used
#define LEDPIN 6 //blue
#define HATPIN 7 //grey
#define BIRDPIN 8
#define HEADSERVOPIN 9
#define ARMSERVOPIN 10
#define TOLERANCE_VALUE 150

//initialisation if LEDs
Adafruit_NeoPixel leds = Adafruit_NeoPixel(2, LEDPIN, NEO_GRB + NEO_KHZ800);
//definition of headServo
Servo headServo;
Servo armServo;
//the following constants are the colors used for the eyes
uint32_t red = leds.Color(255, 0, 0);
uint32_t orange = leds.Color(255, 50, 0);
uint32_t yellow = leds.Color(255, 255, 0);
uint32_t green = leds.Color(0, 255, 0);
uint32_t purple = leds.Color(186, 85, 211);
uint32_t pink = leds.Color(255, 20, 147);
uint32_t black = leds.Color(0, 0, 0);

//fading parameters for leds
int brightness = 0;    // how bright the LED is
int fadeAmount = 5;    // how many points to fade the LED by


void setup() {
  leds.begin();
  setLEDColor(red);

  //attach head servo to pin
  headServo.attach(HEADSERVOPIN);
  //attach arm servo to pin
  armServo.attach(ARMSERVOPIN);
  //start serial connection
  Serial.begin(9600);

  //output pins
  pinMode(LEDPIN, OUTPUT);
  //input pins
  pinMode(HATPIN, INPUT);
  pinMode(BIRDPIN, INPUT);
  //pull up resistors
  digitalWrite(HATPIN, HIGH);
  digitalWrite(BIRDPIN, HIGH);

  //moveHeadRight();
}

void loop() {
  wisdomQuiz();
  //consentrationQuiz();
  //moveHeadRight();
  //consentrationQuiz();
}

void checkInitiationOfAgilityQuiz() {

  startTime = millis();
  while (true) {
    if (digitalRead(HATPIN) == LOW) {
      timeinterval = millis() - startTime;
      if (timeinterval > TOLERANCE_VALUE) {
        break;
      }
    } else {
      startTime = millis();
    }
    delay(5);
  }

  startTime = millis();
  while (true) {
    if (digitalRead(HATPIN) == HIGH) {
      timeinterval = millis() - startTime;
      if (timeinterval > TOLERANCE_VALUE) {
        break;
      }
    } else {
      startTime = millis();
    }
    delay(5);
  }

  startTime = millis();
  while (true) {
    if (digitalRead(HATPIN) == LOW) {
      timeinterval = millis() - startTime;
      if (timeinterval > 100) {
        break;
      }
      delay(5);
    }
  }

  //start second quiz
  agilityQuiz();
}

void moveArmDown() {
  for (int pos = 180; pos >= 90; pos -= 1) {
    // in steps of 1 degree
    armServo.write(pos);
    delay(20);
  }
}

void moveArmUp() {
  for (int pos = 90; pos <= 180; pos += 1) {
    // in steps of 1 degree
    armServo.write(pos);
    delay(20);
  }
}

void moveHeadLeft() {
  for (int pos = 0; pos <= 90; pos += 1) { // goes from 90 degrees to 180 degrees
    // in steps of 1 degee
    headServo.write(pos);
    delay(20);
  }
}

void moveHeadRight() {
  for (int pos = 90; pos > 0; pos -= 1) { // goes from 90 degrees to 180 degrees
    // in steps of 1 degree
    headServo.write(pos);
    delay(20);
  }
}

void shakeHead() {
  for (int pos = 90; pos <= 135; pos += 1) { // goes from 90 degrees to 135 degrees
    // in steps of 1 degree
    headServo.write(pos);
    delay(20);
  }
  for (int pos = 135; pos >= 45; pos -= 1) { // goes from 135 degrees to 45 degrees
    // in steps of 1 degree
    headServo.write(pos);
    delay(20);
  }
  for (int pos = 45; pos <= 90; pos += 1) { // goes from 45 degrees to 90 degrees
    // in steps of 1 degree
    headServo.write(pos);
    delay(20);
  }
}

void setLEDColor(uint32_t color) {
  leds.setPixelColor(0, color);
  leds.setPixelColor(1, color);
  leds.show();
}

void agilityQuiz() {
  //change eye color for quiz
  int pauseShort = 1000;
  int pauseLong = 2000;
  setLEDColor(purple);
  delay(pauseShort);

  setLEDColor(black);
  delay(pauseShort);

  setLEDColor(purple);
  delay(pauseShort);

  setLEDColor(black);
  delay(pauseShort);

  setLEDColor(pink);
  delay(pauseLong);

  setLEDColor(black);
  delay(pauseShort);

  setLEDColor(pink);
  delay(pauseLong);

  setLEDColor(black);
  delay(pauseShort);

  setLEDColor(purple);

  delay(pauseShort);

  setLEDColor(black);
  delay(pauseShort);

  setLEDColor(pink);
  delay(pauseLong);

  setLEDColor(black);
  delay(pauseShort);

  setLEDColor(purple);
  delay(pauseShort);

  setLEDColor(black);
  delay(pauseShort);

  setLEDColor(orange);

  //wait until user lifts head
  Serial.println("Before entered");
  while (digitalRead(HATPIN) == LOW) {
    delay(10);
  }
  Serial.println("After entered");

  bool waitingForFirstInput = true;
  bool waitingForSecondInput = false;
  bool waitingForThirdInput = false;
  bool waitingForFourthInput = false;
  bool waitingForFifthInput = false;
  bool waitingForSixthInput = false;
  bool waitingForSeventhInput = false;
  bool error = false;
  bool waitingForHatToBePutDown = true;

  while (waitingForFirstInput) {
    //check if first move was done correctly PURPLE
    if (digitalRead(HATPIN) == HIGH) {
      Serial.println("First hat was taken!");
      //change eyecolor to purple
      setLEDColor(purple);
      startTime = millis();
      while (waitingForHatToBePutDown) {
        if (digitalRead(HATPIN) == LOW) {
          Serial.println("First hat was reput successfully!");
          currentTime = millis();
          timeinterval = currentTime - startTime;
          Serial.println(timeinterval);
          if (timeinterval > TOLERANCE_VALUE && timeinterval < 2000) {
            Serial.println("First move was made successfully!");
            delay(30);
            waitingForFirstInput = false;
            waitingForSecondInput = true;
            waitingForHatToBePutDown = false;

            error = false;
            //turn off eyes
            setLEDColor(black);
          }
          else if (timeinterval >= 2000) {
            Serial.println("First move was made wrong!");
            delay(30);
            waitingForFirstInput = false;
            waitingForSecondInput = false;
            waitingForHatToBePutDown = false;
            error = true;
            //turn off eyes
            setLEDColor(black);
          }
        }
        delay(5);
      }
      waitingForHatToBePutDown = true;
    }
  }

  while (waitingForSecondInput) {
    //check if second move was done correctly PURPLE
    if (digitalRead(HATPIN) == HIGH) {
      Serial.println("Second hat was taken!");
      //change eyecolor to purple
      setLEDColor(purple);
      startTime = millis();
      while (waitingForHatToBePutDown) {
        if (digitalRead(HATPIN) == LOW) {
          Serial.println("Second hat was reput successfully!");
          currentTime = millis();
          timeinterval = currentTime - startTime;
          Serial.println(timeinterval);
          if (timeinterval > TOLERANCE_VALUE && timeinterval < 2000) {
            Serial.println("Second move was made successfully!");
            delay(30);
            waitingForSecondInput = false;
            waitingForThirdInput = true;
            waitingForHatToBePutDown = false;

            error = false;
            //turn off eyes
            setLEDColor(black);
          }
          else if (timeinterval >= 2000) {
            Serial.println("Second move was made wrong!");
            delay(30);
            waitingForSecondInput = false;
            waitingForThirdInput = false;
            waitingForHatToBePutDown = false;
            error = true;
            //turn off eyes
            setLEDColor(black);
          }
        }
        delay(5);
      }
      waitingForHatToBePutDown = true;
    }
  }

  while (waitingForThirdInput) {
    //check if third move was done correctly PINK
    if (digitalRead(HATPIN) == HIGH) {
      Serial.println("Third hat was taken!");
      //change eyecolor to pink
      setLEDColor(pink);
      startTime = millis();
      while (waitingForHatToBePutDown) {
        if (digitalRead(HATPIN) == LOW) {
          Serial.println("Third hat was reput successfully!");
          currentTime = millis();
          timeinterval = currentTime - startTime;
          Serial.println(timeinterval);
          if (timeinterval > 1500) {
            Serial.println("Third move was made successfully!");
            delay(30);
            waitingForThirdInput = false;
            waitingForFourthInput = true;
            waitingForHatToBePutDown = false;

            error = false;
            //turn off eyes
            setLEDColor(black);
          }
          else if (timeinterval <= 1500 && timeinterval > TOLERANCE_VALUE) {
            Serial.println("Third move was made wrong!");
            delay(30);
            waitingForThirdInput = false;
            waitingForFourthInput = false;
            waitingForHatToBePutDown = false;
            error = true;
            //turn off eyes
            setLEDColor(black);
          }
        }
        delay(5);
      }
      waitingForHatToBePutDown = true;
    }
  }

  while (waitingForFourthInput) {
    //check if forth move was done correctly PINK
    if (digitalRead(HATPIN) == HIGH) {
      Serial.println("Fourth hat was taken!");
      //change eyecolor to pink
      setLEDColor(pink);
      startTime = millis();
      while (waitingForHatToBePutDown) {
        if (digitalRead(HATPIN) == LOW) {
          Serial.println("Fourth hat was reput successfully!");
          currentTime = millis();
          timeinterval = currentTime - startTime;
          Serial.println(timeinterval);
          if (timeinterval > 1500) {
            Serial.println("Fourth move was made successfully!");
            delay(30);
            waitingForFourthInput = false;
            waitingForFifthInput = true;
            waitingForHatToBePutDown = false;

            error = false;
            //turn off eyes
            setLEDColor(black);
          }
          else if (timeinterval <= 1500 && timeinterval > TOLERANCE_VALUE) {
            Serial.println("Fourth move was made wrong!");
            delay(30);
            waitingForFourthInput = false;
            waitingForFifthInput = false;
            waitingForHatToBePutDown = false;
            error = true;
            //turn off eyes
            setLEDColor(black);
          }
        }
        delay(5);
      }
      waitingForHatToBePutDown = true;
    }
  }

  while (waitingForFifthInput) {
    //check if fifth move was done correctly PURPLE
    if (digitalRead(HATPIN) == HIGH) {
      Serial.println("Fifth hat was taken!");
      //change eyecolor to purple
      setLEDColor(purple);
      startTime = millis();
      while (waitingForHatToBePutDown) {
        if (digitalRead(HATPIN) == LOW) {
          Serial.println("Fifth hat was reput successfully!");
          currentTime = millis();
          timeinterval = currentTime - startTime;
          Serial.println(timeinterval);
          if (timeinterval > TOLERANCE_VALUE && timeinterval < 2000) {
            Serial.println("Fifth move was made successfully!");
            delay(30);
            waitingForFifthInput = false;
            waitingForSixthInput = true;
            waitingForHatToBePutDown = false;

            error = false;
            //turn off eyes
            setLEDColor(black);
          }
          else if (timeinterval >= 2000) {
            Serial.println("Fifth move was made wrong!");
            delay(30);
            waitingForFifthInput = false;
            waitingForSixthInput = false;
            waitingForHatToBePutDown = false;
            error = true;
            //turn off eyes
            setLEDColor(black);
          }
        }
        delay(5);
      }
      waitingForHatToBePutDown = true;
    }
  }

  while (waitingForSixthInput) {
    //check if sixth move was done correctly PINK
    if (digitalRead(HATPIN) == HIGH) {
      Serial.println("Sixth hat was taken!");
      //change eyecolor to pink
      setLEDColor(pink);
      startTime = millis();
      while (waitingForHatToBePutDown) {
        if (digitalRead(HATPIN) == LOW) {
          Serial.println("Sixth hat was reput successfully!");
          currentTime = millis();
          timeinterval = currentTime - startTime;
          Serial.println(timeinterval);
          if (timeinterval > 1500) {
            Serial.println("Sixth move was made successfully!");
            delay(30);
            waitingForSixthInput = false;
            waitingForSeventhInput = true;
            waitingForHatToBePutDown = false;

            error = false;
            //turn off eyes
            setLEDColor(black);
          }
          else if (timeinterval <= 1500 && timeinterval > TOLERANCE_VALUE) {
            Serial.println("Sixth move was made wrong!");
            delay(30);
            waitingForSixthInput = false;
            waitingForSeventhInput = false;
            waitingForHatToBePutDown = false;
            error = true;
            //turn off eyes
            setLEDColor(black);
          }
        }
        delay(5);
      }
      waitingForHatToBePutDown = true;
    }
  }

  while (waitingForSeventhInput) {
    //check if seventh move was done correctly PURPLE
    if (digitalRead(HATPIN) == HIGH) {
      //change eyecolor to purple
      setLEDColor(purple);
      startTime = millis();
      while (waitingForHatToBePutDown) {
        if (digitalRead(HATPIN) == LOW) {
          Serial.println("Seventh hat was reput successfully!");
          currentTime = millis();
          timeinterval = currentTime - startTime;
          Serial.println(timeinterval);
          if (timeinterval > TOLERANCE_VALUE && timeinterval < 2000) {
            delay(30);
            Serial.println("Seventh move was made successfully!");
            waitingForSeventhInput = false;
            waitingForHatToBePutDown = false;
            error = false;
            setLEDColor(yellow);
            consentrationQuiz();
          }
          else if (timeinterval >= 2000) {
            Serial.println("Seventh move was made wrong!");
            waitingForSeventhInput = false;
            waitingForHatToBePutDown = false;
            error = true;

            //turn off eyes
            setLEDColor(black);
          }
        }
        delay(5);
      }
      waitingForHatToBePutDown = true;
    }
  }

  if (error) {
    Serial.println("Entered error state!");
    errorSignal();
    agilityQuiz();
    error = false;
  }
}

void wisdomQuiz() {
  //check if wisdom puzzle was solved correctly
  if (digitalRead(HATPIN) == HIGH) {
    //change eye color
    setLEDColor(orange);

    //check if next quiz should start
    checkInitiationOfAgilityQuiz();

  }
  else if (digitalRead(BIRDPIN) == HIGH) {
    errorSignal();
    wisdomQuiz();
  }
  else {
    wisdomQuiz();
  }
}


void errorSignal() {
  //if a wrong quiz element was moved show fading red eyes
  //save current eye color
  leds.setBrightness(255);
  Serial.println("Entered errorSignal");
  uint32_t color = leds.getPixelColor(0);

  //change color to red
  setLEDColor(red);
  for (int i = 0; i < 154; i++) {
    // set the brightness of pin 9:
    leds.setBrightness(brightness);
    setLEDColor(red);

    // change the brightness for next time through the loop:
    brightness = brightness + fadeAmount;

    // reverse the direction of the fading at the ends of the fade:
    if (brightness == 0 || brightness == 255) {
      fadeAmount = -fadeAmount ;
    }
    // wait for 30 milliseconds to see the dimming effect
    delay(30);
  }
  //change color back to former color
  leds.setBrightness(255);
  setLEDColor(color);

  //shake head to signal error
  //shakeHead();
}

void consentrationQuiz() {
  bool takeTheBird = true;
  while (takeTheBird) {
    moveArmDown();

    if (digitalRead(BIRDPIN) == HIGH) {
      Serial.println("Entered brid taken!");
      takeTheBird = false;
    }

    moveArmUp();

    Serial.println("Entered after move arm!");
    if (digitalRead(BIRDPIN) == HIGH) {
      Serial.println("Entered brid taken!");
      takeTheBird = false;
    }
    delay(5);
  }
  //change eye color to green
  setLEDColor(green);
  delay(5);
  moveHeadRight();
  int i = 1;
  while (i < 2000) {
    Serial.println(i);
    i++;
    delay(30);
  }
  //change eye color to green
  setLEDColor(red);

  //move Head back to center
  moveHeadLeft();
  //put arm up
  moveArmDown();
  wisdomQuiz();
}

