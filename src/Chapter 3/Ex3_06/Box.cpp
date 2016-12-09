// Box.cpp
// Box 클래스의 함수 멤버 정의
#include <iostream>
#include "Box.h"

// 스트림에서 Box 객체를 읽기
std::istream& Box::read(std::istream& in)
{
  size_t value {};
  if ((in >> value).eof())
    return in;
  length = value;
  in >> width >> height;
  return in;
}

// 스트림에 Box 객체를 쓰기
std::ostream& Box::write(std::ostream& out) const
{
  out << typeid(*this).name() << "(" << length << "," << width << "," << height << ")";
  return out;
}
