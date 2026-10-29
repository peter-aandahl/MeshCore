#pragma once

#include <Wire.h>
#include <Arduino.h>
#include <helpers/ESP32Board.h>

#ifndef PIN_SDCARD_CS
  #define PIN_SDCARD_CS 12
#endif

class CardputerAdvBoard : public ESP32Board {
public:
  void begin();

  const char* getManufacturerName() const override {
    return "M5Stack Cardputer-Adv";
  }
};
