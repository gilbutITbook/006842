// Ex8_08.cpp
// 조각 상수 분포를 설명하는 예제
#include <random>                                       // 분포와 랜덤 넘버 생성기
#include <vector>                                       // vector 컨테이너
#include <map>                                          // map 컨테이너
#include <utility>                                      // pair 타입
#include <algorithm>                                    // copy(), count(), remove()
#include <iostream>                                     // 표준 스트림
#include <iterator>                                     // 스트림 반복자
#include <iomanip>                                      // 스트림 조작자
#include <string>                                       // string 클래스
using std::string;

int main()
{
  std::vector<double> b {10, 20, 35, 55};                 // 간격: 10-20, 20-35, 35-55
  std::vector<double> w {4, 10, 6};                       // 간격에 적용할 가중치
  std::piecewise_constant_distribution<> d {std::begin(b), std::end(b), std::begin(w)};

  // 간격 경계와 간격 확률을 출력
  auto intvls = d.intervals();
  std::cout << "intervals: ";
  std::copy(std::begin(intvls), std::end(intvls), std::ostream_iterator<double>{std::cout, " "});
  std::cout << "  probability densities: ";
  auto probs = d.densities();
  std::copy(std::begin(probs), std::end(probs), std::ostream_iterator<double>{std::cout, " "});
  std::cout << '\n' << std::endl;

  std::random_device rd;
  std::default_random_engine rng {rd()};
  std::map<int, size_t> results;                          // 랜덤 값을 정수로 저장하고 카운트
  // 많은 랜덤 값을 생성...
  for(size_t i {}; i < 20000; ++i)
    ++results[static_cast<int>(std::round(d(rng)))];

  // 정수 값으로 그리기
  auto max_count = std::max_element(std::begin(results), std::end(results),
                   [](const std::pair<int, size_t>& pr1, const std::pair<int, size_t>& pr2)
                      { return pr1.second < pr2.second; })->second;
  std::for_each(std::begin(results), std::end(results),
                                   [max_count](const std::pair<int, size_t>& pr)
                                   { if(!(pr.first % 10))  // 10의 배수로 값을 표시
                                       std::cout << std::setw(3) << pr.first << "-|";
                                     else
                                       std::cout << "    |";
                                     std::cout << std::string(pr.second * 80 / max_count, '*')
                                               << '\n'; });
}