// Ex5_03.cpp
// 과목에 학생들을 가리키는 스마트 포인터를 등록하기
#include <iostream>                              // 표준 스트림
#include <string>                                // string 클래스
#include <map>                                   // map 컨테이너
#include <set>                                   // set 컨테이너
#include <vector>                                // vector 컨테이너
#include <random>                                // 랜덤 숫자 생성
#include <algorithm>                             // for_each(), count_if()
#include <memory>                                // shared_ptr, weak_ptr
#include <cctype>                                // toupper()
#include "Student.h"
#include "List_Course.h"

using std::string;
using std::make_shared;
using Distribution = std::uniform_int_distribution<size_t>;
using Subject = std::shared_ptr<string>;                                                  // 코스 과목
using Subjects = std::vector<Subject>;                                                    // 과목 벡터
using Group = std::set<std::weak_ptr<Student>, std::owner_less<std::weak_ptr<Student>>>;  // 과목을 수강한 학생 그룹
using Students = std::vector<std::shared_ptr<Student>>;                                   // 모든 학생 정보
using Course = std::pair<Subject, Group>;                                                 // 코스를 표현한 pair
using Courses = std::map<Subject, Group, std::owner_less<Subject>>;                       // 코스 정보를 위한 컨테이너

static std::default_random_engine gen_value;

// 학생들을 참조하는 스마트 포인터의 벡터를 생성한다
Students create_students()
{
  Students students;
  string first_names[] {"Ann", "Jim", "Eve", "Dan", "Ted"};
  string second_names[] {"Smith", "Jones", "Howe", "Watt", "Beck"};

  for(const auto& first : first_names)
    for(const auto& second : second_names)
    {
      students.emplace_back(std::make_shared<Student>(first, second));
    }

  return students;
}

// 과목을 수강하는 학생들의 그룹을 생성한다
Group make_group(const Students& students, size_t group_size, const Distribution& choose_student)
{
  Group group;                                             // 과목을 수강하는 학생 그룹

  // 과목 그룹에 등록할 학생들을 선택한다
  size_t count {};                                         // 그룹에 등록된 학생 수
  std::pair<Group::iterator, bool> pr;                     // 학생 삽입에서 반환된 값을 저장한다

  // group_size에 지정한 학생수에 도달할 때까지 그룹에 임의의 학생을 삽입한다
  while(count < group_size)
  {  // 삽입이 성공하면 카운트를 증가시킨다...
    if(group.insert(students[choose_student(gen_value)]).second) ++count;
  }
  return group;
}

int main()
{
  Students students = create_students();
  Subjects subjects {make_shared<string>("Biology"), make_shared<string>("Physics"), make_shared<string>("Chemistry"),
                     make_shared<string>("Mathematics"), make_shared<string>("Astronomy"), make_shared<string>("Drama"), 
                     make_shared<string>("Politics"), make_shared<string>("Philosophy"), make_shared<string>("Economics")};
  Courses courses;                                         // 과목 키를 갖는 전체 코스

  size_t min_subjects {4};                                 // 학생당 최소 과목 수
  size_t min_group {min_subjects};                         // 코스당 최소 학생 수
  
  // 코스당 최대 학생 수
  size_t max_group {(students.size()*min_subjects) / subjects.size()};  
  
  // 각 과목을 선택한 학생들의 그룹을 생성한다
  Distribution group_size {min_group, max_group};          // 코스당 학생들을 위한 분포
  Distribution choose_student {0, students.size() - 1};    // 랜덤 학생 선택기
  for(const auto& subject : subjects)
    courses.emplace(subject, make_group(students, group_size(gen_value), choose_student));

  Distribution choose_course {0, subjects.size() - 1};     // 랜덤 코스 선택기

  // 모든 학생은 최소 수강 과목에 출석해야 한다...
  // ... 최소 수강 과목을 출석하는지 확인해야 하는 학생들...
  for(const auto& student : students)
  { // 최소 수강 과목을 만족하는지 검증한다

    // 학생이 등록한 과목 수를 카운트
    size_t course_count = std::count_if(std::begin(courses), std::end(courses), [&student](const Course& course)
    {  return course.second.count(student); });
    if(course_count >= min_subjects) continue;             // 최소 수강을 만족하면 다음 학생으로

    // 최소 수강을 미달한 과목 수
    size_t additional {min_subjects - course_count};       // 추가 등록이 필요한 과목 수
    if(!course_count)                                      // 선택한 과목이 없다면...
      std::cout << *student << " is work-shy, having signed up for NO Subjects!\n";
    else                                                   // 일부 과목만 등록했다면...
      std::cout << *student << " is only signed up for " << course_count << " Subjects!\n";

    std::cout << "Registering " << *student << " for " << additional
      << " more course" << (additional > 1 ? "s" : "") << ".\n\n";

    // 최소 수강 요건을 맞추기 위해 과목을 추가로 등록
    while(course_count < min_subjects)
      if((courses.find(subjects[choose_course(gen_value)])->second.insert(student)).second) ++course_count;
  }

  // 각 코스에 참여하는 학생들을 출력
  //std::for_each(std::begin(courses), std::end(courses), List_Course());
  //std::cout << std::endl;

  // 코스 과목을 출력하기
  std::cout << "Course subjects are:\n  ";
  for(const auto& p : subjects)
    std::cout  << *p << "  ";
  std::cout << "\n\n";

  // 학생들을 출력할 코스를 선택하기
  char answer {'Y'};
  string subject {};
  while(std::toupper(answer) == 'Y')
  {
    std::cout << "Enter a course subject to get the list of students: ";
    std::cin >> subject;
    auto iter = std::find_if(std::begin(subjects), std::end(subjects), [&subject](const Subject& psubj){ return subject == *psubj; });
    if(iter == std::end(subjects))
      std::cout << subject << " not found!\n";
    else
    {
      List_Course()(*courses.find(*iter));
      std::cout << std::endl;
    }
    std::cout << "Do you want to see another subject(Y or N)? ";
    std::cin >> answer;
  }
}
