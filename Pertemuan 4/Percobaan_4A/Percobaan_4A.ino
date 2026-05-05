#include <Servo.h>
Servo myservo;

const int potensioPin = A0;
const int servoPin = 9;

int pos = 0; // sudut servo
int val = 0; // nilai ADC

void setup() {
  myservo.attach(servoPin);
  Serial.begin(9600);
}

void loop() {
  val = analogRead(potensioPin);
  pos = map(val,
            0,    // min ADC
            1023, // max ADC
            0,    // sudut min
            180   // sudut max
            );
  myservo.write(pos);
  Serial.print("ADC Potensio: ");
  Serial.print(val);
  Serial.print(" | Sudut Servo: ");
  Serial.println(pos);
  delay(100);
} 
