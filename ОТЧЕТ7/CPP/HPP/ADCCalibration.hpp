#ifndef ADCCalibration_HPP
#define ADCCalibration_HPP
#include "ADC.hpp"

class Calibration
{
private:
  float Cal1;
  float Cal2;
  float Cal3;
  IADC& myADC;

public:
 Calibration(IADC& adc): myADC(adc)
 {
   myADC.On();
   myADC.TSEnable();
   myADC.Config(Resolution::Bits12);
 };
  
public:

  float GetCal1() 
  { 
  volatile uint16_t *tsCal1Pointer = reinterpret_cast<volatile uint16_t*>(0x1FFF7A2C) ;
  volatile uint16_t *tsCal2Pointer = reinterpret_cast<volatile uint16_t*>(0x1FFF7A2E) ;
  uint16_t tsCal132 = (*tsCal1Pointer);
  uint16_t tsCal232 = (*tsCal2Pointer);
  float tsCal1 = tsCal132; 
  float tsCal2 = tsCal232;
  volatile uint16_t *VddaCalPointer = reinterpret_cast<volatile uint16_t*>(0x1FFF7A2A) ;
  uint16_t VddaCal32 = (*VddaCalPointer);
  float VddaCal = VddaCal32;
  using MyAdc = HardwareADC<ADC1> ; 
  ChannelsArray cahnnelArray = {17};
  myADC.SetChannels(cahnnelArray,1) ;
  uint32_t Vdda = 0U ;
  myADC.Start();
  while(!myADC.IsReady()){};
  Vdda = myADC.Get(); //Get data from ADC;
  Cal1 = (110-30)*VddaCal/(Vdda*(tsCal2-tsCal1));
  return Cal1;
  }
  
  float GetCal2() 
  {
   volatile uint16_t *tsCal1Pointer = reinterpret_cast<volatile uint16_t*>(0x1FFF7A2C) ;
   volatile uint16_t *tsCal2Pointer = reinterpret_cast<volatile uint16_t*>(0x1FFF7A2E) ;
   uint16_t tsCal132 = (*tsCal1Pointer);
   uint16_t tsCal232 = (*tsCal2Pointer);
   float tsCal1 = tsCal132; 
   float tsCal2 = tsCal232;
    Cal2 =  30 - (110-30)*tsCal1/(tsCal2-tsCal1);
    return Cal2;
  }
  
    float GetCal3() 
  {
    Cal3 =  3.3F/4096;
    return Cal3;
  }
}
;
#endif