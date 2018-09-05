#include <sparki.h>
#define STATE_FIND_OBJ 0
#define STATE_DRIVE_TO_OBJ 1
#define DETECT_LINE 2
#define FOLLOW_LINE 3
#define DROP_OBJECT 4

int currentState = 0;
int distanceToObject = 30;
int distanceBeforeObject  = 7;

int line_left = 1000;
int line_center = 1000;
int line_right = 1000;
int threshhold = 500;

void setup() {
  // put your setup code here, to run once:
  sparki.RGB(RGB_RED);
  sparki.servo(SERVO_CENTER);
  delay(5000);
  sparki.gripperOpen();
  delay(5000);
  sparki.gripperStop();
  sparki.RGB(RGB_GREEN);
  // put your setup code here, to run once:

}

void loop() {
int distance = -1;
switch(currentState) {
  case STATE_FIND_OBJ:
    sparki.moveRight();
    distance = sparki.ping();
    if (distance > 0 && distance < 30){
      sparki.moveStop();
      currentState = 1;
    }
    break;
  case STATE_DRIVE_TO_OBJ:
    sparki.moveForward();
    distance = sparki.ping();
    if(distance <= 5 && distance > 0){
     sparki.moveStop();
     delay(1000);
     sparki.moveForward(1);
     sparki.moveStop();
     sparki.gripperClose();
     delay(5000);
     sparki.gripperStop();
     delay(1000);
     sparki.moveRight(180);
     currentState = 2;
    }
    break;
   case DETECT_LINE:
    sparki.moveForward();
    delay(1000);
    readSensors();
    if (line_center < threshhold){
      sparki.moveRight();
      delay(1000);
      currentState = 3;
      break;
    }
    
    break;

   case FOLLOW_LINE:
    readSensors();
    if (line_left < threshhold){
      sparki.moveLeft();
    }
    if (line_right < threshhold) {
      sparki.moveRight();
    }
    if (line_center < threshhold) {
      sparki.moveForward();
    }
    if ((line_center < threshhold) && (line_left > threshhold) && (line_right > threshhold)){
      sparki.moveForward();
    }
    if ((line_center < threshhold) && (line_left < threshhold) && (line_right < threshhold)){
      currentState = DROP_OBJECT;
    }
    
    break;
   case DROP_OBJECT:
    sparki.moveStop();
    delay(1000);
    sparki.beep();
    delay(1000);
    sparki.gripperOpen();
    delay(5000);
    break;
    
    
  default:
  //Panic!
    break;
 }

}

void readSensors() {
line_left = sparki.lineLeft();
line_right = sparki.lineRight();
line_center = sparki.lineCenter();
}