/*
 * This program takes as input two digital inputs (defined as PWMSEL0 and PWMSEL1).
 * It then uses these two inputs to determine the PWM to output.
 * 
 * PWMSEL0: HIGH  => Do Not Rotate Servo
 *          LOW   => Rotate Servo
 * PWMSEL1: HIGH  => Rotate Counter Clockwise (Lower)
 *          LOW   => Rotate Clockwise (Raise)
 *  ** PWMSEL* reads HIGH when open, LOW when closed
 */
#include <Servo.h>

// Pin Assignments
const int PWMSEL0 = 2;
const int PWMSEL1 = 3;
const int PWMOUT  = 9;

Servo servo;

void setup() {
  Serial.begin(115200);             // Initialize Serial Output to Console

  pinMode(PWMSEL0, INPUT);          // Set pins as inputs (control servo direction)
  pinMode(PWMSEL1, INPUT);

  servo.attach(PWMOUT);             // PWM Output
}

void loop() {
  int pwm_sel0 = digitalRead(PWMSEL0);
  int pwm_sel1 = digitalRead(PWMSEL1);

  Serial.print("PWM SEL: ");
  Serial.print(pwm_sel0);
  Serial.println(pwm_sel1);

  /*
   * PWM SEL0 Determines whether or not Servo should move
   * PWM SEL1 Determines CW or CCW
   */
  /*
  if(pwm_sel0 == HIGH) {
    // Servo Should be stationary
    servo.write(90);
  } else if(pwm_sel1 == HIGH) {
    // Rotate Servo CW
    servo.write(180);
  } else {
    // Rotate Servo CCW
    servo.write(0);
  }
  */

  /* 
   *  Currently, only support for raising the Dog Feeder
   *  on Web App. Therefore, we will use a simpler model
   *  for now and only use one select input.
   */
  if(pwm_sel0 == HIGH)
  {
    // Rotate CW
    servo.write(0);
  }
  else
  {
    servo.write(85);
  }

  delay(1000);                // Update Every Second
}
