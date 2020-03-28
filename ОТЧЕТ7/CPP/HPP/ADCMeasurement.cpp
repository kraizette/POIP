#include "ADCMeasurement.hpp" 
#include "ADCCalibration.hpp"
#include "intrinsics.h"

Measure::Measure(IADC& adc, IVariable& temp, IVariable& volt): myADC(adc), temperature(temp), voltage(volt)
 {
  myADC.On();
  myADC.TSEnable();
  myADC.Config(Resolution::Bits12);
  myADC.SCMode();
  ChannelsArray cahnnelArray = {18,17};
  myADC.SetChannels(cahnnelArray, 2) ;
 }
 
 void Measure::MeasureAll() 
 {  __istate_t s = __get_interrupt_state();
    __disable_interrupt();
    myADC.Start();
    while(!myADC.IsReady()){};
    uint32_t tcode = myADC.Get();
    temperature.Calculate(static_cast<float>(tcode)) ;
    while(!myADC.IsReady()){};
    uint32_t vcode = myADC.Get();
    voltage.Calculate(static_cast<float>(vcode)) ;
    __set_interrupt_state(s);
 }
  float  Measure::GetTemperature()
 {
   return temperature.Get() ;
 }
 float  Measure::GetVoltage()
 {
   return voltage.Get() ;
 }