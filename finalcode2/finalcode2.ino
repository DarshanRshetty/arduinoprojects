#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

// Define pin numbers
const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
const int soilMoisturePin = A0; 
const int relayPin = 9;        
const int threshold = 1010; 

// Create LCD and GSM objects
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
SoftwareSerial gsmSerial(10, 11); // RX, TX

// Variable to store soil moisture value
int soilMoistureValue = 0;      

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  gsmSerial.begin(9600); // Setting the baud rate of GSM Module
  delay(1000);

  // Initialize the LCD
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("System is on");
  delay(1500);

  // Initialize pins
  pinMode(soilMoisturePin, INPUT);  
  pinMode(relayPin, OUTPUT);        
  digitalWrite(relayPin, LOW);     

  Serial.println("Preparing to send SMS");
}

void loop() {
  // Read the soil moisture value
  soilMoistureValue = analogRead(soilMoisturePin);
  Serial.print("Soil Moisture: ");
  Serial.println(soilMoistureValue);  
  
  // Map soil moisture value to a "temperature-like" scale (0 to 40°C)
  int moistureTemperature = mapMoistureToTemperature(soilMoistureValue);

  // Display the soil moisture temperature on the LCD
  lcd.setCursor(0, 0); 
  lcd.print("Moisture: ");
  lcd.print(moistureTemperature);
  lcd.print("C   "); // To clear any residual characters

  // Control the relay based on the soil moisture value
  if (soilMoistureValue < threshold) {
    digitalWrite(relayPin, HIGH); 
    lcd.setCursor(12, 1); 
    lcd.print(" ON ");
  } else {
    digitalWrite(relayPin, LOW);  
    lcd.setCursor(12, 1);  
    lcd.print(" OFF");
    Serial.println("Motor off");
    SendMessage1();
  }
  
  delay(1000); 
}

// Function to map soil moisture value to a "temperature-like" scale (0 to 40°C)
int mapMoistureToTemperature(int moistureValue) {
  // Assuming moisture sensor value range is 0 to 1023
  // Map 0-1023 to 0-40 (degrees Celsius)
  return map(moistureValue, 0, 1023, 0, 40);
}

void SendMessage1() {
  Serial.println("Setting the GSM in text mode");
  gsmSerial.println("AT+CMGF=1\r");
  delay(2000);
  Serial.println("Sending SMS to the desired phone number!");
  gsmSerial.println("AT+CMGS=\"+916360467963\"\r");
  delay(2000);
  gsmSerial.println("Motor off");    // SMS Text
  delay(200);
  gsmSerial.println((char)26);               // ASCII code of CTRL+Z
  delay(2000);
}
