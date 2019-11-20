#include "gpioaregisters.hpp"
#include "gpiocregisters.hpp" //
#include "rccregisters.hpp"

extern "C"
{
  int __low_level_init(void)
  {
    RCC::CR::HSEON::On::Set();
    while ( !RCC::CR::HSERDY::Enable::IsSet( ) )
     {
     };
    
    RCC::CFGR::SW::Hse::Set();
    while ( !RCC::CFGR::SWS::Hse::IsSet( ) )
    {  
    };
    
    RCC::CFGR::HPRE::
    
    RCC::APB1ENR::TIM2EN::Enable::Set() ;
    TIM2::CR1::URS::OverFlow::Set();
    return 0;
  }
}

void Delay (std::uint32_t delay)

{
  TIM2::ARR::Write(16'000 * delay );
  TIM2::SR::UIF::NoUpdate::Set();
  TIM2::CNT::Write(0);
  TIM2::CR1::CEN::Enable::Set();
  while (TIM2::SR::UIF::NoUpdate::IsSet() )
  {
    
  }
  TIM2::CR1::CEN::Disable::Set();
}


using namespace std;
void delay(uint32_t delay)
 {
   for (int i=0; i<delay; i++)
   {
   }
 }

int main() {
  RCC::AHB1ENR::GPIOCEN::Enable::Set() ;
  for(;;) {
    GPIOC::MODER::MODER5::Output::Set();
    GPIOC::MODER::MODER8::Output::Set();
    GPIOC::MODER::MODER9::Output::Set();
    GPIOC::ODR::ODR5::High::Set();
    GPIOC::ODR::ODR8::High::Set();
    GPIOC::ODR::ODR9::High::Set();
    auto ptr = reinterpret_cast<volatile uint32_t *>(0x40020800) ;
    auto value = *ptr ;
    delay (1'000'000);
    GPIOC::ODR::ODR5::Low::Set();
    GPIOC::ODR::ODR8::Low::Set();
    GPIOC::ODR::ODR9::Low::Set();
  }
  return 0 ;
}