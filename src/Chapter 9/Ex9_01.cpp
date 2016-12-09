// Ex9_01.cpp
// istream_iterator 함수 멤버를 호출하는 예제
#include <iostream>                                   // 표준 스트림
#include <iterator>                                   // 스트림 반복자 

int main()
{
  std::cout << "Enter some integers - enter Ctrl+Z to end.\n";
  std::istream_iterator<int> iter {std::cin};         // 시작 입력 스트림 반복자를 생성...
  std::istream_iterator<int> copy_iter {iter};        // ...복제본 생성
  std::istream_iterator<int> end_iter;                // 끝 입력 스트림 반복자 생성
  // 정수 몇 개를 읽어서 sum에 저장
  int sum {};
  while(iter != end_iter)                             // Ctrl+Z을 읽을 때까지 계속
  {
    sum += *iter++;
  }
  std::cout << "Total is " << sum << std::endl;

  std::cin.clear();                                   // EOF 상태를 정리
  std::cin.ignore();                                  // 문자들을 무시

  // 반복자의 복제본을 사용해 정수를 읽기
  std::cout << "Enter some more integers - enter Ctrl+Z to end.\n";
  int product {1};
  while(true)
  {
    if(copy_iter == end_iter) break;                  // Ctrl+Z를 읽으면 중단
    product *= *copy_iter++;
  }
  std::cout << "product is " << product << std::endl;

}
