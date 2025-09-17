#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

// LED pins on Nano
const int redLED = 6;
const int greenLED = 5;
const int yellowLED = 7;

void setup() {
  Serial.begin(115200);
  Wire.begin();  // SDA=A4, SCL=A5 on Nano

  mpu.initialize();

  // Configure LED pins as outputs
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);

  if (mpu.testConnection()) {
    Serial.println("MPU6050 connection successful");
  } else {
    Serial.println("MPU6050 connection failed");
  }
}

void loop() {
  int16_t ax, ay, az, gx, gy, gz;
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  Serial.print("Accel -> X: "); Serial.print(ax);
  Serial.print(" | Y: "); Serial.print(ay);
  Serial.print(" | Z: "); Serial.print(az);

  Serial.print(" || Gyro -> X: "); Serial.print(gx);
  Serial.print(" | Y: "); Serial.print(gy);
  Serial.print(" | Z: "); Serial.print(gz);
  Serial.println();

  // Reset LEDs
  digitalWrite(redLED, LOW);
  digitalWrite(greenLED, LOW);
  digitalWrite(yellowLED, LOW);

  // LED conditions based on accelerometer
  if (ax < -5000) {
    digitalWrite(redLED, HIGH);
  } else if (ax > 5000) {
    digitalWrite(greenLED, HIGH);
  }

  if (ay > 5000 || ay < -5000) {
    digitalWrite(yellowLED, HIGH);
  }

  delay(500);
}

