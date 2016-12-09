// Ex8_01.cpp
// 8 시드를 연속으로 생성하기
#include <random>                                // random_device 클래스
#include <iostream>                              // 표준 스트림

int main()
{
  std::random_device rd;                         // 시드를 생성하는 함수 객체
  for(size_t n {}; n < 8; ++n)
    std::cout << rd() << " ";
  std::cout << std::endl;
}
