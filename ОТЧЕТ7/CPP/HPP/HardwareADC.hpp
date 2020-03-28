#ifndef HardwareADC_HPP
#define HardwareADC_HPP

#include "adc1registers.hpp" //for ADC1
#include "adccommonregisters.hpp" //for ADCCommon
#include <iostream>
#include <array> // for std::array

using ChannelsArray = std::array<std::uint32_t, 18> ;

enum class Resolution
{
  Bits12,
  Bits10,
  Bits8,
  Bits6
};

template <typename ADCModule>
class HardwareADC
{
public:
 static void On() 
 {
   ADCModule::CR2::ADON::Enable::Set();
 }
 static void Off() 
 {
   ADCModule::CR2::ADON::Disable::Set();
 }
 static void Start()
 {
   ADCModule::CR2::SWSTART::On::Set();
 }
 static bool IsReady() 
 {
   return ADCModule::SR::EOC::ConversionComplete::IsSet();
 }
 static uint32_t Get() 
 {
   return ADCModule::DR::Get();
 }
 static void TSEnable() 
 {
   ADC_Common::CCR::TSVREFE::Enable::Set();
 }
 
 static void SCMode ()
 {
  ADCModule::CR2::CONT::SingleConversion::Set();
  ADCModule::CR2::EOCS::SingleConversion::Set();  
 }
 static void Config(Resolution resolution)
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

 static void SetChannels(const ChannelsArray &channelsList, int ChannelsCount)
{ 
  
  std::size_t index = 0U ;
  constexpr size_t ChannelsInRegister = 6U ;
  typename ADCModule::SQR3::Type result3 = 0U ;
  typename ADCModule::SQR2::Type result2 = 0U ;
  typename ADCModule::SQR1::Type result1 = 0U ;
  
  if (ChannelsCount != 0)   
  {
    if (ChannelsCount > 1)
    {
      ADCModule::CR1::SCAN::Enable::Set() ;
    } 
    else
     {
     ADCModule::CR1::SCAN::Disable::Set() ;
     }
    result1 |= (ChannelsCount-1) << (4* 5U) ;
    for (auto& it: channelsList)
    {
      if (index < ChannelsInRegister)
      {
        result3 |= it << (index * 5U) ;
      } 
      else if ((index < (ChannelsInRegister * 2)) && (index >= ChannelsInRegister))
      {
        result2 |= it << ((index - ChannelsInRegister) * 5U) ;
      } 
      else if ((index < 16) && (index >= ChannelsInRegister * 2))
      {
        result1 |= it << (index - ChannelsInRegister * 2) * 5U ;
      }
      index++;
      if (index == ChannelsCount)
      {
        break ;
      }
    }
    ADCModule::SQR3::Write(result3) ;
    ADCModule::SQR2::Write(result2) ;
    ADCModule::SQR1::Write(result1) ;
  } 
  else
  {
    assert(false) ;
  }    
}
}
;

#endif