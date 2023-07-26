#include <Wire.h>
#include <MPU6050.h>
#include <Servo.h>

Servo sg90Y1, sg90Y2, sg90X1, sg90X2;

int servoY1_pin = 12;
int servoY2_pin = 13;
int servoX1_pin = 10;
int servoX2_pin = 11;

int16_t ax, ay, az;
int16_t gx, gy, gz;

void setup() {
  sg90Y1.attach(servoY1_pin);
  sg90Y2.attach(servoY2_pin);
  sg90X1.attach(servoX1_pin);
  sg90X2.attach(servoX2_pin);

  Wire.begin();
  Serial.begin(9600);

  Serial.println("Initializing the sensor");

  if (senser.testConnection()) {
    Serial.println("Successfully Connected");
  } else {
    Serial.println("Connection failed");
    while (1);
  }

  delay(1000);
}

void loop() {
  senser.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  // Map Y-axis values to servo angles
  int servoY1_angle = map(ay, -17000, 17000, 0, 180);
  int servoY2_angle = map(ay, -17000, 17000, 180, 0);

  // Map X-axis values to servo angles
  int servoX1_angle = map(ax, -17000, 17000, 0, 180);
  int servoX2_angle = map(ax, -17000, 17000, 180, 0);

  // Set servo positions
  sg90Y1.write(servoY1_angle);
  sg90Y2.write(servoY2_angle);
  sg90X1.write(servoX1_angle);
  sg90X2.write(servoX2_angle);

  delay(200);
}
