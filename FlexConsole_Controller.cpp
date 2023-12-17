#include"FlexConsole_Controller.hpp"

FlexConsole_Controller::FlexConsole_Controller(void){
  ch = 0;
  val = 0;
  cs = 0;
  err_num = 0;
  return;
}
void FlexConsole_Controller::set_serialBT(char *device_name,const char *pin){
  SBT.begin(device_name);
  SBT.setPin(pin);
  return;
}

uint8_t FlexConsole_Controller::read_data(void){
  uint8_t err_num=0;
  if(SBT.available()){
    ch = SBT.read();
    val = SBT.read();
    cs = SBT.read();
  }
  if((ch^val) != cs){
    ch = 0xFF;
    val = 0xFF;
    cs = 0xFF;
    while(SBT.available()){
      SBT.read();
    }
    err_num = cs_err;
  }
  else{
    err_num = no_err;
  }
  return err_num;
}

void FlexConsole_Controller::write_data(uint8_t w_ch,uint8_t w_val){
  uint8_t w_cs = w_ch ^ w_val;
  SBT.write(w_ch);
  SBT.write(w_val);
  SBT.write(w_cs);
  return;
}

uint8_t FlexConsole_Controller::get_ch(void){
  return ch;
}

uint8_t FlexConsole_Controller::get_val(void){
  return val;
}
