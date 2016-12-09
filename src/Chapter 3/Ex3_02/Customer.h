// 고객을 계산대까지 남은 시간으로 정의한다
#ifndef CUSTOMER_H
#define CUSTOMER_H
class Customer
{
private:
  size_t service_t {};                           // 계산대까지 남은 시간

public:
  explicit Customer(size_t st = 10) :service_t {st}{}

  // 계산대까지 대기 시간을 감소시킨다
  Customer& time_decrement()
  {
    if(service_t > 0)
      --service_t;
    return *this;
  }
  bool done() const { return service_t == 0; }
};
#endif
