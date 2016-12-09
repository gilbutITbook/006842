// List_Course.h
// Ex5_01에서 그룹에 있는 학생들을 출력하기 위한 함수 객체
#ifndef LIST_COURSE_H
#define LIST_COURSE_H
#include <iostream>                              // 표준 스트림
#include <string>                                // string 클래스
#include <set>                                   // set 컨테이너
#include <algorithm>                             // copy()
#include <iterator>                              // ostream_iterator
#include "Student.h"

using Subject = std::string;                     // 코스 과목
using Group = std::set<Student>;                 // 과목에 등록한 학생 그룹
using Course = std::pair<Subject, Group>;        // 코스를 표현한 pair

class List_Course
{
public:
  void operator()(const Course& course)
  {
    std::cout << "\n\n" << course.first << "  " << course.second.size() << " students:\n  ";
    std::copy(std::begin(course.second), std::end(course.second),
              std::ostream_iterator<Student>(std::cout, "  "));
  }
};
#endif
