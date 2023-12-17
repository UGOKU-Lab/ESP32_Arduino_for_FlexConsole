#pragma once
#include<Arduino.h>
#include "FlexConsole_define.h"
#include "BluetoothSerial.h"

class FlexConsole_Controller{
  public:
  FlexConsole_Controller();
  uint8_t read_data(void);
  void write_data(uint8_t,uint8_t);
  uint8_t get_ch(void);
  uint8_t get_val(void);
  void set_ch(uint8_t);
  void set_val(uint8_t);
  void set_serialBT(char *,const char *);

  private:
  BluetoothSerial SBT;
  uint8_t ch;
  uint8_t val;
  uint8_t cs;
  uint8_t err_num;
};