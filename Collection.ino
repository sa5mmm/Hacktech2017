#include <MQ135.h>
#include <CS_MQ7.h>
#include <DHT.h>
#include <DHT_U.h>
#include <Adafruit_Sensor.h>

#define DHTPIN 2
#define DHTTYPE DHT11

const int ms=5000;
#define MQ135PIN 3

CS_MQ7 MQ7(4,4);
MQ135 gasSensor = MQ135(MQ135PIN);
const int mq135LED = 2;
const int mq7LED = 3;
float temp;
float hum;
DHT dht(DHTPIN, DHTTYPE);
void blink(int pin);
void setup()
{
  Serial.begin(115200);
  pinMode(mq135LED, OUTPUT);//LED lights
  pinMode(mq7LED, OUTPUT);//LED-lights
  dht.begin();
  int coSensorOutput = 1;
}
void loop()
{
  delay(30000);

  hum = dht.readHumidity();
  temp = dht.readTemperature();
  float heatindexC = dht.computeHeatIndex(temp, hum, false);
  
  int mq_135 = analogRead(A0);
  float ppm135 = gasSensor.getCorrectedPPM(temp, hum);
  blink(mq135LED);

  int CO2 = analogRead(A1);
  blink(mq7LED);
  Serial.print("B ");
  delay(ms);
  //Serial.print("CO2 ppm: ");
  Serial.print(ppm135);
  Serial.print(" ");
  delay(ms);
  //Serial.print("MQ7: ");
  Serial.print(CO2);
    Serial.print(" ");
  delay(ms);
  //Serial.print("Humdity: ");
  Serial.print(hum);
    Serial.print(" ");
  delay(ms);
  //Serial.print("Temperature in C: ");
  Serial.print(temp);
    Serial.print(" ");
  delay(ms);
 // Serial.print("Heat index in C: ");
  Serial.println(heatindex);
  delay(ms);
}

void blink(int pin)
{
  digitalWrite(pin, HIGH);
  delay(500);
  digitalWrite(pin, LOW);
}

//https://github.com/adafruit/DHT-sensor-library
//https://github.com/mastero101/MQ135/blob/master/MQ135.ino
//https://github.com/GeorgK/MQ135
//https://github.com/adafruit/Adafruit_Sensor
//https://github.com/jmsaavedra/Citizen-Sensor/tree/master/sensors/MQ7%20Arduino%20Library
