#include "rccregisters.hpp" //for RTC
#include "gpioaregisters.hpp" //for gpioa
#include "gpiocregisters.hpp" //for gpioc
#include "tim2registers.hpp" //for tim2

extern "C"

{
  int __low_level_init(void)
  {
    RCC::CR::HSION::Enable::Set ();
    while ( ! RCC::CR::HSIRDY::Enable::IsSet () )
    {
    };
    
      RCC::CFGR::SW::Hsi::Set();
      while ( ! RCC::CFGR::SWS::Hsi::IsSet () )
    {
    };
    RCC::AHB1ENR::GPIOAEN::Enable::Set();
    GPIOA::MODER::MODER5::Output::Set();
    
    RCC::AHB1ENR::GPIOCEN::Enable::Set(); // 
    GPIOC::MODER::MODER5::Output::Set();
    GPIOC::MODER::MODER8::Output::Set();
    GPIOC::MODER::MODER9::Output::Set();
    GPIOC::MODER::MODER13::Input::Set();
    
    RCC::APB1ENR::TIM2EN::Enable::Set();
    TIM2::CR1::URS::Overflow::Set();
    return 0;
  }
}

void delay(std::uint32_t delay)
{
  TIM2::ARR::Write(16'000 *delay);
  TIM2::SR::UIF::NoUpdate::Set();
  TIM2::CNT::Write(0);
  TIM2::CR1::CEN::Enable::Set();
  while(TIM2::SR::UIF::NoUpdate::IsSet())
                   {
                   }
                
                 
};

 struct Button 
 {
   static bool IsPressed()
   {
     bool result = false;
     if (GPIOC::IDR::IDR13::Low::IsSet() )
     {
       while (GPIOC::IDR::IDR13::Low::IsSet() )
       {
         result = true;
       };
     }
     return result;
   }
 };

template <typename Port, std::uint32_t pinNum>
struct Led
{
  static void Toggle()
  {
    Port::ODR::Toggle(1<<pinNum);
  }
};

using Led1 = Led<GPIOC,5>;
using Led2 = Led<GPIOC,8>;
using Led3 = Led<GPIOC,9>;
using Led4 = Led<GPIOA,5>;


int main()
{
  for (; ;)
  {
      Led1::Toggle ();
      delay(1000); //pol gorit pol net
      Led2::Toggle ();  

    if (Button::IsPressed())
    {
      Led1::Toggle ();
      Led2::Toggle ();
      Led3::Toggle ();
      Led4::Toggle ();
    }
  } 
  return 0;
}
