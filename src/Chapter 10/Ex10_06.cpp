// Ex10_06.cpp
// complex 객체를 사용해 쥘리아 집합의 프랙탈 이미지를 생성하는 예제
#include <iostream>                                      // 표준 스트림
#include <iomanip>                                       // 스트림 조작자
#include <complex>                                       // complex 타입
#include <chrono>                                        // 클록, duration, time_point
using std::complex;
using namespace std::chrono;
using namespace std::literals;

// time_point<>에 대해 정확한 시간 간격을 초 단위로 출력한다
template<typename TimePoint>
void print_timepoint(const TimePoint& tp, size_t places = 0)
{
  auto elapsed = tp.time_since_epoch();          // 시간 간격을 위한 duration 객체

  auto seconds = duration_cast<duration<double>>(elapsed).count();
  std::cout << std::fixed << std::setprecision(places) << seconds << " seconds\n";
}

int main()
{
  const int width {100}, height {100};                     // 이미지 폭과 높이
  size_t count {100};                                      // 재귀를 위한 반복 카운트
  char image[width][height];
  auto start_time = steady_clock::now();                   // 시작 시점을 위한 time_point 객체
  complex<double> c {-0.7, 0.27015};                       // z = z*z + c에서 상수 c 선언

  for(int i {}; i < width; ++i)                            // 픽셀을 width에 대해 반복
  {
    for(int j {}; j < height; ++j)                         // 픽셀을 height에 대해 반복
    {
      // -1과 +1 사이의 실수부와 허수부의 스케일(확대/축소)
      auto re = 1.5*(i - width/2) / (0.5*width);
      auto im = (j - height/2) / (0.5*height);
      complex<double> z {re,im};                           // 복소 평면의 점
      image[i][j] = ' ';                                   // 쥘리아 집합이 아닌 점
      // z=z*z+c 카운트 만큼 반복
      for(size_t k {}; k < count; ++k)
      {
        z = z*z + c;
      }
      if(std::abs(z) < 2.0)                                // 점이 여기에 해당한다면...
        image[i][j] = '*';                                 // ...쥘리아 집합에 해당
    }
  }
  auto end_time = std::chrono::steady_clock::now();        // 끝 지점을 위한 time_point 객체
  auto elapsed = end_time - start_time.time_since_epoch();
  std::cout << "Time to generate a Julia set with " << width << "x" << height << " pixels is ";
  print_timepoint(elapsed, 9);

  std::cout << "The Julia set looks like this:\n";
  for(size_t i {}; i < width; ++i)
  {
    for(size_t j {}; j < height; ++j)
      std::cout << image[i][j];
    std::cout << '\n';
  }
}
