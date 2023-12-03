#include <Arduino.h>
#include <Flame.h>
#include <LowPower.h>

// #define VERBOSE

#define SLPTIME 24 // seconds

#if defined(__AVR_ATtiny85__)
#define ledPin1 0
#define ldrPin1 A2
#else
#define ledPin1 10
#define ldrPin1 A0
#endif

Flame flame1;

int ldrThreshold = 100;
int ldrValue = 0;

void blinkLED(int numBlinks)
{
  for (int i = 0; i < numBlinks; ++i)
  {
    digitalWrite(ledPin1, HIGH);
    delay(200);
    digitalWrite(ledPin1, LOW);
    delay(200);
  }
  delay(500);
}

#ifdef SLPTIME
void sleepDeep(int seconds)
{
#ifdef VERBOSE
  Serial.print(F("> SleepDeep: "));
  Serial.print(seconds);
  Serial.println(F("s"));
  delay(1000);
#endif
  delay(100);
  int sleepCycles = seconds / 8;
  for (int i = 0; i < sleepCycles; ++i)
  {
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  }
}
#endif

void setup()
{
#ifdef VERBOSE
  Serial.begin(9600);
  delay(3000);
  Serial.println(F("> "));
  Serial.println(F("> Booting..."));
#endif
  blinkLED(3);
  pinMode(ldrPin1, INPUT);
  flame1.setup(ledPin1, 50, 100);
}

void loop()
{
  ldrValue = analogRead(ldrPin1);
#ifdef VERBOSE
  Serial.print(F("> LDR: "));
  Serial.println(ldrValue);
#endif
  if (ldrValue < ldrThreshold)
  {
    flame1.flicker();
  }
  else
  {
    flame1.stop();
#ifdef SLPTIME
    sleepDeep(SLPTIME);
#endif
  }
}
