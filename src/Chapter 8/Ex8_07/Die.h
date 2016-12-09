#ifndef DIE_H
#define DIE_H
#include <random>                                        // discrete_distribution, 랜덤 넘버 생성기
#include <vector>                                        // vector 컨테이너
#include <algorithm>                                     // remove()
#include <iterator>                                      // 반복자, begin(), end()

// 이산분포의 param_type을 위한 별칭
using Params = std::discrete_distribution<size_t>::param_type;

std::default_random_engine& rng(); 

// 임의의 값을 갖는 6면 주사위를 표현한 클래스
// 눈의 값이 유일할 필요는 없다
class Die
{
public:
  Die() { values.push_back(0); };

  // 생성자
  Die(std::initializer_list<size_t> init)
  {
    std::vector<size_t> faces {init};                      // 주사위 눈의 값을 저장
    auto iter = std::begin(faces);
    auto end_iter = std::end(faces);
    std::vector<size_t> wts;                               // 눈의 값에 대한 가중치를 저장
    while(iter != end_iter)
    {
      values.push_back(*iter);
      wts.push_back(std::count(iter, end_iter, *iter));
      end_iter = std::remove(iter, end_iter, *iter++);
    }
    dist.param(Params {std::begin(wts), std::end(wts)});
  }

  size_t throw_it() { return values[dist(rng())]; }

private:
  std::discrete_distribution<size_t> dist;                // 값의 확률 분포
  std::vector<size_t> values;                             // 눈의 값
};
#endif
