/*
 * This program takes as input two digital inputs (defined as PWMSEL0 and PWMSEL1).
 * It then uses these two inputs to determine the PWM to output.
 * 
 * PWMSEL0: HIGH  => Do Not Rotate Servo
 *          LOW   => Rotate Servo
 * PWMSEL1: HIGH  => Rotate Clockwise
 *          LOW   => Rotate Counter Clockwise        
 *  ** PWMSEL* reads HIGH when open, LOW when closed
 */
#include <Servo.h>

// Pin Assignments
const int PWMSEL0 = 2;
const int PWMSEL1 = 3;
const int PWMOUT  = 9;

Servo servo;

void setup() {
  Serial.begin(115200);             // Initialze Serial Output to Console

  pinMode(PWMSEL0, INPUT_PULLUP);   // INPUT requires external pulldown
  pinMode(PWMSEL1, INPUT_PULLUP);

  servo.attach(PWMOUT);             // PWM Output
}

void loop() {
  int pwm_sel0 = digitalRead(PWMSEL0);
  int pwm_sel1 = digitalRead(PWMSEL1);

  Serial.print("PWM SEL: ");
  Serial.print(pwm_sel0);
  Serial.print(pwm_sel1);
  Serial.println(")");

  /*
   * PWM SEL0 Determines whether or not Servo should move
   * PWM SEL1 Determines CW or CCW
   */
  if(pwm_sel0 == HIGH) {
    // Servo Should be stationary
    servo.write(90);    // May have to modify this
  } else if(pwm_sel1 == HIGH) {
    // Rotate Servo CW
    servo.write(180);   // May have to modify this
  } else {
    // Rotate Servo CCW
    servo.write(0);     // May have to modify this
  }

  delay(1000);
}
