#include <sparki.h>
#define STATE_FIND_OBJ 0
#define STATE_DRIVE_TO_OBJ 1
#define DETECT_LINE 2

int currentState = 0;
int distanceToObject = 30;
int distanceBeforeObject  = 7;

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
    sparki.moveRight(5);
    distance = sparki.ping();
    if (distance > 0 && distance < 30){
      sparki.moveRight(10);
      currentState = 1;
    }
    break;
  case STATE_DRIVE_TO_OBJ:
    sparki.moveForward(1);
    distance = sparki.ping();
    delay(1000);
    if(distance <= 5 && distance > 0){
     sparki.gripperClose();
     delay(5000);
     sparki.gripperStop();
     delay(1000);
     sparki.moveRight(180);
     currentState = 2;
    }
    break;
   case DETECT_LINE:
    sparki.moveForward(1);
    if (readSensors()){
      currentState = 3;
    }
    
    break;
  default:
  //Panic!
    break;
 }

}

bool readSensors() {
//cm_distance = sparki.ping();
int line_left = sparki.lightLeft();
int line_right = sparki.lightRight();
int line_center = sparki.lightCenter();
if (line_center < 500){
  return true;
}
return false;
}