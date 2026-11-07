#include <RPLidar.h>
#include <SoftwareSerial.h>

#define RPLIDAR_MOTOR 3

#define LIDAR_RX 8
#define LIDAR_TX 9

#define DETECTION_DISTANCE 500

SoftwareSerial lidarSerial(LIDAR_RX, LIDAR_TX);

RPLidar lidar(&lidarSerial);

void setup() {
  // USB serial communication
  Serial.begin(115200);

  // LIDAR serial communication
  lidarSerial.begin(115200);

  // Motor control
  pinMode(RPLIDAR_MOTOR, OUTPUT);

  // Start motor
  analogWrite(RPLIDAR_MOTOR, 180);

  delay(2000);

  Serial.println("================================");
  Serial.println("       RPLIDAR STARTING");
  Serial.println("================================");

  // Start scanning
  lidar.startScan();

  delay(1000);

  Serial.println("LIDAR SCANNING STARTED");
  Serial.println("Angle (degrees) | Distance (mm)");
  Serial.println("--------------------------------");
}

void loop() {
  // Parse incoming LIDAR measurements.
  // Your library prints A:angle D:distance
  lidar.parseLidarData();
  delay(1000);
}