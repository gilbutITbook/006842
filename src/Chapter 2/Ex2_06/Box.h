// Box.h
// Ex2_06에서 사용할 Box 클래스 정의
#ifndef BOX_H
#define BOX_H
#include <iostream>                              // 표준 스트림
#include <utility>                               // 비교 연산자 템플릿
using namespace std::rel_ops;                    // 비교 연산자 템플릿 네임스페이스


class Box
{
private:
  size_t length {};
  size_t width {};
  size_t height {};

public:
  explicit Box(size_t l = 1, size_t w = 1, size_t h = 1) : length {l}, width {w}, height {h} {}
  double volume() const { return length*width*height; }
  bool operator<(const Box& box) { return volume() < box.volume(); }
  bool operator==(const Box& box) { return length == box.length&& width == box.width&&height == box.height; }

  friend std::istream& operator>>(std::istream& in, Box& box);
  friend std::ostream& operator<<(std::ostream& out, const Box& box);
};

inline std::istream& operator>>(std::istream& in, Box& box)
{
  std::cout << "Enter box length, width, & height separated by spaces - Ctrl+Z to end: ";
  size_t value;
  in >> value;
  if (in.eof()) return in;

  box.length = value;
  in >> value;
  box.width = value;
  in >> value;
  box.height = value;
  return in;
}

inline std::ostream& operator<<(std::ostream& out, const Box& box)
{
  out << "Box(" << box.length << "," << box.width << "," << box.height << ")  ";
  return out;
}
#endif