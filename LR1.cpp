#include <iostream> //for std: cout

int main()
{
  float a,b,c,p,s, l, m, k, q, v, r, o,pi=3.1415  ;
  {
  std::cout<<"Введите длины сторон треугольника:";
    std::cin>>a>>b>>c;
  if ((a+b)<c or (a+c)<b or (b+c)<a)
    {
    std::cout<<"\nНеправильный треугольник";
    goto sq;
    }
  p=(a+b+c)/2;
  s= sqrt(p*(p-a)*(p-b)*(p-c));
  v=a+b+c;
  std::cout <<"\nПлощадь треугольника:" << s <<"\nПериметр треугольника:" << v;
  
  sq:
  std::cout<<"\nВведите длины сторон прямоугольника:";
  std::cin>>l>>m;
  k=l*m;
  q=(l+m)*2;
  std::cout <<"\nПлощадь прямоугольника:" << k <<"\nПериметр прямоугольника:" << q ;
  
  std::cout<<"\nВведите радиус круга:";
  std::cin>>r;
  o=pi*r*r;
  std::cout <<"\nПлощадь круга:" << o;
  return 0;
}
}