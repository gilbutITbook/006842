// Ex2_04.cpp
// deque 컨테이너 사용하기
#include <iostream>                          // 표준 스트림
#include <algorithm>                         // copy()
#include <deque>                             // deque 컨테이너
#include <string>                            // string 클래스
#include <iterator>                          // front_insert_iterator와 스트림 반복자

using std::string;

int main()
{
  std::deque<string> names;
  std::cout << "Enter first names separated by spaces. Enter Ctrl+Z on a new line to end:\n";
  std::copy(std::istream_iterator<string> {std::cin}, std::istream_iterator<string> {},
                                                      std::front_inserter(names));
  std::cout << "\nIn reverse order, the names you entered are:\n";
  std::copy(std::begin(names), std::end(names), std::ostream_iterator<string> {std::cout, "  "});
  std::cout << std::endl;
}
