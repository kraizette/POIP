#include "HardwareADC.hpp" 
#include "ADC.hpp" 
#include "ADCTemperature.hpp" 
#include "ADCVoltage.hpp" 
#include "ADCMeasurement.hpp"  
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
  ADC1::SMPR1::SMP18::Cycles56::Set();
  ADC1::SMPR1::SMP17::Cycles56::Set();
  return 1;
}
}

int main()
{
  using  hwADC = HardwareADC<ADC1>;
  ADC<hwADC> adc;
  Calibration Calibration1(adc);
  float tsCal1 = Calibration1.GetCal1();
  float tsCal2 = Calibration1.GetCal2();
  float tsCal3 = Calibration1.GetCal3();
  float tsCal4 = 0.0F;
  Temperature temp(tsCal1, tsCal2);
  Voltage volt(tsCal3, tsCal4);
  Measure  Measure1(adc, temp, volt) ;
    for(;;)  
  {
  Measure1.MeasureAll();
  std::cout << "\n" << Measure1.GetVoltage() << "\n" << Measure1.GetTemperature() << std::endl ;
  }
};