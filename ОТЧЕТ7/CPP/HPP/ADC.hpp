#ifndef ADC_HPP
#define ADC_HPP
#include "IADC.hpp"

template <typename hwADC>
class ADC: public IADC
{  
public:
  void On()  override
  {
     hwADC::On()  ;
  }
  void Off()  override 
  {
    hwADC::Off() ;
  }
 void Start() override
 {
   hwADC::Start() ;
 }
 bool IsReady() override
 {
    return hwADC::IsReady() ;
 }
 uint32_t Get() override
 {
    return hwADC::Get() ;
 }
 void TSEnable() override
 {
   hwADC::TSEnable() ;
 }
 void SCMode () override
 {
   hwADC::SCMode();
 }
 void Config(Resolution resolution) override
 {
   hwADC::Config(resolution);
 }
 void SetChannels(const ChannelsArray &channelsList,int count) override
 {
   hwADC::SetChannels(channelsList, count) ;
 }
} ;

#endif