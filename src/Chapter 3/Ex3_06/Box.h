// Box.h
// Carton 클래스의 기반이 될 Box 클래스 정의
#ifndef BOX_H
#define BOX_H
#include <iostream>                              // 표준 스트림
#include <istream>                               // 스트림 클래스
#include <utility>                               // 비교 연산자 템플릿
using namespace std::rel_ops;                    // 비교 연산자 템플릿 네임스페이스

class Box
{
protected:
  size_t length {};
  size_t width {};
  size_t height {};

public:
  explicit Box(size_t l = 1, size_t w = 1, size_t h = 1) : length {l}, width {w}, height {h} {}
  virtual ~Box() = default;

  virtual double volume() const;                 // 상자의 부피

  // Box 객체의 비교 연산자
  bool operator<(const Box& box) const;
  bool operator==(const Box& box) const;

  // 입력 스트림과 출력 스트림
  virtual std::istream& read(std::istream& in);
  virtual std::ostream& write(std::ostream& out) const;
};


inline double Box::volume() const { return length*width*height; }

// < 연산자
inline bool Box::operator<(const Box& box) const 
{ return volume() < box.volume(); }

// 동등성(equality) 비교 연산자
inline bool Box::operator==(const Box& box) const
{
  return length == box.length && width == box.width && height == box.height;
}

// operator>> 연산자(스트림 추출)
inline std::istream& operator>>(std::istream& in, Box& box)
{
  return box.read(in);
}

// operator<< 연산자(스트림 삽입)
inline std::ostream& operator<<(std::ostream& out, Box& box)
{
  return box.write(out);
}
#endif