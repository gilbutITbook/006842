// Hash_Function_Objects.h
// Ex4_07를 위한 해시 함수 객체 타입
#ifndef HASH_FUNCTION_OBJECTS_H
#define HASH_FUNCTION_OBJECTS_H

#include <string>                                // string 클래스
#include <utility>                               // pair 타입
#include <tuple>                                 // tuple 타입

using Name = std::pair < std::string, std::string >;
using Phone = std::tuple < std::string, std::string, std::string >;

// 전화 번호를 해시한다
class PhoneHash
{
public:
  size_t operator()(const Phone& phone) const
  {
    return std::hash<std::string>()(std::get<0>(phone)+std::get<1>(phone)+std::get<2>(phone));
  }
};

// 이름을 해시한다
class NameHash
{
public:
  size_t operator()(const Name& name) const
  {
    return std::hash<std::string>()(name.first + name.second);
  }
};
#endif