#ifndef MY23LED_TASK_HPP
#define MY23LED_TASK_HPP

#include "thread.hpp"
#include "ledsdriver.hpp"

class Led23Task : public OsWrapper::Thread
{
public:
  Led23Task() = default;
  void Execute() override
  {
    for(;;)
    {
      auto& led2 = ledsdriver.GetLed(LedNum::led2);
      auto& led3 = ledsdriver.GetLed(LedNum::led3);
      led2.Toggle();
      led3.Toggle();
      Sleep(100);
    } 
  }
  inline static std::array<OsWrapper::tStack, 256> Stack;

private:
  LedsDriver ledsdriver;
}
;

#endif