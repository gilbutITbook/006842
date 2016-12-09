// 마트 계산대 - 대기열에 있는 고객을 관리하고 처리한다
#ifndef CHECKOUT_H
#define CHECKOUT_H
#include <queue>                                 // queue 컨테이너
#include "Customer.h"

class Checkout
{
private:
  std::queue<Customer> customers;                // 계산을 기다리는 대기열(큐)

public:
  void add(const Customer& customer) { customers.push(customer); }
  size_t qlength() const { return customers.size(); }

  // 1분씩 대기 시간을 증가시킨다
  void time_increment() 
  { // 기다리는 고객이 있다면...
    if (!customers.empty())
    { 
      if (customers.front().time_decrement().done()) // 고객이 계산을 끝냈으면...
        customers.pop();                             // ...대기열에서 제거한다
    }
  };

  bool operator<(const Checkout& other) const { return qlength() < other.qlength(); }
  bool operator>(const Checkout& other) const { return qlength() > other.qlength(); }
};
#endif
