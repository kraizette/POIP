#include <cstdint>
#include <cstddef>
#include <iostream>

using namespace std;
constexpr size_t GpiocAddr = 0x1FFF7A2C;
constexpr size_t ModerAddr = GpiocAddr;
constexpr size_t RAMAddr =  0x1FFF7A2E;
int main() 
{
    volatile uint32_t *ModerPointer = reinterpret_cast<volatile uint32_t*>(ModerAddr) ;
    volatile uint32_t *RAMPointer = reinterpret_cast<volatile uint32_t*>(RAMAddr) ;

     uint32_t Moder = *ModerPointer;
     uint32_t RAM1 = *RAMPointer;

  return 0 ;
}
