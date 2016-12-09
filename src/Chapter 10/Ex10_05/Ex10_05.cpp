// Ex10_05.cpp
// 선형 방정식을 푸는 시간을 측정하는 예제
#include <valarray>                              // valarray, slice, abs()
#include <vector>                                // vector 컨테이너
#include <iterator>                              // ostream 반복자
#include <algorithm>                             // generate_n() 
#include <utility>                               // swap() 
#include <iostream>                              // 표준 스트림
#include <iomanip>                               // 스트림 조작자
#include <string>                                // string 타입
#include <chrono>                                // 클록, duration, time_point
using std::string;
using std::valarray;
using std::slice;
using namespace std::chrono;

// 함수 프로토타입
valarray<double> get_data(size_t n);
void reduce_matrix(valarray<double>& equations, std::vector<slice>& row_slices);
valarray<double> back_substitution(valarray<double>& equations, const std::vector<slice>& row_slices);

// time_point<>에 대해 정확한 시간 간격을 초 단위로 출력한다
template<typename TimePoint>
void print_timepoint(const TimePoint& tp, size_t places = 0)
{
  auto elapsed = tp.time_since_epoch();          // 시간 간격을 위한 duration 객체

  auto seconds = std::chrono::duration_cast<std::chrono::duration<double>>(elapsed).count();
  std::cout << std::fixed << std::setprecision(places) << seconds << " seconds\n";
}

int main()
{
  size_t n_rows {};
  std::cout << "Enter the number of variables: ";
  std::cin >> n_rows;
  auto equations = get_data(n_rows);

  auto start_time = steady_clock::now();                   // time_point 객체

  // 행 순서로 행에 대한 slice 객체를 생성
  std::vector<slice> row_slices;                           // 순차 컨테이너에 행을 slice 객체로 정의
  size_t row_len {n_rows + 1};
  std::generate_n(std::back_inserter(row_slices), n_rows,
    [row_len]()
  { static size_t index {};
  return slice {row_len*index++, row_len, 1};
  });

  reduce_matrix(equations, row_slices);                    // 행 사다리꼴 형태로 축소
  auto solution = back_substitution(equations, row_slices);

  auto end_time = steady_clock::now();                     // time_point 객체
  auto elapsed = end_time - start_time.time_since_epoch();
  std::cout << "Time to solve " << n_rows << " equations is ";
  print_timepoint(elapsed, 9);

  // 해를 출력
  size_t count {}, perline {8};
  std::cout << "\nSolution:\n";
  string x {"x"};
  for(const auto& v : solution)
  {
    std::cout << std::setw(3) << x + std::to_string(count + 1) << " = "
      << std::fixed << std::setprecision(2) << std::setw(10)
      << v;
    if(++count % perline) std::cout << '\n';
  }
  std::cout << std::endl;
}