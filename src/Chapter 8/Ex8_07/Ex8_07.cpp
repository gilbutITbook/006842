// Ex8_07.cpp
// 이산분포를 사용해 주사위 던지기 게임을 구현하는 예제
#include <random>                              // discrete_distribution, 랜덤 넘버 생성기
#include <array>                               // array 컨테이너
#include <utility>                             // pair 타입
#include <algorithm>                           // count(), remove()
#include <iostream>                            // 표준 스트림
#include <iomanip>                             // 스트림 조작자
#include "Die.h"                               // 주사위를 정의한 클래스

// 프로그램 코드 전체에서 사용할 랜덤 넘버 생성기
std::default_random_engine& rng()
{
  static std::default_random_engine engine {std::random_device()()};
  return engine;
}

int main()
{
  size_t n_games {};                                       // 플레이한 게임의 횟수
  const size_t n_dice {4};                                 // 주사위의 개수

  std::array<Die, n_dice> dice                             // 주사위
  {
    Die {3, 3, 3, 3, 3, 3},
    Die {0, 0, 4, 4, 4, 4},
    Die {1, 1, 1, 5, 5, 5},
    Die {2, 2, 2, 2, 6, 6}
  };

  std::cout <<
     "For each game, select a die from the following by entering 1, 2, 3, or 4 (or Ctrl+Z to end):\n"
            << "die 1: 3 3 3 3 3 3\n"
            << "die 2: 0 0 4 4 4 4\n"
            << "die 3: 1 1 1 5 5 5\n"
            << "die 4: 2 2 2 2 6 6\n";

  size_t you {}, me {};                                    // 내 주사위와 상대방 주사위의 인덱스를 저장

  while(true)
  {
    std:: cout << "\nChoose a die: ";
    if((std::cin >> you).eof()) break;                     // EOF - 모든 것이 끝남

    if(you == 0 || you > n_dice)                           // 1부터 4까지만 선택할 수 있음
    {
      std::cout << "Selection must be from 1 to 4, try again.\n";
      continue;
    }

    // 내 주사위를 순차열에서 다음 순서로 선택한다
    me = you-- % n_dice;                                   // 상대방은 0부터 3, 나는 you + 1 mod 4
    std::cout << "I'll choose:  " << (me+1) << std::endl;


    // 주사위 던지기
    const size_t n_throws {15};
    std::array<std::pair<size_t, size_t>, n_throws> goes; // 진행 결과 - pair<me_value, you_value>
    std::generate(std::begin(goes), std::end(goes),       // 주사위를 던진다
      [&dice, me, you] { return std::make_pair(dice[me].throw_it(), dice[you].throw_it()); });

    // 게임 결과를 출력한다
    std::cout << "\nGame " << ++n_games << ":\n";

    // 내 던지기 결과를 출력...
    std::cout << "Me : ";
    std::for_each(std::begin(goes), std::end(goes),
      [](const std::pair<size_t, size_t>& pr)
    {  std::cout << std::setw(3) << pr.first; });
    auto my_wins = std::count_if(std::begin(goes), std::end(goes), 
                                                     [](const std::pair<size_t, size_t>& pr)
                                                     { return pr.first > pr.second; });
    std::cout << " My wins:   " << std::setw(2) <<  std::right << my_wins 
              << "   I " << ((my_wins > n_throws / 2) ? "win!!" : "lose {:-(")
              << std::endl;

    // 상대방의 던지기 결과를 출력 - 내 결과 밑에 정렬해서 출력한다
    std::cout << "You: ";
    std::for_each(std::begin(goes), std::end(goes), [](const std::pair<size_t, size_t>& pr)
                                              { std::cout << std::setw(3) << pr.second; });
    std::cout << " Your wins: " << std::setw(2) << std:: right << n_throws - my_wins 
              << "   You " << ((my_wins <= n_throws / 2) ? "win!!" : "lose!!!") 
              << std::endl;
  }
}
