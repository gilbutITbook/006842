// Ex8_05.cpp
// 정규분포를 확인하는 예제
#include <random>                                      // 분포와 랜덤 넘버 생성기
#include <algorithm>                                   // generate(), for_each(), max_element(), transform()
#include <numeric>                                     // accumulate() 
#include <vector>                                      // vector 컨테이너
#include <map>                                         // map 컨테이너
#include <cmath>                                       // pow(), round() 함수
#include <iostream>                                    // 표준 스트림
#include <iomanip>
#include <string>
using std::string;
using Params = std::normal_distribution<>::param_type;

// 샘플 값의 범위에서 분포를 그리는 템플릿
template<typename Iter>
void dist_plot(Iter& beg_iter, Iter& end_iter, size_t width=90)
{
  // 분포 평면(distribution plot)을 그리기 위한 데이터 생성
  std::map<int, size_t> plot_data;                 // 원소는 pair<value, frequency>

  // 모든 값이 평면(plot) 안에 있는지 확인
  auto pr = std::minmax_element(beg_iter, end_iter, [](const double v1, const double v2) 
                                                      { return v1 < v2; });
  for(int n {static_cast<int>(*pr.first)}; n < static_cast<int>(*pr.second); ++n)
    plot_data.emplace(n,0);

  // 평면 데이터를 생성
  std::for_each(beg_iter, end_iter,
    [&plot_data](double value) { ++plot_data[static_cast<int>(std::round(value))]; });

  // 평면에 그릴 최대 빈도 찾기 - 반드시 페이지 너비 안에 맞춰야 한다
  size_t max_f {std::max_element(std::begin(plot_data), std::end(plot_data),
    [](const std::pair<int,int>& v1, const std::pair<int,int>& v2)
                            { return v1.second < v2.second; })->second};

  // 분포를 히스토그램으로 그리기
  std::for_each(std::begin(plot_data), std::end(plot_data),
    [max_f, width](const std::pair<int, int>& v)
  {std::cout << std::setw(3) << v.first << " -| " 
                             << string((width*v.second) / max_f, '*') << std::endl; });
}


int main()
{
  std::random_device rd;
  std::default_random_engine rng {rd()};
  std::normal_distribution<> norm;
  double mu {}, sigma {};
  const size_t sample_count{20000};
  std::vector<double> values(sample_count);
  while(true)
  {
    std::cout << "\nEnter values for the mean and standard deviation, or Ctrl+Z to end: ";
    if((std::cin >> mu).eof()) break;
    std::cin >> sigma;
    norm.param(Params{mu, sigma});
    std::generate(std::begin(values), std::end(values), [&norm, &rng]{ return norm(rng); });

    // 히스토그램을 그릴 데이터를 생성
    dist_plot(std::begin(values), std::end(values));

    // 생성된 랜덤 값에 적용할 평균과 표준편차를 구한다 
    double mean {std::accumulate(std::begin(values), std::end(values), 0.0)/ values.size()};

    std::transform(std::begin(values), std::end(values), std::begin(values),
                   [&mean](double value) { return std::pow(value - mean,2); });
    double s_dev {std::sqrt(std::accumulate(std::begin(values), 
                                       std::end(values), 0.0) /(values.size() - 1))};
    std::cout << "For generated values, mean = " << mean 
              << " standard deviation = " << s_dev << std::endl;
  }
}