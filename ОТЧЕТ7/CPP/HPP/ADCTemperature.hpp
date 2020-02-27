struct ITemperature
{
 virtual float Get() = 0 ;
 virtual float Calculate(float code) = 0 ;
} ;
 
 
class Temperature: public ITemperature
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
  }
};