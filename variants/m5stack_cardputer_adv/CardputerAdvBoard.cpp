#include <Arduino.h>
#include "CardputerAdvBoard.h"

void CardputerAdvBoard::begin() {
  ESP32Board::begin();

  // Deselect onboard MicroSD card (shares SPI bus SCK=40, MISO=39, MOSI=14 with Cap LoRa-1262)
  pinMode(PIN_SDCARD_CS, OUTPUT);
  digitalWrite(PIN_SDCARD_CS, HIGH);

  // Configure user button (BtnG0)
  pinMode(PIN_USER_BTN, INPUT_PULLUP);

  // Configure LoRa MISO pull-up
  pinMode(P_LORA_MISO, INPUT_PULLUP);

  esp_reset_reason_t reason = esp_reset_reason();
  if (reason == ESP_RST_DEEPSLEEP) {
    long wakeup_source = esp_sleep_get_ext1_wakeup_status();
    if (wakeup_source & (1ULL << P_LORA_DIO_1)) {
      startup_reason = BD_STARTUP_RX_PACKET;
    }

    rtc_gpio_hold_dis((gpio_num_t)P_LORA_NSS);
    rtc_gpio_deinit((gpio_num_t)P_LORA_DIO_1);
  }
}
