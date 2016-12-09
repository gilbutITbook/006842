// Ex5_06을 위한 Name.h
// 이름을 정의한다
#ifndef NAME_H
#define NAME_H
#include <string>                                // string 클래스
#include <ostream>                               // 출력 스트림
#include <istream>                               // 입력 스트림
using std::string;

class Name
{
private:
  string first {};
  string second {};

public:
  Name(const string& name1, const string& name2) : first (name1), second (name2) {}
  Name() = default;

  const string& get_first() const  { return first; }
  const string& get_second() const { return second; }

  size_t get_length() const { return first.length() + second.length() + 1; }

  // 보다-작은(<) 연산자
  bool operator<(const Name& name) const
  {
    return second < name.second || (second == name.second && first < name.first);
  }

  // 상등 관계(==) 연산자
  bool operator==(const Name& name) const
  {
    return (second == name.second) && (first == name.first);
  }

  size_t hash() const { return std::hash<std::string>()(first+second); }

  friend std::istream& operator>>(std::istream& in, Name& name);
  friend std::ostream& operator<<(std::ostream& out, const Name& name);
};

// operator>> 연산자 오버로드
inline std::istream& operator>>(std::istream& in, Name& name)
{
  in >> name.first >> name.second;
  return in;
}

// operator<< 연산자 오버로드
inline std::ostream& operator<<(std::ostream& out, const Name& name)
{
  out << name.first + " " + name.second;
  return out;
}
#endif