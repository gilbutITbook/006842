// Ex3_06.cpp
// 베이스 포인터를 저장하는 컨테이너에 파생 클래스 객체를 저장하는 예제
#include <iostream>                              // 표준 스트림
#include <memory>                                // 스마트 포인터
#include <vector>                                // 벡터 컨테이너
#include "Box.h"
#include "Carton.h"
using std::unique_ptr;
using std::make_unique;

int main()
{
  std::vector<unique_ptr<Box>> boxes;
  boxes.push_back(make_unique<Box>(1, 2, 3));
  boxes.push_back(make_unique<Carton>(1, 2, 3));
  boxes.push_back(make_unique<Carton>(4, 5, 6));
  boxes.push_back(make_unique<Box>(4, 5, 6));
  for(auto&& ptr : boxes)
    std::cout << *ptr << " volume is " << ptr->volume() << std::endl;
}
