#include <LiquidCrystal.h>

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

int light_sensor_pin = A0;
int button_pin = 2;
LiquidCrystal lcd(8, 7, 6, 5, 4, 3);
int green_led_pin = 9;
int yellow_led_pin = 10;
int blue_led_pin = 11;
int red_led_pin = 12;
int moisture = 0;
int comfort_level = 500;
int button_state = 0;
int lcd_display_mode = 0;



void setup()
{
  pinMode(A0, OUTPUT);
  pinMode(A1, INPUT);
  pinMode(green_led_pin, OUTPUT);
  pinMode(yellow_led_pin, OUTPUT);
  pinMode(blue_led_pin, OUTPUT);
  pinMode(red_led_pin, OUTPUT);
  pinMode(button_pin, INPUT_PULLUP);
  sensors.begin();
  lcd.begin(16, 2);
  Serial.begin(9600);
}

void loop()
{

  button_state = digitalRead(button_pin);
  if (button_state == LOW) {
  lcd_display_mode++;
  if (lcd_display_mode > 2) {
  lcd_display_mode = 0;
  }
  delay(100);
}


  //temperature part

  sensors.requestTemperatures();
  float temperature = sensors.getTempCByIndex(0);
  Serial.print("Température : ");
  Serial.print(temperature);
  Serial.println(" °C");

  if (temperature >= 10 && temperature <= 18) {
    digitalWrite(blue_led_pin, HIGH);
    digitalWrite(red_led_pin, LOW);
  } else if (temperature >= 19 && temperature <= 21) {
    digitalWrite(blue_led_pin, LOW);
    digitalWrite(red_led_pin, HIGH);
  } else if (temperature > 22) {
    digitalWrite(blue_led_pin, LOW);
    digitalWrite(red_led_pin, LOW);
  } else {
    digitalWrite(blue_led_pin, LOW);
    digitalWrite(red_led_pin, LOW);
  }

  //moisture part

  digitalWrite(A0, HIGH);
  delay(10);
  moisture = analogRead(A1);
  digitalWrite(A0, LOW);
  Serial.println(moisture);

  if (moisture >= comfort_level) {
    digitalWrite(green_led_pin, HIGH);
    digitalWrite(yellow_led_pin, LOW);
  } else {
    digitalWrite(green_led_pin, LOW);
    digitalWrite(yellow_led_pin, HIGH);
  }

  //brightness part

  int light_level = analogRead(light_sensor_pin);
  Serial.print("Niveau de lumière : ");
  Serial.println(light_level);
  delay(1000);
 
 //display part
  lcd.clear();
  if (lcd_display_mode == 0) {
  lcd.setCursor(0, 0);
  lcd.print("Temperature:");
  lcd.setCursor(0, 1);
  lcd.print(temperature);
  lcd.print("C");
}
