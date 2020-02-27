struct IADC
{
 virtual void On() = 0 ;
 virtual void Off() = 0 ;
 virtual void Start() = 0 ;
 virtual bool IsReady() = 0 ;
 virtual uint32_t Get() = 0 ;
 virtual void TSEnable() = 0 ;
 virtual void Config(Resolution resolution) = 0;
 virtual void SCMode () = 0;
} ;


class ADC: public IADC
{
private:
  IHardwareADC& hwADC ; 
  
public:
  ADC(IHardwareADC& adc): hwADC(adc) {};
  void On()  override
  {
     hwADC.On()  ;
  }
  void Off()  override 
  {
    hwADC.Off() ;
  }
 void Start() override
 {
   hwADC.Start() ;
 }
 bool IsReady() override
 {
    return hwADC.IsReady() ;
 }
 uint32_t Get() override
 {
    return hwADC.Get() ;
 }
 void TSEnable() override
 {
   hwADC.TSEnable() ;
 }
 void Config(Resolution resolution) override
 {
   hwADC.Config(resolution);
 }
 void SCMode() override
 {
  hwADC.SCMode();
 }
} ;