// Ex1_03.cpp
// 알고리즘에 함수를 전달하기
#include <iostream>                         // 표준 스트림
#include <algorithm>                        // transform()
#include <iterator>                         // 반복자
#include <functional>                       // function

class Root
{
public:
  double operator()(double x) { return std::sqrt(x); };
};

int main()
{
  double data[] { 1.5, 2.5, 3.5, 4.5, 5.5};

  // 함수 객체를 전달하기
  Root root;                                // 함수 객체
  std::cout << "Square roots are:" << std::endl;
  std::transform(std::begin(data), std::end(data),
                    std::ostream_iterator<double>(std::cout, " "), root);

  // 람다 표현식을 인자로 사용하기
  std::cout << "\n\nCubes are:" << std::endl;
  std::transform(std::begin(data), std::end(data),
                    std::ostream_iterator<double>(std::cout, " "), [](double x){ return x*x*x; });

  // std::function<> 타입의 변수를 인자로 사용하기
  std::function<double(double)> op {[](double x){ return x*x; }};
  std::cout << "\n\nSquares are:" << std::endl;
  std::transform(std::begin(data), std::end(data),
                    std::ostream_iterator<double>(std::cout, " "), op);

  // 다른 람다 표현식을 호출하는 람다 표현식을 인자로 사용하기
  std::cout << "\n\n4th powers are:" << std::endl;
  std::transform(std::begin(data), std::end(data),
             std::ostream_iterator<double>(std::cout, " "), [&op](double x){ return op(x)*op(x); });
  std::cout << std::endl;
}
