// 마트 계산대 - 대기열에 있는 고객에 대해 스마트 포인터를 사용
#ifndef CHECKOUT_H
#define CHECKOUT_H
#include <queue>                                 // queue 컨테이너
#include <memory>                                // 스마트 포인터
#include "Customer.h"
using PCustomer = std::unique_ptr<Customer>;

class Checkout
{
private:
  std::queue<PCustomer> customers;                // 계산을 기다리는 대기열

public:
  void add(PCustomer&& customer) { customers.push(std::move(customer)); }
  size_t qlength() const { return customers.size(); }

  // 1분씩 대기 시간을 증가시킨다
  void time_increment()
  {
    if (customers.front()->time_decrement().done())  // 고객이 계산을 끝냈으면...
      customers.pop();                               // ...대기열에서 제거한다
  };

  bool operator<(const Checkout& other) const { return qlength() < other.qlength(); }
  bool operator>(const Checkout& other) const { return qlength() < other.qlength(); }
};
#endif
