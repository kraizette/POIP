#include "gpioaregisters.hpp"
#include "gpiocregisters.hpp" //
#include "rccregisters.hpp"

int main()
{
  RCC::AHB1ENR::GPIOAEN::Enable::Set() ;
  GPIOA::MODER::MODER5::Output::Set() ;
  
  RCC::AHB1ENR::GPIOCEN::Enable::Set() ; //Value1=Enable
  GPIOC::MODER::MODER9::Output::Set() ; //Value1=Output;
  GPIOC::MODER::MODER8::Output::Set() ;
  GPIOC::MODER::MODER5::Output::Set() ;

  
  GPIOA::ODR::ODR5::Enable::Set() ;
  GPIOC::ODR::ODR9::Enable::Set() ;
  GPIOC::ODR::ODR8::Enable::Set() ;
  GPIOC::ODR::ODR5::Enable::Set() ;
  
  GPIOA::ODR::ODR5::Disable::Set() ; 
  GPIOC::ODR::ODR9::Disable::Set() ; //Value1=Disable
  GPIOC::ODR::ODR8::Disable::Set() ;
  GPIOC::ODR::ODR5::Disable::Set() ;
  return 0; 
}
