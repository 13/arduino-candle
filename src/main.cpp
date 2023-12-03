#include <Arduino.h>
#include <Flame.h>
#include <LowPower.h>

#define DEBUG
#define SLEEP

#if defined(__AVR_ATtiny85__)
#define ledPin1 0
#define ldrPin1 2 //A1
#else
#define ledPin1 10
#define ldrPin1 A0
#endif

Flame flame1;

int ldrThreshold = 100;
int ldrValue = 0;

void deepSleepM(int minutes)
{
#ifdef DEBUG
  Serial.print(F("> SleepDeepM: "));
  Serial.print(minutes);
  Serial.println(F("m"));
  delay(1000);
#endif
  delay(100);
  int seconds = minutes * 60;
  int sleepCycles = seconds / 8;
  for (int i = 0; i < sleepCycles; ++i)
  {
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  }
}

void setup()
{
#ifdef DEBUG
  Serial.begin(9600);
  delay(3000);
  Serial.println(F("> "));
  Serial.println(F("> Booting..."));
#endif
  pinMode(ldrPin1, INPUT);
  flame1.setup(ledPin1, 50, 100);
}

void loop()
{
  ldrValue = analogRead(ldrPin1);
#ifdef DEBUG
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
#ifdef SLEEP
    deepSleepM(15);
#endif
  }
}
