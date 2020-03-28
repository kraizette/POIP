#include <iostream>
#include "IADC.hpp"
#include "IVariable.hpp"

class Measure
{
private:
 IADC& myADC;
 IVariable& temperature;
 IVariable& voltage ;

public:
 Measure(IADC& adc, IVariable& temp, IVariable& volt) ;
 void MeasureAll();
 float GetTemperature();
 float GetVoltage();
}
;