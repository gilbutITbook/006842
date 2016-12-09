#pragma setlocale("ko-KR")
  
// Ex4_01.cpp
// 이름과 나이를 저장
#include <iostream>                              // 표준 스트림
#include <iomanip>                               // 스트림 조작자
#include <string>                                // string 클래스
#include <map>                                   // map 컨테이너 클래스
#include <utility>                               // pair<>, make_pair<>()
#include <cctype>                                // toupper()
#include "Name.h"

using std::string;
using Entry = std::pair<const Name, size_t>;
using std::make_pair;
using std::map;


// 입력에서 맵 항목을 생성
Entry get_entry()
{
  std::cout << "Enter first and second names followed by the age: ";
  Name name {};
  size_t age {};
  std::cin >> name >> age;
  return make_pair(name, age);
}

// 맵에 있는 원소들를 출력
void list_entries(const map<Name, size_t>& people)
{
  for(auto& entry : people)
  {
    std::cout << std::left << std::setw(30) << entry.first
              << std::right << std::setw(4) << entry.second << std::endl;
  }
}


int main()
{
  map<Name, size_t> people {{{"Ann", "Dante"}, 25}, {{"Bill", "Hook"}, 46}, {{"Jim", "Jams"}, 32}, {{"Mark", "Time"}, 32}};

  std::cout << "\nThe initial contents of the map is:\n";
  list_entries(people);

  char answer {'Y'};
  std::cout << "\nEnter a Name and age entry.\n";
  while(std::toupper(answer) == 'Y')
  {
    Entry entry {get_entry()};
    auto pr = people.insert(entry);
    if(!pr.second)
    { // 맵에 이미 있으면 업데이트해야 하는지 검사
      std::cout << "Key \"" << pr.first->first << "\" already present. Do you want to update the age (Y or N)? ";
      std::cin >> answer;
      if(std::toupper(answer) == 'Y')
        pr.first->second = entry.second;
    }
    // 입력할 항목이 더 있는지 확인
    std::cout << "Do you want to enter another entry(Y or N)? ";
    std::cin >> answer;
  }

  std::cout << "\nThe map now contains the following entries:\n";
  list_entries(people);
}