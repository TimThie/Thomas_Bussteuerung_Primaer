#ifndef APPTEMPERATURE_H
#define APPTEMPERATURE_H
#include <Arduino.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_HTU21DF.h>

#define TEMP_SENSOR_ADDRESS 0x40

void appTemperature();
void sensor_init();
double read_temperature(const int addr);
double read_humidity(const int addr);
void turnOffBacklight();
void turnOnBacklight();
void setTrunkLightState(bool);
void setMainLightState(bool);

#endif