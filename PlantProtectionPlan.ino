#include <LiquidCrystal.h>
#include <DHT.h>

#define LIGHTPIN A5 // 光敏电阻
#define DHT11PIN 7  // DHT 11 温湿度传感器
#define SoilPIN A4  // 土壤湿度传感器

const int RS = 13, E = 11, D7 = 2, D6 = 3, D5 = 4, D4 = 5;
LiquidCrystal lcd(RS, E, D4, D5, D6, D7);
DHT dht;
int light;  // 光照
float temp; // 温度
float humi; // 湿度
float soil; // 土壤湿度

void setup()
{
  lcd.begin(16, 2);
  dht.setup(DHT11PIN);
}

void say_hello()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Hi,JuneBoa!");
  lcd.setCursor(0, 1);
  update_sensor();
  if (light > 1000)
  {
    // 勿扰 ～～～
    analogWrite(9, 0);
  }
  else
  {
    analogWrite(9, 100);
  }
}

void update_sensor()
{
  temp = dht.getTemperature();
  humi = dht.getHumidity();
  light = analogRead(LIGHTPIN);
  soil = analogRead(SoilPIN) / 8.0; //  - 纯水：800
}

void loop()
{
  delay(dht.getMinimumSamplingPeriod());

  say_hello();
  lcd.print("temp: ");
  lcd.print(temp);
  lcd.print(" C ");
  delay(1300);

  say_hello();
  lcd.print("humi: ");
  lcd.print(humi);
  lcd.print(" %rh ");
  delay(1300);

  say_hello();
  lcd.print("soil: ");
  lcd.print(soil);
  lcd.print(" % ");
  delay(1300);

  say_hello();
  lcd.print("light: ");
  lcd.print(light);
  delay(1300);
}
