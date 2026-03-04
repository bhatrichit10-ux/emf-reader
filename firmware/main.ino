#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>
#include <Adafruit_NeoPixel.h>

#define LED_PIN 6
#define LED_COUNT 5'

Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(02020);

void void setup()
{
 Serial.begin(9600);
    if (!mag.begin())
    {
    Serial.println("Magnometer not connected");
    while (1);
    }
    strip.begin();
    strip.show(); 

}

void loop() {
  sensors_event_t event;
  mag.getEvent(&event);

  float field = sqrt(
    event.magnetic.x * event.magnetic.x +
    event.magnetic.y * event.magnetic.y +
    event.magnetic.z * event.magnetic.z
  );

  int level = map(field, 20, 100, 0, 5);
  level = constrain(level, 0, 5);

  for(int i=0;i<5;i++){
    if(i < level) strip.setPixelColor(i, strip.Color(0,255,0));
    else strip.setPixelColor(i,0);
  }

  strip.show();
}