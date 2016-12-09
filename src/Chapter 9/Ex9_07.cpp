// Ex9_07.cpp
// 스트림 반복자를 사용해 파일에 피보나치 수를 쓰는 예제
#include <iostream>                                        // 표준 스트림
#include <iterator>                                        // 반복자, begin(), end()
#include <iomanip>                                         // 스트림 조작자
#include <fstream>                                         // fstream
#include <algorithm>                                       // generate_n(), for_each()
#include <string>
using std::string;

int main()
{
  string file_name {"fibonacci.txt"};
  std::fstream fibonacci {file_name, std::ios_base::in | std::ios_base::out | 
                          std::ios_base::trunc};
  if(!fibonacci)
  {
    std::cerr << file_name << " not open." << std::endl;
    exit(1);
  }
  unsigned long long first {0ULL}, second {1ULL};
  auto iter = std::ostream_iterator<unsigned long long> {fibonacci, " "};
  (iter = first) = second;                                 // 처음 두 값을 쓴다

  const size_t n {50};
  std::generate_n(iter, n, [&first, &second]
  { auto result = first + second;
  first = second;
  second = result;
  return result; });
  fibonacci.seekg(0);                                      // 파일 처음으로 돌아간다
  std::for_each(std::istream_iterator<unsigned long long> {fibonacci},
    std::istream_iterator<unsigned long long> {},
    [](unsigned long long k)
  { const size_t perline {6};
  static size_t count {};
  std::cout << std::setw(12) << k << ((++count % perline) ? " " : "\n");
  });
  std::cout << std::endl;
  fibonacci.close();                                       // 파일을 닫는다
}
