#include "gpioaregisters.hpp"
#include "gpiocregisters.hpp" //
#include "rccregisters.hpp"

int main()
{
  RCC::AHB1ENR::GPIOAEN::Enable::Set() ;
  GPIOA::MODER::MODER5::Output::Set() ;
  
  RCC::AHB1ENR::GPIOCEN::Value1::Set() ; //Value1=Enable
  GPIOC::MODER::MODER9::Value1::Set() ; //Value1=Output;
  GPIOC::MODER::MODER8::Value1::Set() ;
  GPIOC::MODER::MODER5::Value1::Set() ;

  
  GPIOA::ODR::ODR5::Enable::Set() ;
  GPIOC::ODR::ODR9::Value1::Set() ;
  GPIOC::ODR::ODR8::Value1::Set() ;
  GPIOC::ODR::ODR5::Value1::Set() ;
  
  GPIOA::ODR::ODR5::Disable::Set() ; 
  GPIOC::ODR::ODR9::Value0::Set() ; //Value1=Disable
  GPIOC::ODR::ODR8::Value0::Set() ;
  GPIOC::ODR::ODR5::Value0::Set() ;
  return 0;
}
