#include <Wire.h>
#include <MPU6050.h>
#include <SR04.h>
#include <Servo.h>

Servo sg90; // Gyroscope servo
int servoPinGyro = 10; // Gyroscope servo pin
int servoPinElevator = 12; // Ultrasonic sensor servo pin
int echo_pin = 9; // Ultrasonic sensor echo pin
int trig_pin = 13; // Ultrasonic sensor trig pin

// Ultrasonic sensor servo positions
int elevatorPositionDown = 0;
int elevatorPositionUp = 90;
int updateInterval = 1000;
int groundDistance = 100;
long distance;

MPU6050 sensor;
int16_t ax, ay, az;
int16_t gx, gy, gz;

SR04 distanceSensor(echo_pin, trig_pin);
Servo myServo;



void setup() {
  // put your setup code here, to run once:
  sg90.attach(servoPinGyro);
  myServo.attach(servoPinElevator);

  Wire.begin();
  Serial.begin(9600);
  Serial.println("Initializing the sensor");
  sensor.initialize();
  Serial.println(sensor.testConnection() ? "Successfully Connected" : "Connection failed");
  delay(1000);
  Serial.println("Taking Values from the sensor");
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
   // Ultrasonic sensor servo loop
  distance = distanceSensor.Distance();

  if (distance < groundDistance) {
    myServo.write(elevatorPositionUp);
  } else {
    myServo.write(elevatorPositionDown);
  }

  // Wait time between readings for ultrasonic sensor
  delay(updateInterval);

  // Gyro servo
  sensor.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  ax = map(ax, -17000, 17000, 0, 180);
  Serial.println(ax);
  sg90.write(ax);
  delay(200);
}
