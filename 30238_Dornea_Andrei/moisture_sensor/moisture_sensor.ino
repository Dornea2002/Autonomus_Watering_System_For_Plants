#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define soilWet 500     //->max value to consider when soil is wet
#define soilDry 800     //->min value to consider when soil is dry

#define sensorPower 7
#define sensorRead A0

#define turnPump 2

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // put your setup code here, to run once:

  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);

  pinMode( sensorPower, OUTPUT);

  digitalWrite( sensorPower, LOW);

  pinMode(turnPump, OUTPUT);

  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

     lcd.clear();

  int moistureStatus = readMoistureSensor();
  Serial.print("Analog Output: ");
  Serial.print(moistureStatus);

  lcd.setCursor(0, 0);
  lcd.print("Ang Output: ");

  lcd.setCursor(12, 0);
  lcd.print(moistureStatus);

  lcd.setCursor(0, 1);
  lcd.print("Status: ");
  lcd.setCursor(8, 1);

  if(moistureStatus < soilWet){
    Serial.println ("      Status: soil is too wet. Turn off the water pump!");

    lcd.print("Wet!");

    digitalWrite(turnPump, LOW);
  }
  else if(moistureStatus > soilDry){
    Serial.println ("      Status: soil is too dry. Turn on the water pump!");

    lcd.print("Dry!");

    digitalWrite(turnPump, HIGH);
  }
  else {
    Serial.println ("      Status: soil is prefect!");

    lcd.print("Perfect!");

    digitalWrite(turnPump, LOW);
  }

    delay(1000);

    Serial.println();
}

int readMoistureSensor(){
  digitalWrite(sensorPower, HIGH); //turn on the sensor
  delay(10);
  int value = analogRead(sensorRead); //read analog value from sensor
  digitalWrite(sensorPower, LOW); //turn off the sensor
  return value;
}
