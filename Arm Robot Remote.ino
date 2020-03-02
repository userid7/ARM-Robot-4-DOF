#define stepPin1 2
#define stepPin2 4
#define dirPin1 5
#define dirPin2 7
#define EN 8

#include <Servo.h>
#include <SoftwareSerial.h>

SoftwareSerial blue(A1, A2);
Servo ser_yaw, ser_roll;


String cmd;
int kecc = 250;
char data;
int yaw_ = 90, roll_ = 90;
float yaw = 90, roll = 90;

void move_servo() {
  if (data == 'F') stepping(stepPin1, 0, kecc);
  else if (data == 'G') do_yaw(0);
  else if (data == 'I') do_roll(0);
  else if (data == 'H') do_roll(1);
  else if (data == 'J') do_yaw(1);
  else if (data == 'B') stepping(stepPin1, 1, kecc);
  else if (data == 'L') stepping(stepPin2, 0, kecc);
  else if (data == 'R') stepping(stepPin2, 1, kecc);
  else if (data == 'C') digitalWrite(EN, LOW); //W
  else if (data == 'M') digitalWrite(EN, HIGH); //w

  //  else if (data == 'G') stepping2(1,1,0,1,kecc);
  //  else if (data == 'I') stepping2(1,1,0,0,kecc);
  //  else if (data == 'H') stepping2(1,1,1,1,kecc);
  //  else if (data == 'J') stepping2(1,1,1,1,kecc);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(stepPin1, OUTPUT);
  pinMode(stepPin2, OUTPUT);
  pinMode(dirPin1, OUTPUT);
  pinMode(dirPin2, OUTPUT);
  pinMode(EN, OUTPUT);
  digitalWrite(EN, HIGH);
  ser_roll.attach(9);
  ser_roll.write(yaw);
  ser_yaw.attach(10);
  ser_yaw.write(roll);
  Serial.begin(9600);
  blue.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (blue.available() > 0) {
    data = blue.read();
    Serial.println(data);
  }
  move_servo();
  //    if (cmd == "1") {
  //      Serial.println("Stepper1 Kanan");
  //      stepping(stepPin1, 0, kecc);
  //    }
  //    else if (cmd == "2") {
  //      Serial.println("Stepper1 Kiri");
  //      stepping(stepPin1, 1, kecc);
  //    }
  //    else if (cmd == "3") {
  //      Serial.println("Stepper2 Kanan");
  //      stepping(stepPin2, 0, kecc);
  //    }
  //    else if (cmd == "4") {
  //      Serial.println("Stepper2 Kiri");
  //      stepping(stepPin2, 1, kecc);
  //    }
}

void stepping(int stepPin, bool dir, int kec) {
  for (int i = 0; i < 50; i++) {
    digitalWrite(stepPin + 3, dir);
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(kec);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(kec);
  }
  //  Serial.print(stepPin);
  //  Serial.print(dir);
  //  Serial.println(kec);
}

void stepping2(bool step1, bool step2, bool dir1, bool dir2, int kec) {
  digitalWrite(dirPin1, dir1);
  digitalWrite(dirPin2, dir2);
  for (int i = 0; i < 50; i++) {
    digitalWrite(stepPin1, step1);
    digitalWrite(stepPin2, step2);
    delayMicroseconds(kec);
    digitalWrite(stepPin1, 0);
    digitalWrite(stepPin2, 0);
    delayMicroseconds(kec);
  }
}

void do_yaw(bool dir_yaw) {
  float dyaw =  0.4;
  if (dir_yaw == 0)yaw = yaw + dyaw;
  else yaw = yaw - dyaw;
  if (yaw > 180)yaw = 180;
  if (yaw < 0)yaw = 0;
  yaw_ = yaw;
  ser_yaw.write(yaw_);
  Serial.println(yaw_);
}

void do_roll(bool dir_roll) {
  float droll = 0.4;
  if (dir_roll == 0)roll = roll + droll;
  else roll = roll - droll;
  if (roll > 180)roll = 180;
  if (roll < 0)roll = 0;
  roll_ = roll;
  ser_roll.write(roll_);
  Serial.println(roll_);
}
