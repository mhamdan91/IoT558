/*
 * SmartHome
 * 
 * 
 */

#include <IRremote.h>
#include <NewTone.h>
#include <EEPROM.h>
#include <Wire.h>

#include <dht.h>
#define CDS_INPUT 0
#define DHT11_PIN 2
#define DARK 200
#define RELAY 4
#define PROBE_WATER 1
#define MOSTURE_LEVEL 800
#define ALARM 8
#define ALARM_DELAY 3000

int redPin = 9;
int greenPin = 10;

int addr = 0;
int relay;
int motor_dir1Pin = 5;
int motor_dir2Pin = 6;
int motor_speedPin = 7;

float sinVal;
int toneVal;

dht DHT;
IRsend irsend;
//
//int  relay_status = 0;
//
void setup() 
{
  Serial.begin(9600);
  pinMode(RELAY, OUTPUT);
  relay = EEPROM.read(addr);
  if (relay)
      digitalWrite(RELAY,HIGH);
    else if (!relay)
      digitalWrite(RELAY,LOW);

  pinMode(motor_dir1Pin, OUTPUT);
  pinMode(motor_dir2Pin, OUTPUT);
  pinMode(motor_speedPin, OUTPUT);

  pinMode(ALARM, OUTPUT);

  pinMode(redPin, OUTPUT);
  pinMode(greenPin,OUTPUT);

  Wire.begin();
}

void loop() 
{
  String str;

  if (ck_flood())
    alarm();

  str = Serial.readString();
  str.toLowerCase();
  if (str == "t")
    get_temperature();
  else if (str == "h")
    get_humidity();
  else if (str == "l")
    get_brightness();
  else if (str == "tv")
  {
    irsend.sendSony(0xFE50AF, 32);
    //delay(500);
  }
  else if (str == "r")
  {
    int relay_status = EEPROM.read(addr);
    relay_status = !relay_status;
    EEPROM.update(addr, relay_status);
    delay(500);
    if (relay_status)
      digitalWrite(RELAY,HIGH);
    else if (!relay_status)
      digitalWrite(RELAY,LOW);
  }
  else if (str == "w")
    send_flood();

  transmit_data();
  //delay(1000);
}

void  transmit_data()
{
  int temperature;
  
  DHT.read11(DHT11_PIN);
  temperature = DHT.temperature;
  Wire.beginTransmission(8);
  Wire.write("Temperature: ");
  Wire.write(temperature);
  Wire.endTransmission();
}
void  motor_on()
{
  analogWrite(motor_speedPin, 255);
  digitalWrite(motor_dir1Pin, LOW);
  digitalWrite(motor_dir2Pin, HIGH);
}

void  motor_off()
{
  analogWrite(motor_speedPin, 0);
  digitalWrite(motor_dir1Pin, LOW);
  digitalWrite(motor_dir2Pin, HIGH);
}

int   ck_flood()
{
  int moisture = analogRead(PROBE_WATER);
  if (moisture < MOSTURE_LEVEL)
  {
    //Serial.println(moisture);
    return (1);
  }
  else
  {
    //Serial.println(moisture);
    return (0);
  }
}

void   send_flood()
{
  int moisture = analogRead(PROBE_WATER);
  if (moisture < MOSTURE_LEVEL)
     Serial.println(1);
  else
     Serial.println(0);
}

void  get_brightness()
{
  int light = analogRead(CDS_INPUT);

  if (light > DARK)
    light = 1;
  else
    light = 0;

  Serial.println(light);
}

void  get_temperature()
{
  int temperature;
  
  DHT.read11(DHT11_PIN);
  temperature = DHT.temperature;
  Serial.println(temperature);
}

void  get_humidity()
{
  int humidity;
  
  DHT.read11(DHT11_PIN);
  humidity = DHT.humidity;
  Serial.println(humidity);
}

void  led_color(int red, int green)
{
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
}

void alarm()
{
 motor_on();
 for (int x=0; x<180; x++) 
 {
    // convert degrees to radians then obtain sin value
    sinVal = (sin(x*(3.1412/180)));
    // generate a frequency from the sin value
    toneVal = 2000+(int(sinVal*1000));
    NewTone(ALARM, toneVal);
  }
  alarm_led();
  noNewTone(ALARM);
  motor_off();
}

void  alarm_led()
{
  led_color(255, 0);
  delay(100);
  led_color(0, 255);
  delay(100);
  led_color(0, 0);
  delay(100);
  led_color(255, 255);
  delay(100);
  led_color(255, 0);
  delay(100);
  led_color(0, 255);
  delay(100);;
  led_color(0, 0);
  delay(100);
  led_color(255, 255);
  delay(100);
  led_color(255, 0);
  delay(100);
  led_color(0, 255);
  delay(100);
  led_color(0, 0);
  delay(100);
  led_color(255, 255);
  delay(100);
  led_color(255, 0);
  delay(100);
  led_color(0, 255);
  delay(100);
  led_color(0, 0);
  delay(50);
  led_color(255, 255);
  delay(100);
  led_color(255, 0);
  delay(100);
  led_color(0, 255);
  delay(100);
  led_color(0, 0);
  delay(100);
  led_color(255, 255);
  delay(100);
  led_color(255, 0);
  delay(100);
  led_color(0, 255);
  delay(100);
  led_color(0, 0);
  delay(100);
  led_color(255, 255);
  delay(100);
  led_color(255, 255);
  delay(100);
  led_color(255, 0);
  delay(100);
  led_color(0, 255);
  delay(100);
  led_color(0, 0);
  delay(100);
  led_color(255, 255);
  delay(100);
  led_color(0, 0);
}
