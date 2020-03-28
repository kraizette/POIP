#ifndef ADCTemperature_HPP
#define ADCTemperature_HPP
#include "IVariable.hpp"

class Temperature: public IVariable
{
private:
  float temperature ;
  float Cal1;
  float Cal2;
  
public:
  Temperature(float K1, float B1): Cal1(K1), Cal2(B1){} ;

  float Get()  override 
  {
    return temperature;
  }
  float Calculate(float code) override
  {
    temperature = Cal1*code + Cal2;
    return temperature;
  }
};
#endif