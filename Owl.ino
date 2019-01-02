/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>
#include "./OwlTone.h"

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position
int val;

void setup() {
  Serial.begin(115200);
  pinMode(2, INPUT);  // motion sensor
  pinMode(11, OUTPUT); // LED
  pinMode(3, OUTPUT); // speaker
//  TCCR2A = 0b00100011; // *** 高速PWM設定
//  TCCR2B = 0b00011001;
//  OCR2A = 255;
//  OCR2B = 0; // *** Duty 0 - 255
  TCCR2A = _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);
  TCCR2B = _BV(CS20);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo.write(90); // tell servo to go to position in variable 'pos'
}

void play() {
/*
  tone(3,131,1000) ;
  delay(1000) ;
  tone(3,147,1000) ;
  delay(1000) ;
  tone(3,165,1000) ;
  delay(1000) ;
  tone(3,175,1000) ;
  delay(1000) ;
  tone(3,196,1000) ;
  delay(1000) ;
  tone(3,220,1000) ;
  delay(1000) ;
  tone(3,247,1000) ;
  delay(1000) ;

  tone(3,139,1000) ;
  delay(1000) ;
  tone(3,156,1000) ;
  delay(1000) ;
  tone(3,185,1000) ;
  delay(1000) ;
  tone(3,208,1000) ;
  delay(1000) ;
  tone(3,233,1000) ;
  delay(1000) ;
 */
 
  for (int i = 0; i < u8bit_fukuro3_raw_len; i++) {
    OCR2B = pgm_read_byte_near(&u8bit_fukuro3_raw[i]);
    delayMicroseconds(125);
  }
} 

void loop() {
  val = digitalRead(2);
  Serial.print("motion=");
  Serial.println(val); 

  if (val == HIGH) {
    //digitalWrite(13, HIGH);
    for(int i=0; i<256; i=i+10) {
      analogWrite(11, i);
      delay(50);
    }

    for (pos = 90; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
    for (pos = 180; pos >= 90; pos -= 1) { // goes from 180 degrees to 0 degrees
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
    for (pos = 90; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
    for (pos = 0; pos <= 90; pos += 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
    play();
    delay(1000);
    play();
    for(int i=255; i>0; i=i-10) {
      analogWrite(11, i);
      delay(50);
    }
    digitalWrite(11, LOW);
  }
 
  delay(1000);
}

