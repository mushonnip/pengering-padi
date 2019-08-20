#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"

#define capacitiveSoil A1
#define DHTPIN 2
#define heater 3
#define motorAC 4
#define buzzer 6

#define DHTTYPE DHT11

//motor
#define in1 29
#define in2 31
#define ENA 5

int kadarAir;
int persen;
float t;
int data = 0;
int data2 = 0;
bool udah_bunyi = false;

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); // Set the LCD I2C address
DHT dht(DHTPIN, DHTTYPE);

void setup()
{
  Serial.begin(38400);
  dht.begin();
  pinMode(heater, OUTPUT);
  pinMode(motorAC, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(buzzer, OUTPUT);

  lcd.begin(16, 2);
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Pengering Gabah");
}

void loop()
{
  kadarAir = analogRead(capacitiveSoil);

  t = dht.readTemperature();
  lcd.setCursor(0, 1);
  //lcd.print(suhu);
  lcd.print(t);

  persen = -0.04 * kadarAir + 40;
  lcd.setCursor(13, 1);
  if (persen < 10)
  {
    lcd.print(" ");
  }
  else
  {
    lcd.print(persen);
  }

  lcd.print("%");
  delay(1000);

  if (persen <= 14 && udah_bunyi == false)
  {
    digitalWrite(heater, LOW);
    digitalWrite(motorAC, LOW);
    lcd.setCursor(8, 1);
    lcd.print("OFF");
    bunyi();
    udah_bunyi = true;
  }
  else if (persen > 14)
  {
    digitalWrite(heater, HIGH);
    digitalWrite(motorAC, HIGH);
    lcd.setCursor(8, 1);
    lcd.print("ON ");
    udah_bunyi = false;
  }

  if (Serial.available() > 0)
  {
    data = Serial.read();
    Serial.print(data);
    Serial.print("\n");
    if (data == '1')
    {
      data2 = '1';
      kipasNyala();
      data = 0;
    }
    else if (data == '0')
    {
      kipasMati();
      data2 = '0';
      data = 0;
    }
  }

  Serial.print(t);
  Serial.print("\t");
  Serial.println(persen);

}

void kipasNyala()
{
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
}

void kipasMati()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
}

void bunyi()
{
  tone(buzzer, 3000); // Send 1KHz sound signal...
  delay(1500);        // ...for 1 sec
  noTone(buzzer);     // Stop sound...
}