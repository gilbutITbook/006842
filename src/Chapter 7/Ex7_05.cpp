// Ex7_05.cpp
// 몇 가지 알고리즘을 적용해 곡선을 그리는 예제
// 올바른 가로 세로 비로 출력하기 위해
// 표준 출력 스트림 대상에 출력할 문자를 8x8 픽셀 같은 네모틀 폰트로 설정한다.
#include <iostream>                                      // 표준 스트림
#include <iterator>                                      // 반복자, begin(), end()
#include <string>                                        // string 클래스
#include <vector>                                        // vector 컨테이너
#include <algorithm>                                     // 알고리즘
#include <cmath>                                         // sin(), cos()
using std::string;
using Point = std::pair<double, double>;

static const double pi {3.1415926};

// Function template to plot a range of x,y values on cout
template<typename Iterator>
void plot(Iterator begin_iter, Iterator end_iter, string name = "Curve", size_t n_x = 100)
{ // n_x는 문자로 표현한 평면의 폭, 즉, x 축에 출력할 문자의 개수

  // x와 y를 위한 비교 함수
  auto x_comp = [](const Point& p1, const Point& p2) { return p1.first < p2.first; };
  auto y_comp = [](const Point& p1, const Point& p2) { return p1.second < p2.second; };

  // x 값의 최솟값과 최댓값
  auto min_x = std::min_element(begin_iter, end_iter, x_comp)->first;
  auto max_x = std::max_element(begin_iter, end_iter, x_comp)->first;

  // 출력을 위한 간격 길이 - x와 y에 값은 간격을 적용해야 한다
  double step {(max_x - min_x) / (n_x + 1)};

  // y 값의 최솟값과 최댓값
  auto min_y = std::min_element(begin_iter, end_iter, y_comp)->second;
  auto max_y = std::max_element(begin_iter, end_iter, y_comp)->second;

  size_t nrows {1 + static_cast<size_t>(1 + (max_y - min_y)/step)};
  std::vector<string> rows(nrows, string(n_x + 1, ' '));

  // 점들이 범위 안에 있으면 y = 0에 x축을 생성한다
  if(max_y > 0.0 && min_y <= 0.0)
    rows[static_cast<size_t>(max_y/step)] = string(n_x + 1, '-');

  // 점들이 범위 안에 있으면 x = 0에 y축을 생성한다
  if(max_x > 0.0 && min_x <= 0.0)
  {
   size_t x_axis {static_cast<size_t>(-min_x/step)}; 
   std::for_each(std::begin(rows), std::end(rows),
     [x_axis](string& row) { row[x_axis] = row[x_axis] == '-' ? '+' : '|'; });
  }

  std::cout << "\n\n     " << name << ":\n\n";
  // 출력을 위해 행을 생성한다
  auto y {max_y};                             // 현재 출력 행을 위한 y의 상한값
  for(auto& row : rows)
  {
    // Find points to be included in an output row
    std::vector<Point> row_pts;               // 이 행의 점들을 저장한다
    std::copy_if(begin_iter, end_iter, std::back_inserter(row_pts),
    [&y, &step](const Point& p) { return p.second < y + step && p.second >= y; });

    std::for_each(std::begin(row_pts), std::end(row_pts),  // 행에 점들을 위한 *을 설정
    [&row, min_x, step](const Point& p)
                       {row[static_cast<size_t>((p.first - min_x) / step)] = '*'; });
    y -= step;
  }
  // 평면을 출력한다 - 즉, 모든 행을 출력한다
  std::copy(std::begin(rows), std::end(rows), std::ostream_iterator<string>{std::cout, "\n"});
  std::cout << std::endl;
}

// y = sin(x)에서 x 값 0부터 4π에 대해 x, y 점들을 생성한다 
std::vector<Point> sine_curve(size_t n_pts = 100)
{ // n_pts는 곡선에 사용할 데이터 점들의 개수
  std::vector<double> x_values(n_pts);      
  double value {};
  double step {4 * pi / (n_pts - 1)};
  std::generate(std::begin(x_values), std::end(x_values),
    [&value, &step]() { double v {value};
                        value += step;
                        return v; });
  std::vector<Point> curve_pts;
  std::transform(std::begin(x_values), std::end(x_values), std::back_inserter(curve_pts),
    [](double x) { return Point {x, sin(x)}; });
  return curve_pts;
}

// Generate x,y points on a cardioid defined by parametric equations:
// x = a(2cos(t) - cos(2t))  y = a(sin(t) - sin(2t) 
// A cardioid is the path of a point on one circle
// that is rolling around another with the same radius
std::vector<Point> cardioid_curve(double r = 1.0, size_t n_pts = 100)
{ // n_pts는 데이터 점들의 개수
  double step = 2 * pi / (n_pts - 1);                 // x와 y의 간격 길이
  double t_value {};                                  // 곡선 매개변수

  // 곡선을 정의한 매개변수 값들을 생성
  std::vector<double> t_values(n_pts);                
  std::generate(std::begin(t_values), std::end(t_values), 
                                      [&t_value, step]() { auto value = t_value;
                                                           t_value += step;
                                                           return value; });

  // t에 대해 심장형 곡선의 x, y 점을 정의하는 함수
  auto cardioid = [r](double t)
                  { return Point {r*(2*cos(t) + cos(2*t)), r*(2*sin(t) + sin(2*t))}; };

  // 심장형 곡선의 점들을 생성한다
  std::vector<Point> curve_pts;
  std::transform(std::begin(t_values), std::end(t_values), std::back_inserter(curve_pts),
                                                           cardioid);
  return curve_pts;
}

int main()
{
  auto curve1 = sine_curve(50);
  plot(std::begin(curve1), std::end(curve1), "Sine curve", 90);
  auto curve2 = cardioid_curve(1.5, 120);
  plot(std::begin(curve2), std::end(curve2), "Cardioid", 60);
}