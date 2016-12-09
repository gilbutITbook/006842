// Ex4_07.cpp
#include <iostream>                              // 표준 스트림
#include <cctype>                                // toupper()
#include <string>                                // string 클래스
#include <unordered_map>                         // unordered_map 컨테이너

#include "Record_IO.h"
#include "My_Templates.h"
#include "Hash_Function_Objects.h"

using std::string;
using std::unordered_multimap;
using Name = std::pair < string, string >;
using Phone = std::tuple < string, string, string >;

// 명령 프롬프트를 표시한다
void show_operations()
{
  std::cout << "Operations:\n"
    << "A: Add an element.\n"
    << "D: Delete elements.\n"
    << "F: Find elements.\n"
    << "L: List all elements.\n"
    << "Q: Quit the program.\n\n";
}

int main()
{
  unordered_multimap<Name, Phone, NameHash> by_name {8, NameHash()};
  unordered_multimap<Phone, Name, PhoneHash> by_number {8, PhoneHash()};
  show_operations();

  char choice {};                                     // 처리할 작업 선택
  Phone number {};                                    // 숫자를 기록
  Name name {};                                       // 이름을 기록

  while(std::toupper(choice) != 'Q')                  // 종료할 때까지 계속 실행...
  {
    std::cout << "Enter a command: ";
    std::cin >> choice;
    switch(std::toupper(choice))
    {
    case 'A':                                         // 레코드를 추가
      std::cout << "Enter first & second names, area code, exchange, and number separated by spaces:\n";
      std::cin >> name >> number;
      by_name.emplace(name, number);                  // 두 컨테이너 모두...
      by_number.emplace(number, name);                // ...내부에서 생성
      break;

    case 'D':                                         // 레코드 삭제
    {
      std::cout << "Enter a name: ";                  // 이름으로 찾기
      auto pr = find_elements(by_name);
      auto count = std::distance(pr.first, pr.second);  // 원소의 개수
      if(count == 1)
      {                                               // 원소가 하나만 있다면…
        by_number.erase(pr.first->second);            // ... by_numbers 컨테이너에서 삭제
        by_name.erase(pr.first);                      // ... by_names 컨테이너에서 삭제
      }
      else if(count > 1)
      { // 두 개 이상이면
        std::cout << "There are " << count << " records for "
                  << pr.first->first << ". Delete all(Y or N)? ";
        std::cin >> choice;

        if(std::toupper(choice) == 'Y')
        { // by_number 컨테이너부터 레코드를 삭제
          for(auto iter = pr.first; iter != pr.second; ++iter)
          {
            by_number.erase(iter->second);
          }
          by_name.erase(pr.first, pr.second);         // by_name 컨테이너에서도 삭제
        }
      }
    }
    break;

    case 'F':                                         // 레코드를 찾기
      std::cout << "Find by name(Y or N)? ";
      std::cin >> choice;
      if(std::toupper(choice) == 'Y')
      {
        std::cout << "Enter first name and second name: ";
        list_range(find_elements(by_name));
      }
      else
      {
        std::cout << "Enter area code, exchange, and number separated by spaces: ";
        list_range(find_elements(by_number));
      }
      break;

    case 'L':                                         // 모든 레코드를 출력
      std::cout << "List by name(Y or N)? ";
      std::cin >> choice;
      if(std::toupper(choice) == 'Y')
        list_elements(by_name);
      else
        list_elements(by_number);
      break;
    case 'Q':
      break;

    default:
      std::cout << "Invalid command - try again.\n";
    }
  }
}