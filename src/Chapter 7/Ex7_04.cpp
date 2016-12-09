// Ex7_04.cpp
// reverse_copy()를 사용해 회문 테스트하기
#include <iostream>                                      // 표준 스트림
#include <iterator>                                      // 스트림 반복자, begin(), end()
#include <algorithm>                                     // reverse_copy(), copy_if()
#include <cctype>                                        // toupper(), isalpha()
#include <string>
using std::string;

int main()
{
  while(true)
  {
    string sentence;
    std::cout << "Enter a sentence or Ctrl+Z to end: ";
    std::getline(std::cin, sentence);
    if(std::cin.eof()) break;

    // 문자가 알파벳이면 복제하고 대문자로 변환한다
    string only_letters;
    std::copy_if(std::begin(sentence), std::end(sentence), std::back_inserter(only_letters),
      [](char ch) { return std::isalpha(ch); });
    std::for_each(std::begin(only_letters), std::end(only_letters), [](char& ch) { ch = toupper(ch); });

    // 뒤집은 복제본을 만든다
    string reversed;
    std::reverse_copy(std::begin(only_letters), std::end(only_letters), std::back_inserter(reversed));
    std::cout << '"' << sentence << '"'
      << (only_letters == reversed ? " is" : " is not") << " a palindrome." << std::endl;
  }
}
