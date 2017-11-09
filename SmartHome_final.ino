/*
 * SmartHome
 * 
 * 
 */
//#include <NewTone.h>
//#include <IRremote.h>
#include <EEPROM.h>
#include <Wire.h>
#include <ArduinoJson.h>

#include <dht.h>
#define CDS_INPUT 0
#define DHT11_PIN 8
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
//IRsend irsend;

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

  str = Serial.readString();
  str.toLowerCase();
  if (str == "tv")
  {
  //  IRsend irsend;
  //  irsend.sendSony(0xFE50AF, 32);
  }
  /*else if (str == "r")
  {
    int relay_status = EEPROM.read(addr);
    relay_status = !relay_status;
    EEPROM.update(addr, relay_status);
    delay(500);
    if (relay_status)
      digitalWrite(RELAY,HIGH);
    else if (!relay_status)
      digitalWrite(RELAY,LOW);
  }*/
  //else if (str == "w")
   // send_flood();

   
  else if (str == "thl")
  {
   // delay(1000);
    //str="ok";
    send_data();
  }
   if (ck_flood())
    alarm();
   else
    motor_off();
  transmit_data();
}

void  send_data()
{
   StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["temp"] = get_temperature();
  root["humidity"] = get_humidity();
  root["lumina"] = get_brightness();
  root["alarm"] =  ck_flood();
  root.printTo(Serial);
  Serial.println();
 // root[""]="";
//  root.printTo(Serial);
 // jsonBuffer.clear();
}

void  transmit_data()
{
  char buff1[3];
  char buff2[3];
  String temp_str = "Temp: ";
  String hum_str = "Humidity: ";
  String c = " C  |  ";
  String p = " %";
  int temperature = get_temperature();;
  int humidity = get_humidity();
  itoa(temperature, buff1, 10);
  itoa(humidity, buff2, 10);
  
  Wire.beginTransmission(8);
  Wire.write(temp_str.c_str());
  Wire.write(buff1);
  Wire.write(c.c_str());
  Wire.write(hum_str.c_str());
  Wire.write(buff2);
  Wire.write(p.c_str());
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
    return (1);
  else
    return (0);
}

void   send_flood()
{
  int moisture = analogRead(PROBE_WATER);
  if (moisture < MOSTURE_LEVEL)
     Serial.println(1);
  else
     Serial.println(0);
}

int  get_brightness()
{
  int light = analogRead(CDS_INPUT);

  if (light > DARK)
    return (1);
    //light = 1;
  else
    return(0);
    //light = 0;

  Serial.println(light);
}

int get_temperature()
{
  int temperature;
  
  DHT.read11(DHT11_PIN);
  temperature = DHT.temperature;
  return(temperature);
}

int  get_humidity()
{
  int humidity;
  
  DHT.read11(DHT11_PIN);
  humidity = DHT.humidity;
  return(humidity);
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
   // NewTone(ALARM, toneVal);
  }
  alarm_led();
//  noNewTone(ALARM);
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
