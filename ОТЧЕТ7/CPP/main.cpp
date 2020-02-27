#include "HardwareADC.hpp" 
#include "ADC.hpp" 
#include "ADCTemperature.hpp" 
#include "ADCTemperatureMeasurement.hpp" 
#include "ADCCalibration.hpp" 
#include "adc1registers.hpp" //for ADC1
#include "adccommonregisters.hpp" //for ADCCommon
#include "rccregisters.hpp"    //for RCC
#include "tim2registers.hpp"   //for TIM2
#include <iostream>

extern "C"
{
int __low_level_init(void)
{
  
  //Switch on external 8 MHz oscillator
  RCC::CR::HSEON::On::Set();
  while(!RCC::CR::HSERDY::Ready::IsSet())
  {};
  //Switch system clock on external oscillator
  RCC::CFGR::SW::Hse::Set();
  while (!RCC::CFGR::SWS::Hse::IsSet())
  {};
  //Switch on clock on ADC1
  RCC::APB2ENR::ADC1EN::Enable::Set();

  // Set laentgh of conversion sequence
  ADC1::SQR1::L::Conversions1::Set(); //temperature & voltage
  // Set 84 cycles sample rate for channels
  ADC1::SMPR1::SMP18::Cycles3::Set();
  
  return 1;
}
}

int main()
{
  HardwareADC<ADC1> hwAdc ;
  ADC adc(hwAdc);
  
  Calibration Calibration1(adc);
  float tsCal1 = Calibration1.GetCal1();
  float tsCal2 = Calibration1.GetCal2();
  Temperature temp(tsCal1, tsCal2);    
  Measure  Measure1(adc, temp) ;
  Measure1.Measurement() ;
};