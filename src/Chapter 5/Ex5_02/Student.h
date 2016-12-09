// Student.h
// Ex5_02를 위한 Student 클래스 정의 - Ex5_01과 같음
#ifndef STUDENT_H
#define STUDENT_H
#include <string>                                // string 클래스
#include <ostream>                               // 출력 스트림

class Student
{
private:
  std::string first {};
  std::string second {};

public:
  Student(const std::string& name1, const std::string& name2) : first (name1), second (name2){}
  Student(Student&& student) : first(std::move(student.first)), second(std::move(student.second)){} // 이동 생성자
  Student(const Student& student) : first(student.first), second(student.second){}                  // 복제 생성자
  Student() {}                                                                                      // 기본 생성자

  // 보다-작은(<) 연산자
  bool operator<(const Student& student) const
  {
    return second < student.second || (second == student.second && first < student.first);
  }

  friend std::ostream& operator<<(std::ostream& out, const Student& student);
};

// 삽입 연산자 오버로드
inline std::ostream& operator<<(std::ostream& out, const Student& student)
{
  out << student.first + " " + student.second;
  return out;
}
#endif