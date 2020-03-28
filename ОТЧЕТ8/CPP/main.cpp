#include "Rtos/wrapper/rtos.hpp"
#include "Rtos/wrapper/mailbox.hpp"
#include "Rtos/wrapper/event.hpp"
#include "CMSIS/stm32f411xe.h"
#include "MyTasks/mytask.hpp"
#include "MyTasks/led1task.hpp"
#include "myled.hpp"
#include "LED23.hpp"
#include "MyButton.hpp"

//#include "Application/Diagnostic/GlobalStatus.hpp"
#include <iostream>

std::uint32_t SystemCoreClock = 16'000'000U;


extern "C" {
  int __low_level_init(void) {
  //Switch on external 16 MHz oscillator
  RCC->CR |= RCC_CR_HSION;
  while ((RCC->CR & RCC_CR_HSIRDY) != RCC_CR_HSIRDY) {
  }
  //Switch system clock on external oscillator
  RCC->CFGR |= RCC_CFGR_SW_HSI;
  while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSI) {
  }
  //Switch on clock on PortA and PortC
  RCC->AHB1ENR |= (RCC_AHB1ENR_GPIOCEN | RCC_AHB1ENR_GPIOAEN);
  RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN ;
  //LED1 on PortA.5, set PortA.5 as output
  GPIOA->MODER |= GPIO_MODER_MODE5_0;
  /* LED2 on PortC.9, LED3 on PortC.8, LED4 on PortC.5 so set PortC.5,8,9 as output */
  GPIOC->MODER |= (GPIO_MODER_MODE9_0 | GPIO_MODER_MODE5_0 | GPIO_MODER_MODE8_0);
  
  //Button on PortC.13 external interrupt
  EXTI->RTSR |= EXTI_RTSR_TR13;
  EXTI->IMR  |= EXTI_IMR_MR13;
  SYSCFG->EXTICR[3] |= SYSCFG_EXTICR4_EXTI13_PC ;
   
  NVIC_EnableIRQ(EXTI15_10_IRQn);  
  
  return 1;
}
}

using OsWrapper::operator""ms ;
OsWrapper::Event event{500ms, 1};

MyTask myTask;
Led1Task led1Task;
OsWrapper::MailBox<int, 10> queue;
//GlobalStatus status;
MyLedTask myLedTask;
Led23Task My23Led;
MyButtonTask MyButton;

int main()
{
  using namespace OsWrapper ;
  
  Rtos::CreateThread(myLedTask, MyLedTask::Stack.data(), "MyLedTask",ThreadPriority::lowest,MyLedTask::Stack.size()) ;
  //Rtos::CreateThread(led1Task, Led1Task::Stack.data(), "Led1Task", ThreadPriority::lowest, MyTask::Stack.size());
  Rtos::CreateThread(My23Led, Led23Task::Stack.data(), "Led23Task", ThreadPriority::belowNormal, Led23Task::Stack.size());
  Rtos::CreateThread(MyButton, MyButtonTask::Stack.data(), "MyButtonTask", ThreadPriority::belowNormal, MyButtonTask::Stack.size());
  Rtos::Start();
  
  return 0;
}
