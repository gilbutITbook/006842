// Ex8_04.cpp
// 막대기를 던져서 π를 구하기
#include <iostream>                                             // 표준 스트림
#include <random>                                               // 분포, 랜덤 넘버 생성기
#include <cmath>                                                // sin() 함수

int main()
{
  const double pi = 3.1415962;
  double stick_length{};                                        // 막대기 길이
  double board_width {};                                        // 마루판 너비

  std::cout << "마룻바닥의 너비를 입력하세요: ";
  std::cin >> board_width;
  std::cout << "막대기의 길이를 입력하세요(마룻바닥의 너비 " << board_width << "보다 작아야 함): ";
  std::cin >> stick_length;
  if(board_width < stick_length) stick_length = 0.9*board_width;

  std::uniform_real_distribution<> angle {0.0, pi};             // 막대기 각도의 분포

  // 막대기 중심 위치의 분포, 마루판의 가장자리를 기준으로
  std::uniform_real_distribution<> position {0.0, board_width}; 

  std::random_device rd;                                        // 비결정적인 시드 소스
  std::default_random_engine rng {rd()};                        // 랜덤 넘버 생성기를 만든다
  const size_t throws{5'000'000};                               // 랜덤 던지기의 횟수
  size_t hits {};                                               // 마루판을 교차하는 막대기의 개수

  // 막대기를 throws 횟수만큼 던진다
  for(size_t i {}; i < throws; ++i)
  {
    double y {position(rng)};
    double theta {angle(rng)};
    // 막대기가 마루판의 가장자리에 교차하는지 검사
    if(((y + stick_length*sin(theta)/2) >= board_width) || ((y - stick_length*sin(theta) / 2) <= 0))
      ++hits;                                                    // 교차하면 카운트를 증가
  }

  std::cout << "마루판의 가장자리를 교차하는 막대기의 확률: "
              << (static_cast<double>(hits)/ throws) << std::endl;
  std::cout << "파이 값: " << (2* stick_length*throws)/(board_width*hits) << std::endl;
}
