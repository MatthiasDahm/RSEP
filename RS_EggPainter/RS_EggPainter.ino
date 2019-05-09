/**************************************************************
 * Test-Code für RS EGGPainter
 **************************************************************/

#include <Stepper.h>
#include <Servo.h>

const int stepsPerRevolution = 2048;  // change this to fit the number of steps per revolution
const int RevolutionsPerMinute = 15;         // Adjustable range of 28BYJ-48 stepper is 0~17 rpm

// Schrittmotor fuer X-Richtung (Eidrehung) an Pins 4 bis 7:
Stepper Stepper_X(stepsPerRevolution, 4, 6, 5, 7);
// Schrittmotor fuer X-Richtung (Stiftdrehung) an Pins 8 bis 11:
Stepper Stepper_Y(stepsPerRevolution, 8, 10, 9, 11);
// Servo für Stift hoch/runter an Pin 3 in setup()
Servo Servo_Stift;

int flag = 0;

void setup() {
  Stepper_X.setSpeed(RevolutionsPerMinute);
  Stepper_Y.setSpeed(RevolutionsPerMinute);
  Servo_Stift.attach(3);
  // initialize the serial port:
  Serial.begin(9600);
}

void Stift_hoch(){
  // Hier wird der Servo hochgefahren - WERTE ANPASSEN
  Servo_Stift.write(45);
}

void Stift_runter(){
  // Hier wird der Servo runtergefahren  - WERTE ANPASSEN
  Servo_Stift.write(90);
}


void loop() {
  
  flag = 1 - flag;
  
  if (flag == 0){
    Serial.println("Pen up");
      Stift_hoch(); 
    } else {
      Serial.println("Pen down");
      Stift_runter();
    }
  delay(500);
    
  // Nur 1/12 einer ganzen Umdrehung, damit der Stift nicht anschlaegt:
  Serial.println("X clockwise");
  Stepper_X.step(stepsPerRevolution/12);
  delay(500);
  Serial.println("Y clockwise");
  Stepper_Y.step(stepsPerRevolution/12);
  delay(500);

  // Nur 1/12 einer ganzen Umdrehung, damit der Stift nicht anschlaegt:
  Serial.println("X counterclockwise");
  Stepper_X.step(-stepsPerRevolution/12);
  delay(500);
  Serial.println("Y clockwise");
  Stepper_Y.step(-stepsPerRevolution/12);
  delay(500);

}
