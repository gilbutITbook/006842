// Gaussian.cpp
// 가우스 소거법을 구현한 함수
#include <valarray>                              // valarray, slice, abs()
#include <vector>                                // vector 컨테이너
#include <iterator>                              // ostream 반복자
#include <algorithm>                             // copy_n() 
#include <utility>                               // swap() 
#include <iostream>                              // 표준 스트림
#include <iomanip>                               // 스트림 조작자
using std::valarray;
using std::slice;

// 미지수 n개로 된 n개의 방정식에 대한 데이터를 읽어들인다
valarray<double> get_data(size_t n)
{
  valarray<double> equations(n*(n + 1));    // n+1개의 원소로 된 n개의 행
  std::cout << "Enter " << n + 1
    << " values for each of "<< n << " equations.\n"
    << "(i.e. including coefficients that are zero and the rhs:\n";
  for(auto& coeff: equations) std::cin >> coeff;
  return equations;
}

// 행 n에서 최적 피벗을 선택하기(행의 인덱스는 0부터 시작한다)
void set_pivot(const valarray<double>& equations, std::vector<slice>& row_slices, size_t n)
{
  size_t n_rows {row_slices.size()};             // 행의 개수
  size_t row_len {n_rows + 1};                   // 행 길이 = 열의 개수

  // 행 n부터 시작하고, 열 n의 원소를 포함한 객체를 생성
  valarray<double> column {equations[slice {n*row_len + n, n_rows - n, row_len}]};
  column = std::abs(column);                     // 절댓값

  size_t max_index {};                           // 열에서 최적 피벗에 대한 인덱스
  for(size_t i {1}; i < column.size(); ++i)      // 최댓값의 인덱스를 찾기
  {
    if(column[max_index] < column[i]) max_index = i;
  }

  if(max_index > 0)
  { // 피벗이 열에서 첫 번째가 아닌 경우 - 첫 번째로 만들기 위해 행을 교환한다
    std::swap(row_slices[n], row_slices[n + max_index]);
  }
  else if(!column[0])                            // 제로(0) 피벗인지 검사
  { // 피벗이 0이면 행렬은 특이 행렬
    std::cerr << "No solution. Ending program." << std::endl;
    std::exit(1);
  }
} 

// 방정식 행렬을 행 사다리꼴 형태로 정리(reduce)
// equations 객체는 미지수가 n개인 방정식 n개를 행렬로 저장하고 있다
// row_slices 컨테이너의 원소들은 방정식의 행을 정의한 것이다
void reduce_matrix(valarray<double>& equations, std::vector<slice>& row_slices)
{
  size_t n_rows {row_slices.size()};             // 행의 개수
  size_t row_len {n_rows + 1};                   // 행 길이
  for(size_t row {}; row < n_rows - 1; ++row)    // 첫 번째 행부터 끝에서 두 번째 행까지
  {
    set_pivot(equations, row_slices, row);       // 최적 피벗 찾기

    // 피벗 행에 대한 원소 값을 담고 있는 객체 생성하기
    valarray<double> pivot_row {equations[row_slices[row]]};
    auto pivot = pivot_row[row];                 // 피벗 원소
    pivot_row /= pivot;                          // 피벗 행을 피벗으로 나누기

    // 현재 행 뒤의 각 행에 대해
    // 피벗 열에 행 원소로 곱한 피벗 행을 빼기
    for(size_t next_row {row + 1}; next_row < n_rows; ++next_row)
    {
      equations[row_slices[next_row]] -= equations[row_slices[next_row].start() + row] * pivot_row;
    }
  }
} 

// 후치 대입을 수행하고 해(solution)를 반환한다
valarray<double> back_substitution(valarray<double>& equations, 
                                                      const std::vector<slice>& row_slices)
{
  size_t n_rows{row_slices.size()};
  size_t row_len {n_rows + 1};

  // 마지막 행을 끝에서 두 번째 원소로 나눈다
  // 마지막 행을 각 행의 끝에서 두 번째 원소로 곱하고, 해당 행에서 뺀다.
  // 나머지 행에 대해서도 이 과정을 반복한다
  valarray<double> results(n_rows);         // 해를 저장한다
  for(int row {static_cast<int>(n_rows - 1)}; row >= 0; --row)
  {
    equations[row_slices[row]] /= 
                       valarray<double>(equations[row_slices[row].start() + row], row_len);
    valarray<double> last_row {equations[row_slices[row]]};
    results[row] = last_row[n_rows];               // x[row]의 값을 저장한다
    for(int i {}; i < row; ++i)
    {
      equations[row_slices[i]] -= equations[row_slices[i].start() + row] * last_row;
    }
  }
  return results; 
}