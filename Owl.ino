/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>
#include "./OwlTone5.h"

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position
int val;

void setup() {
  Serial.begin(115200);
  pinMode(2, INPUT);  // motion sensor
  pinMode(11, OUTPUT); // LED
  pinMode(3, OUTPUT); // speaker
  TCCR2A = _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);
  TCCR2B = _BV(CS20);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo.write(90);  // Servo to base position
}

//  Play owl voice
void play() { 
  for (int i = 0; i < u8bit_fukuro3_raw_len; i++) {
    OCR2B = pgm_read_byte_near(&u8bit_fukuro3_raw[i]);
    delayMicroseconds(125);
  }
} 

void loop() {
  // Read from motion sensor 
  val = digitalRead(2);
  Serial.print("motion=");
  Serial.println(val); 

  if (val == HIGH) {
    // LED ON
    for(int i=0; i<256; i=i+10) {
      analogWrite(11, i);
      delay(50);
    }
    // Servo to 180 degree
    for (pos = 90; pos <= 180; pos += 1) {
      myservo.write(pos);              
      delay(15);
    }
    // Servo to base position
    for (pos = 180; pos >= 90; pos -= 1) {
      myservo.write(pos);
      delay(15);
    }
    // Servo to 90 degree
    for (pos = 90; pos >= 0; pos -= 1) {
      myservo.write(pos);
      delay(15);
    }
    // Servo to base position
    for (pos = 0; pos <= 90; pos += 1) { 
      myservo.write(pos);
      delay(15);
    }
    // Owl voice
    play();
    delay(1000);
    play();

    // LED OFF
    for(int i=255; i>0; i=i-10) {
      analogWrite(11, i);
      delay(50);
    }
    digitalWrite(11, LOW);
  }
  // delay loop
  delay(1000);
}

