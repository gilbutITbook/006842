// Ex9_08.cpp
// 스트림 반복자를 사용해 랜덤 온도 파일을 생성하는 예제
#include <iostream>                                   // 표준 스트림
#include <iterator>                                   // 반복자, begin(), end()
#include <iomanip>                                    // 스트림 조작자
#include <fstream>                                    // 파일 스트림
#include <algorithm>                                  // generate_n(), for_each()
#include <random>                                     // 분포와 랜덤 넘버
#include <string>                                     // string 클래스
using std::string;

int main()
{
  string file_name {"temperatures.txt"};
  std::ofstream temps_out {file_name, std::ios_base::out | std::ios_base::trunc};
  const size_t n {50};                                // 필요한 온도 값의 개수

  std::random_device rd;                              // 비결정적인 소스
  std::mt19937 rng {rd()};                            // 메르센 트위스터 생성기
  double mu {50.0}, sigma {15.0};                     // 평균: 50, 온도 표준편차: 15
  std::normal_distribution<> normal {mu, sigma};      // 분포 생성

  // 랜덤 온도 값을 파일에 쓰기
  std::generate_n(std::ostream_iterator<double> { temps_out, " "}, n,
    [&rng, &normal]
  { return normal(rng); });
  temps_out.close();                                  // 출력 파일을 닫기

  // 파일의 내용을 출력한다
  std::ifstream temps_in {file_name};                 // 랜덤 온도 값을 읽기 위해 파일 열기
  for_each(std::istream_iterator<double> {temps_in}, std::istream_iterator<double> {},
    [](double t) 
      { const size_t perline {10};
        static size_t count {};
        std::cout << std::fixed << std::setprecision(2) << std::setw(5) << t
                  << ((++count % perline) ? " " : "\n");
      });
  std::cout << std::endl;
  temps_in.close();                                       // 입력 파일을 닫기
}
