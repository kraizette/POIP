#ifndef IADC_HPP
#define IADC_HPP
#include "HardwareADC.hpp"  //for Resolution

 


struct IADC
{
 virtual void On() = 0 ;
 virtual void Off() = 0 ;
 virtual void Start() = 0 ;
 virtual bool IsReady() = 0 ;
 virtual uint32_t Get() = 0 ;
 virtual void TSEnable() = 0 ;
 virtual void SCMode() = 0 ;
 virtual void Config(Resolution resolution) = 0;
 virtual void SetChannels(const ChannelsArray &channelsList, int count) = 0;
 
} ;

#endif