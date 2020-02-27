#include "adc1registers.hpp" //for ADC1
#include "adccommonregisters.hpp" //for ADCCommon

enum class Resolution
{
  Bits12,
  Bits10,
  Bits8,
  Bits6
};

struct IHardwareADC
{
 virtual void On() = 0 ;
 virtual void Off() = 0 ;
 virtual void Start() = 0 ;
 virtual bool IsReady() = 0 ;
 virtual uint32_t Get() = 0 ;
 virtual void TSEnable() = 0 ;
 virtual void Config(Resolution resolution) = 0;
 virtual void SCMode() = 0;
} ;

template <class ADCModule>
class HardwareADC : public IHardwareADC
{
public:
 void On() override
 {
   ADCModule::CR2::ADON::Enable::Set();
 }
 void Off() override
 {
   ADCModule::CR2::ADON::Disable::Set();
 }
 void Start() override
 {
   ADCModule::CR2::SWSTART::On::Set();
 }
 bool IsReady() override
 {
   return ADCModule::SR::EOC::ConversionComplete::IsSet();
 }
 uint32_t Get() override
 {
   return ADCModule::DR::Get();
 }
 void TSEnable() override
 {
   ADC_Common::CCR::TSVREFE::Enable::Set();
 }
 void Config(Resolution resolution) override
 {
   switch (resolution)
   {
   case Resolution::Bits12:
   ADCModule:: CR1:: RES:: Bits12::Set();
   break;
   
   case Resolution::Bits10:
   ADCModule:: CR1:: RES:: Bits10:: Set();
   break;
   
   case Resolution::Bits8:
   ADCModule:: CR1:: RES:: Bits8:: Set();
   break;
   
   case Resolution::Bits6:
   ADCModule:: CR1:: RES:: Bits6:: Set();
   break;
   
   default:
   ADCModule:: CR1:: RES:: Bits12::Set();
   break;    
   }
 }
 void SCMode() override
 {
  ADCModule::CR2::CONT::SingleConversion::Set();
  ADCModule::CR2::EOCS::SingleConversion::Set(); 
 }
}
;