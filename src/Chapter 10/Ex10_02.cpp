// Ex10_02.cpp
// valarray 객체를 사용해 높은 빌딩에서 벽돌을 안전하게 떨어뜨리는 예제
#include <numeric>                                       // iota()
#include <iostream>                                      // 표준 스트림
#include <iomanip>                                       // 스트림 조작자
#include <algorithm>                                     // for_each()
#include <valarray>                                      // valarray
const static double g {32.0};                            // 중력 가속도에 의한 가속도

int main()
{
  double height {};                                      // 건물 높이
  std::cout << "Enter the approximate height of the building in feet: ";
  std::cin >> height;

  // 벽돌이 떨어지는 시간을 초(sec)로 계산
  double end_time {std::sqrt(2 * height / g)};
  size_t max_time {1 + static_cast<size_t>(end_time + 0.5)};

  std::valarray<double> times(max_time+1);               // 시간을 담을 배열
  std::iota(std::begin(times), std::end(times), 0);      // 초기화: 0 to max_time
  *(std::end(times) - 1) = end_time;                     // 마지막 시간 값을 설정

  // 매 초당 거리를 계산
  auto distances = times.apply([](double t) { return 0.5*g*t*t; });

  // 매 초당 속도를 계산 
  auto v_fps = sqrt(distances.apply([](double d) { return 2 * g*d;}));

  // 결과 출력을 위한 람다 표현식
  auto print = [](double v) { std::cout << std::setw(6) << static_cast<int>(std::round(v)); };

  // 시간을 출력 - 마지막 값은 특별한 케이스로 처리...
  std::cout << "Time (seconds): ";
  std::for_each(std::begin(times), std::end(times)-1, print);
  std::cout << std::setw(6) << std::fixed << std::setprecision(2) << *(std::end(times)-1);

  std::cout << "\nDistances(feet):";
  std::for_each(std::begin(distances), std::end(distances), print);

  std::cout << "\nVelocity(fps):  ";
  std::for_each(std::begin(v_fps), std::end(v_fps), print);

  // mph(시간당 마일)로 속도를 구하고 출력한다
  auto v_mph = v_fps.apply([](double v) { return v*60/88; });
  std::cout << "\nVelocity(mph):  ";
  std::for_each(std::begin(v_mph), std::end(v_mph), print);
  std::cout << std::endl;
}
