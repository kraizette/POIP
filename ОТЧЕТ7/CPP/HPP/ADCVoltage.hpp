#ifndef ADCVoltage_HPP
#define ADCVoltage_HPP
#include "IVariable.hpp"

class Voltage: public IVariable
{
private:
  float voltage ;
  float Cal3;
  float Cal4;
  
public:
  Voltage(float K3, float K4): Cal3(K3), Cal4(K4){} ;

  float Get()  override 
  {
    return voltage;
  }
  float Calculate(float code) override
  {
    voltage = Cal3*code + Cal4;
    return voltage;
  }
};
#endif