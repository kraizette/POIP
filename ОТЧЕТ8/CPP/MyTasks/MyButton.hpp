#ifndef MYBUTTON_TASK_HPP
#define MYBUTTON_TASK_HPP

#include "thread.hpp"
#include "ledsdriver.hpp"
#include "userbutton.hpp"

class MyButtonTask : public OsWrapper::Thread
{
public:
  MyButtonTask() = default;
  void Execute() override
  {
    for(;;)
    {
      if (UserButton::GetInstance().IsPressed())
    {
      auto& led4 = ledsdriver.GetLed(LedNum::led4);
      led4.Toggle();
      Sleep(300);
    }
    } 
  }
  inline static std::array<OsWrapper::tStack, 256> Stack;

private:
  LedsDriver ledsdriver;
 // UserButton userbutton;
}
;

#endif