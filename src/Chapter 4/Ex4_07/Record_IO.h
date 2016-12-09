#ifndef RECORD_IO_H
#define RECORD_IO_H
#include <string>                                // string 클래스
#include <istream>                               // istream 클래스
#include <ostream>                               // ostream 클래스
#include <utility>                               // pair 타입
#include <tuple>                                 // tuple 타입

using Name = std::pair <std::string, std::string>;
using Phone = std::tuple <std::string, std::string, std::string>;

// 전화번호 출력
inline std::ostream& operator<<(std::ostream& out, const Phone& phone)
{
  std::string area_code {}, exchange {}, number {};
  std::tie(area_code, exchange, number) = phone;
  out << area_code << " " << exchange << " " << number;
  return out;
}

// 이름 출력
inline std::ostream& operator<<(std::ostream& out, const Name& name)
{
  out << name.first << " " << name.second;
  return out;
}

// 전화번호 입력
inline std::istream& operator>>(std::istream& in, Phone& phone)
{
  std::string area_code {}, exchange {}, number {};
  in >> std::ws >> area_code >> exchange >> number;
  phone = std::make_tuple(area_code, exchange, number);
  return in;
}

// 이름 입력
inline std::istream& operator>>(std::istream& in, Name& name)
{
  in >> std::ws >> name.first >> name.second;
  return in;
}
#endif