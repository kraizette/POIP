#ifndef MYLED_TASK_HPP
#define MYLED_TASK_HPP

#include "thread.hpp"
#include "ledsdriver.hpp"

class MyLedTask : public OsWrapper::Thread
{
public:
  MyLedTask() = default;
  void Execute() override
  {
    for(;;)
    {
      auto& led1 = ledsdriver.GetLed(LedNum::led1);
      led1.Toggle();
      Sleep(1000);
    } 
  }
  inline static std::array<OsWrapper::tStack, 256> Stack;

private:
  LedsDriver ledsdriver;
}
;

#endif