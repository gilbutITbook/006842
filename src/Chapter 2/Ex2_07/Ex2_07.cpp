// Ex2_07.cpp
// Numeric_Range 템플릿 사용해보기
#include <algorithm>                         // copy()
#include <numeric>                           // accumulate()
#include <iostream>                          // 표준 스트림
#include <vector>                            // 벡터 컨테이너
#include "Numeric_Range.h"                   // Numeric_Range<T> & Numeric_Iterator<T>

int main()
{
  Numeric_Range<double> range {1.5, 0.5, 5};
  auto first = range.begin();
  auto last = range.end();
  std::copy(first, last, std::ostream_iterator<double>(std::cout, "  "));
  std::cout << "\nSum = " << std::accumulate(std::begin(range), std::end(range), 0.0) << std::endl;

  // Numeric_Range에서 컨테이너를 초기화
  Numeric_Range<long> numbers {15L, 4L, 10};
  std::vector<long> data {std::begin(numbers), std::end(numbers)};
  std::cout << "\nValues in vector are:\n";
  std::copy(std::begin(data), std::end(data), std::ostream_iterator<long>(std::cout, "  "));
  std::cout << std::endl;

  // 범위에 있는 값을 출력하기
  std::cout << "\nThe values in the numbers range are:\n";
  for (auto n : numbers)
    std::cout << n << " ";
  std::cout << std::endl;
}
