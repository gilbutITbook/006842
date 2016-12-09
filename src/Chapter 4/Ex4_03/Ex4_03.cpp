// Ex4_03.cpp
// 맵에 인명에 따른 명언을 저장하는 프로그램
#include <iostream>                              // 표준 스트림
#include <cctype>                                // toupper()
#include <map>                                   // map 컨테이너
#include <string>                                // string 클래스
#include "Quotations.h"
#include "Name.h"

using std::string;

// 표준 입력에서 이름을 읽어들인다
inline Name get_name()
{
  Name name {};
  std::cout << "Enter first name and second name: ";
  std::cin >> std::ws >> name;
  return name;
}

// 표준 입력에서 명언을 읽어들인다
inline string get_quote(const Name& name)
{
  std::cout << "Enter the quotation for " << name
    << ". Enter * to end:\n";
  string quote;
  std::getline(std::cin >> std::ws, quote, '*');
  return quote;
}

int main()
{
  std::map<Name, Quotations> quotations;         // 이름/명언 쌍을 저장할 컨테이너

  std::cout << "Enter 'A' to add a quote."
    "\nEnter 'L' to list all quotes."
    "\nEnter 'G' to get a quote."
    "\nEnter 'Q' to end.\n";
  Name name {};                                  // 이름을 저장
  string quote {};                               // 명언을 저장
  char  command {};                              // 명령어를 저장

  while(command != 'Q')
  {
    std::cout << "\nEnter command: ";
    std::cin >> command;
    command = static_cast<char>(std::toupper(command));
    switch(command)
    {
    case 'Q':
      break;                                     // 동작을 끝낸다

    case 'A':
      name = get_name();
      quote = get_quote(name);
      quotations[name] << quote;
      break;

    case 'G':
    {
      name = get_name();
      const auto& quotes = quotations[name];
      size_t count = quotes.size();
      if(!count)
      {
        std::cout << "There are no quotes recorded for "
          << name << std::endl;
        continue;
      }
      size_t index {};
      if(count > 1)
      {
        std::cout << "There are " << count << " quotes for " << name << ".\n"
          << "Enter an index from 0 to " << count - 1 << ": ";
        std::cin >> index;
      }
      std::cout << quotations[name][index] << std::endl;
    }
    break;
    case 'L':
      if(quotations.empty())                                         // 이름/명언이 없을 때를 테스트
      {
        std::cout << "\nNo quotations recorded for anyone." << std::endl;
      }
      // List all quotations
      for(const auto& pr : quotations)                               // 이름/명언에 대해 반복
      {
        std::cout << '\n' << pr.first << std::endl;
        for(const auto& quote : pr.second)                           // 명언에 대해 반복
        {
          std::cout << "  " << quote << std::endl;
        }
      }
      break;

    default:
      std::cout << " Command must be 'A', 'G', 'L', or 'Q'. Try again.\n";
      continue;
      break;
    }
  }
}