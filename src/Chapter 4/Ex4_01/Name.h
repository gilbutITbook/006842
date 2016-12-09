// Name.h for Ex4_01
// 사람의 이름을 정의한다
#ifndef NAME_H
#define NAME_H
#include <string>                                // string 클래스
#include <ostream>                               // 출력 스트림
#include <istream>                               // 입력 스트림

class Name
{
private:
  std::string first {};
  std::string second {};

public:
  Name(const std::string& name1, const std::string& name2) : first (name1), second (name2) {}
  Name() = default;

  //  보다-작은(<) 연산자
  bool operator<(const Name& name) const
  {
    return second < name.second || (second == name.second && first < name.first);
  }

  friend std::istream& operator>>(std::istream& in, Name& name);
  friend std::ostream& operator<<(std::ostream& out, const Name& box);
};

// 추출 연산자 오버로드
inline std::istream& operator>>(std::istream& in, Name& name)
{
  in >> name.first >> name.second;
  return in; 
}

// 삽입 연산자 오버로드
inline std::ostream& operator<<(std::ostream& out, const Name& name)
{
  out << name.first + " " + name.second;
  return out;
}

#endif
