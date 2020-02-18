#include "adc1registers.hpp" //for ADC1
#include "adccommonregisters.hpp" //for ADCCommon
#include "gpioaregisters.hpp"  //for Gpioa
#include "gpiocregisters.hpp"  //for Gpioc
#include "rccregisters.hpp"    //for RCC
#include <iostream>

using namespace std;
      
class ADC
{
  
public:
  void Start() 
  {
  RCC::CR::HSEON::On::Set();
  while(!RCC::CR::HSERDY::Ready::IsSet())
  {}; 
  RCC::CFGR::SW::Hse::Set();
  while (!RCC::CFGR::SWS::Hse::IsSet())
  {};
  RCC::APB2ENR::ADC1EN::Enable::Set();
  ADC1::CR2::ADON::Enable::Set();
  }
  void TSEnable() 
  {
   ADC_Common::CCR::TSVREFE::Enable::Set();
   ADC1::CR1::RES::Bits12::Set();
  ADC1::CR2::CONT::SingleConversion::Set();
  ADC1::CR2::EOCS::SingleConversion::Set();   
  }
  void VSEnable() 
  {
  RCC::AHB1ENR::GPIOAEN::Enable::Set();
  GPIOA::MODER::MODER0::Analog::Set();
  ADC1::CR1::RES::Bits12::Set();
  ADC1::CR2::CONT::SingleConversion::Set();
  ADC1::CR2::EOCS::SingleConversion::Set();   
  }
}
;
                 
class TemperatureSensor
{
public:
  void Code() 
  {
      ADC1::SQR1::L::Conversions1::Set();
  ADC1::SQR3::SQ2::Channel18::Set();
  ADC1::SMPR1::SMP18::Cycles84::Set();
    uint32_t ADC_Code = 0U ;
    ADC1::CR2::SWSTART::On::Set();
    while(!ADC1::SR::EOC::ConversionComplete::IsSet())
    {};
    ADC_Code =  ADC1::DR::Get(); //Get data from ADC;
    cout << "\nTemperature data from ADC: " << ADC_Code << endl ; 
  }
  void Temperature() 
  {
  ADC1::SQR1::L::Conversions2::Set();
  ADC1::SQR3::SQ1::Channel17::Set();
  ADC1::SQR3::SQ2::Channel18::Set();
  ADC1::SMPR1::SMP17::Cycles84::Set();
  ADC1::SMPR1::SMP18::Cycles84::Set();
  ADC1::CR1::SCAN::Enable::Set();
   constexpr size_t tsCal1Addr = 0x1FFF7A2C;
   constexpr size_t tsCal2Addr =  0x1FFF7A2E; 
   constexpr size_t VddaCalAddr =  0x1FFF7A2A; 
   volatile uint16_t *tsCal1Pointer = reinterpret_cast<volatile uint16_t*>(tsCal1Addr) ;
   volatile uint16_t *tsCal2Pointer = reinterpret_cast<volatile uint16_t*>(tsCal2Addr) ;
   uint16_t tsCal132 = (*tsCal1Pointer);
   uint16_t tsCal232 = (*tsCal2Pointer);
   float tsCal1 = tsCal132; 
   float tsCal2 = tsCal232;
   volatile uint16_t *VddaCalPointer = reinterpret_cast<volatile uint16_t*>(VddaCalAddr) ;
   uint16_t VddaCal32 = (*VddaCalPointer);
   float VddaCal = VddaCal32;
   uint32_t ADC_Code = 0U ; //for getting reference voltage data from ADC
   uint32_t Vdda = 0U ; //for getting reference voltage data from ADC
   float temperature = 0.0F ;
    float DEGREE_30 = 30.0F;
    ADC1::CR2::SWSTART::On::Set();
    while(!ADC1::SR::EOC::ConversionComplete::IsSet())
    {};
    Vdda =  ADC1::DR::Get(); 
    while(!ADC1::SR::EOC::ConversionComplete::IsSet())
    {};
    ADC_Code =  ADC1::DR::Get();
    temperature = ADC_Code * (110-30)*VddaCal/(Vdda*(tsCal2-tsCal1)) + DEGREE_30 - (110-30)*tsCal1/(tsCal2-tsCal1) ; //Convert ADC counts to temperature
    cout << "\nTemperature: " << temperature << endl ; 
  }
}
;

class VoltageSensor
{
public:
  void Code() 
  {
  ADC1::SQR1::L::Conversions1::Set();
  ADC1::SQR3::SQ1::Channel0::Set();
  ADC1::SMPR2::SMP0::Cycles84::Set();
  std::uint32_t data = 0U ;
  ADC1::CR2::SWSTART::On::Set();
  while(!ADC1::SR::EOC::ConversionComplete::IsSet())
 {};
  data =   ADC1::DR::Get(); //Get data from ADC;
  cout << "\nVoltage data from ADC " << data << endl ;
  }
  void Voltage() 
  {
  ADC1::SQR1::L::Conversions1::Set();
  ADC1::SQR3::SQ1::Channel0::Set();
  ADC1::SMPR2::SMP0::Cycles84::Set();
  constexpr float B2 = 0 ;//25.0F - 0.76F/0.0025F ;// see datacheet (page 226) and calculate B coeficient here ;
  constexpr float K2 = 3.3F/4096 ;//3.3F/(4096.0F*0.0025F); // see datcheet  (page 226) and calculate K coeficient here ; 
  std::uint32_t data = 0U ;
  float voltage = 0.0F ;
  ADC1::CR2::SWSTART::On::Set();
  while(!ADC1::SR::EOC::ConversionComplete::IsSet())
 {};
  data =   ADC1::DR::Get(); //Get data from ADC;
  voltage = data * K2 + B2 ; //Convert ADC counts to temperature      
  cout << "\nVoltage: " << voltage << endl ; 
  }
}
;

int main()
{
  ADC ADC1;
  ADC1.Start();
  ADC1.TSEnable();
  ADC1.VSEnable();
  TemperatureSensor Sensor1;
  Sensor1.Temperature();
  Sensor1.Code();
  VoltageSensor Sensor2;
  Sensor2.Code();
  Sensor2.Voltage();
  return 0;
}
