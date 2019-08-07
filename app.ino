#include  <Wire.h>
#include  <LiquidCrystal_I2C.h>
#include "DHT.h"

#define capacitiveSoil A1
#define heater 2
#define DHTPIN 3
#define DHTTYPE DHT11

//motor
#define in1 4
#define in2 5

int kadarAir;
int persen;
float t;
int data = 0;
int data2 = 0; 

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address
DHT dht(DHTPIN, DHTTYPE);

void setup() 
{
  Serial.begin(38400);
  dht.begin();
  pinMode(heater, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
 
  lcd.begin(16,2);  
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Pengering Gabah");
}

void loop() 
{
  kadarAir = analogRead(capacitiveSoil);
 
  t = dht.readTemperature();
  lcd.setCursor(0, 1);
  //lcd.print(suhu);
  lcd.print(t);

  persen = -0.04*kadarAir+40;
  lcd.setCursor(11, 1);
  lcd.print(persen);
  lcd.print("%");
  delay(1000);

  if (persen <=14)
  {
    digitalWrite(heater, LOW);
    lcd.setCursor(15,0);
    lcd.print("0");
  }else
  {
    digitalWrite(heater, HIGH);
    lcd.setCursor(15,0);
    lcd.print("1");   
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
			}else if (data == '0') 
			{
    		kipasMati();
				data2 = '0';
				data = 0;
			}
  }
	Serial.println(data);
	
}

void kipasNyala(){
	digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
}

void kipasMati(){
	digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
}
