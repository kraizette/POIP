#include "adc1registers.hpp" //for ADC1
#include "adccommonregisters.hpp" //for ADCCommon
#include "gpioaregisters.hpp"  //for Gpioa
#include "gpiocregisters.hpp"  //for Gpioc
#include "rccregisters.hpp"    //for RCC
#include "tim2registers.hpp"   //for TIM2
#include <iostream>

using namespace std;

extern "C"
{
int __low_level_init(void)
{
  //Switch on external 8 MHz oscillator
  RCC::CR::HSEON::On::Set();
  while(!RCC::CR::HSERDY::Ready::IsSet())
  {}; 
  //Switch system clock on external oscillator
  RCC::CFGR::SW::Hse::Set();
  while (!RCC::CFGR::SWS::Hse::IsSet())
  {};
    
   //---------------ADC1 setup--------------------------------------------------
  //Switch on clock on ADC1
  RCC::APB2ENR::ADC1EN::Enable::Set();
   //Switch On internal tempearture sensor  
  ADC_Common::CCR::TSVREFE::Enable::Set();
  //Resolution of the conversion.
  ADC1::CR1::RES::Bits12::Set();
   //Set single conversion mode
  ADC1::CR2::CONT::SingleConversion::Set();
  ADC1::CR2::EOCS::SingleConversion::Set();   
  // Set laentgh of conversion sequence
  ADC1::SQR1::L::Conversions2::Set();
  // Connect first conversion on Channel 17 ADC1_IN17 (VREFINT)
  ADC1::SQR3::SQ1::Channel17::Set();
  // Connect second conversion on Channel 18 ADC1_IN18 (temperature sensor) 
  ADC1::SQR3::SQ2::Channel18::Set();
  // Set 84 cycles sample rate for channels
  ADC1::SMPR1::SMP17::Cycles84::Set();
  ADC1::SMPR1::SMP18::Cycles84::Set();
  // Enable scan mod
  ADC1::CR1::SCAN::Enable::Set();
  // Enable ADC1
  ADC1::CR2::ADON::Enable::Set();
  
  return 1;
}
}
//---------------Addresses------------------------------------------------------
// Temperature sensor calibration values
constexpr size_t tsCal1Addr = 0x1FFF7A2C; //TS ADC raw data acquired at temperature of 30 °C
constexpr size_t tsCal2Addr =  0x1FFF7A2E; // TS ADC raw data acquired at temperature of 110 °C
// Internal reference voltage calibration values
constexpr size_t VddaCalAddr =  0x1FFF7A2A; //Raw data acquired at temperature of 30 °C

//---------------Calibration values---------------------------------------------
// Temperature sensor calibration values
volatile uint16_t *tsCal1Pointer = reinterpret_cast<volatile uint16_t*>(tsCal1Addr) ;
volatile uint16_t *tsCal2Pointer = reinterpret_cast<volatile uint16_t*>(tsCal2Addr) ;
uint16_t tsCal132 = (*tsCal1Pointer);
uint16_t tsCal232 = (*tsCal2Pointer);
float tsCal1 = tsCal132; 
float tsCal2 = tsCal232;

// Internal reference voltage calibration values
volatile uint16_t *VddaCalPointer = reinterpret_cast<volatile uint16_t*>(VddaCalAddr) ;
uint16_t VddaCal32 = (*VddaCalPointer);
float VddaCal = VddaCal32;

/*----------------Temperature coeficients---------------------------------------

Temperature sensor calibration:-------------------------------------------------
temperature = (110-30) * (Adc_code - tsCal1) / (tsCal2- tsCal2) + 30 ;
kx+b:
temperature = ADC_Code * (110-30)/(tsCal2- tsCal2) + (30 - (110-30)*tsCal1/(tsCal2- tsCal2) )
k = (110-30)/(tsCal2- tsCal2)
b = 30 - (110-30)*tsCal1/(tsCal2- tsCal2) 

Internal reference voltage calibration:-----------------------------------------
temperature = (110-30) * ((ADC_Code * vddaCal)/vdda -  tsCal1) / (tsCal2 - tsCal1) + DEGREE_30;
kx+b:
temperature = ADC_Code * (110-30)*VddaCal/(Vdda*(tsCal2-tsCal1)) + DEGREE_30 - (110-30)*tsCal1/(tsCal2-tsCal1)
k = (110-30)*VddaCal/(Vdda*(tsCal2-tsCal1))
b = DEGREE_30 - (110-30)*tsCal1/(tsCal2-tsCal1)
*/

/*---------------Temperature coeficients without calibration--------------------
0.0025 - Average slope
0.76 - Voltage at 25
3.3 - Reference voltage
4096 - 2^12 (for 12bits)
*/

constexpr float b = 25.0F - 0.76F/0.0025F ;
constexpr float k = 3.3F/(4096.0F*0.0025F); 

int main()
{
  uint32_t ADC_Code = 0U ; //for getting reference voltage data from ADC
  uint32_t Vdda = 0U ; //for getting reference voltage data from ADC
  float temperature = 0.0F ;
  float temperature1 = 0.0F ;
  float temperature2 = 0.0F ;
  float DEGREE_30 = 30.0F;
  
  for(;;)    
  {
    //Start conversion
    ADC1::CR2::SWSTART::On::Set();
    
    //----------Reference voltage-----------------------------------------------
    // wait until Conversion is not complete 
    while(!ADC1::SR::EOC::ConversionComplete::IsSet())
    {};
    Vdda =  ADC1::DR::Get(); //Get data from ADC;
    
    //----------Temperature-----------------------------------------------------
    // wait until Conversion is not complete 
    while(!ADC1::SR::EOC::ConversionComplete::IsSet())
    {};
    ADC_Code =  ADC1::DR::Get(); //Get data from ADC;
    //without calibration
    temperature = ADC_Code * k + b ; //Convert ADC counts to temperature
    
    //temperature sensor calibration
    temperature1 = ADC_Code * (110-30)/(tsCal2 - tsCal1) + (30 - (110-30)*tsCal1/(tsCal2- tsCal1) );
    
    //temperature sensor and internal reference voltage calibration
    temperature2 = ADC_Code * (110-30)*VddaCal/(Vdda*(tsCal2-tsCal1)) + DEGREE_30 - (110-30)*tsCal1/(tsCal2-tsCal1) ; //Convert ADC counts to temperature

    //----------I/O-------------------------------------------------------------
    cout << "\nADC_Code: " << ADC_Code << " tsCal1: " << tsCal1 << " tsCal2: " << tsCal2 << "\nVdda: " << Vdda << " VddaCal: " << VddaCal << " \nTemperature \nWithout calibration: " << temperature << " \nWith temperature sensor calibration: " << temperature1 << " \nWith temperature sensor and internal reference voltage calibration: " << temperature2 << endl ;
  }
return 0;  
}
