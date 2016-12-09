// Ex8_03.cpp
// 분포로 임의로 카드를 다루기
#include <iostream>                                      // 표준 스트림
#include <ostream>                                       // ostream 스트림
#include <iomanip>                                       // 스트림 조작자
#include <iterator>                                      // 반복자, begin(), end()
#include <random>                                        // 랜덤 넘버 생성기와 분포
#include <utility>                                       // pair<T1,T2> 템플릿
#include <vector>                                        // vector<T> 컨테이너
#include <list>                                          // list<T> 컨테이너
#include <array>                                         // array<T,N> 컨테이너
#include <string>                                        // string 클래스
#include <type_traits>                                   //  is_same 조건자


using std::string;
enum class Suit : size_t { Clubs, Diamonds, Hearts, Spades };
enum class Face : size_t { Two, Three, Four, Five, Six, Seven, 
                           Eight, Nine, Ten, Jack, Queen, King, Ace };
using Card = std::pair<Suit,Face>;                       // 카드를 위한 타입
using Hand = std::list<Card>;                            // 손에 쥔 카드를 위한 타입
using Deck = std::list<Card>;                            // 카드 덱을 위한 타입
using Hands = std::vector<Hand>;                         // 손에 쥔 카드 컨테이너를 위한 타입
using Range = std::uniform_int_distribution<size_t>::param_type;

// Card 객체를 위한 스트림 삽입(<<) 연산자
std::ostream& operator<<(std::ostream& out, const Card& card)
{
  static std::array<string, 4> suits { "C", "D", "H", "S" };              // 카드 문양 이름
  static std::array<string, 13> values { "2", "3", "4", "5", "6", "7",    // 카드 끗수 이름
                                         "8", "9", "10", "J", "Q", "K", "A" };
  string suit { suits[static_cast<size_t>( card.first )] };
  string value { values[static_cast<size_t>( card.second )] };
  return out << std::setw(2) << value << suit;
}

// 프로그램 코드 전체에서 사용할 수 있는 랜덤 넘버 생성기
std::default_random_engine& rng()
{
  static std::default_random_engine engine {std::random_device()()};
  return engine;
}

// 프로그램 코드 전체에서 사용할 수 있는 int 타입을 위한 균등 분포 객체
std::uniform_int_distribution<size_t>& dist()
{
  static std::uniform_int_distribution<size_t> d ;
  return d;
}

// 52장의 카드 전체 세트를 덱으로 초기화
Deck& init_deck(Deck& deck)
{
  static std::array<Suit,4> suits{ Suit::Clubs, Suit::Diamonds, Suit::Hearts, Suit::Spades };
  static std::array<Face, 13> values { Face::Two,   Face::Three, Face::Four, Face::Five, Face::Six,
                                       Face::Seven, Face::Eight, Face::Nine, Face::Ten,
                                       Face::Jack,  Face::Queen, Face::King, Face::Ace };
  deck.clear();
  for(const auto& suit : suits)
    for(const auto& value : values)
    deck.emplace_back(Card {suit, value});
  return deck;
}

// 전체 덱을 딜(deal)한다
void deal(Hands& hands, Deck& deck)
{
  auto d = dist();
  while(!deck.empty())
  {
    for(auto&& hand : hands)
    {
      size_t max_index = deck.size() - 1;
      d.param(Range{0, max_index});
      auto iter = std::begin(deck);
      std::advance(iter, d(rng()));
      hand.push_back(*iter);
      deck.erase(iter);
    }
  }
}

// 손에 쥔 카드를 카드 순서로 정렬
void sort_hands(Hands& hands)
{
  for(auto&& hand : hands)
    hand.sort([](const auto& crd1, const auto crd2) { return crd1.first < crd2.first ||
      (crd1.first == crd2.first && crd1.second < crd2.second); });
}

// 손에 쥔 모든 카드를 출력
void show_hands(const Hands& hands)
{
  for(auto&& hand : hands)
  {
    std::copy(std::begin(hand), std::end(hand), std::ostream_iterator<Card> {std::cout, " "});
    std::cout << std::endl;
  }
}

int main()
{
  // 덱을 생성한다
  Deck deck;
  init_deck(deck);

  // 손(hands)을 만들고 딜한다
  Hands hands(4);
  deal(hands, deck);

  // 손에 든 카드를 정렬하고 보여준다
  sort_hands(hands);
  show_hands(hands);
}