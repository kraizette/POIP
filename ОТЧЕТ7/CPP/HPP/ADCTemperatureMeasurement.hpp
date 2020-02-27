#include <iostream>

class Measure
{
private:
 IADC& myADC;
 ITemperature& temperature;

public:
 Measure(IADC& adc, ITemperature& temp): myADC(adc), temperature(temp)
 {
  myADC.On();
  myADC.TSEnable();
  myADC.Config(Resolution::Bits12);
  myADC.SCMode();
  ADC1::SQR1::L::Conversions1::Set();
  ADC1::SQR3::SQ1::Channel18::Set();
 };

void Measurement()
 {
  myADC.Start();
  for(;;)  
  {
    myADC.Start();
    while(!myADC.IsReady()){};
    uint32_t code = myADC.Get();
    temperature.Calculate(static_cast<float>(code)) ;
    std::cout << "\nTemperature: " << temperature.Get() << std::endl ;
  }
}
}
;