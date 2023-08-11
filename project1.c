#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int ledPin = 13;
int buzzerPin = 10;
int xPin = A0;
int yPin = A1;
int zPin = A2;
int xCalibrated = 0;
int yCalibrated = 0;
int zCalibrated = 0;
int xValue = 0;
int yValue = 0;
int zValue = 0;
float xg = 0;
float yg = 0;
float zg = 0;
float threshold = 0.09;
void setup() {pinMode(ledPin, OUTPUT);
pinMode(buzzerPin, OUTPUT);
lcd.begin(16, 2);
lcd.setCursor(0,0);
lcd.print("Earthquake Detect");
lcd.setCursor(0,1);
lcd.print("Calibrating...");
delay(2000);
lcd.clear();
xCalibrated = analogRead(xPin);
yCalibrated = analogRead(yPin);
zCalibrated = analogRead(zPin);
Serial.begin(9600);
}
void loop() {
xValue = analogRead(xPin) - xCalibrated;
yValue = analogRead(yPin) - yCalibrated;
zValue = analogRead(zPin) - zCalibrated;
xg = xValue / 330.0;
yg = yValue / 330.0;
zg = zValue / 330.0;
lcd.clear();
lcd.setCursor(0,0);
lcd.print("X:");
lcd.print(xg, 2);
lcd.setCursor(8,0);
lcd.print("Y:");
lcd.print(yg, 2);
lcd.setCursor(0,1);
lcd.print("Z:");
lcd.print(zg, 2);
Serial.print("X:");
Serial.print(xg, 2);
Serial.print(" Y:");
Serial.print(yg, 2);
Serial.print(" Z:");
Serial.print(zg, 2);
if (abs(xg) > threshold || abs(yg) > threshold || abs(zg) > threshold) {
digitalWrite(ledPin, HIGH);
tone(buzzerPin, 1000);lcd.setCursor(0,1);
lcd.print("Earthquake Detected");
Serial.println(" Earthquake Detected");
} else {
digitalWrite(ledPin, LOW);
noTone(buzzerPin);
Serial.println();
}
delay(50);