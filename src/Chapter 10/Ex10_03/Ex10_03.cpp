// Ex10_03.cpp
// 가우스 소거법을 사용해 선형 방정식의 해를 구하는 예제
#include <valarray>                              // valarray, slice, abs()
#include <vector>                                // vector 컨테이너
#include <iterator>                              // ostream 반복자
#include <algorithm>                             // For generate_n() 
#include <utility>                               // For swap() 
#include <iostream>                              // 표준 스트림
#include <iomanip>                               // 스트림 조작자
#include <string>                                // string 타입
using std::string;
using std::valarray;
using std::slice;

// 함수 프로토타입
valarray<double> get_data(size_t n);
void reduce_matrix(valarray<double>& equations, std::vector<slice>& row_slices);
valarray<double> back_substitution(valarray<double>& equations, const std::vector<slice>& row_slices);

int main()
{
  size_t n_rows {};
  std::cout << "Enter the number of variables: ";
  std::cin >> n_rows;
  auto equations = get_data(n_rows);

  // 행 순서로 행에 대한 slice 객체를 생성
  std::vector<slice> row_slices;                   // 순차 컨테이너에 행을 slice 객체로 정의
  size_t row_len {n_rows + 1};
  std::generate_n(std::back_inserter(row_slices), n_rows,
                                           [row_len]()
                                           { static size_t index {};
                                             return slice {row_len*index++, row_len, 1};
                                           });

  reduce_matrix(equations, row_slices);            // 행 사다리꼴 형태로 축소
  auto solution = back_substitution(equations, row_slices);

  // 해를 출력
  size_t count {}, perline {8};
  std::cout << "\nSolution:\n";
  string x{"x"};
  for(const auto& v : solution)
  {
    std::cout << std::setw(3) << x + std::to_string(count+1) << " = "
              << std::fixed << std::setprecision(2) << std::setw(10)
              << v;
    if(++count % perline) std::cout << '\n';
  }
  std::cout << std::endl;
}
