// Ex3_02.cpp
// 계산대가 여럿인 마트 시뮬레이션
#include <iostream>                              // 표준 스트림
#include <iomanip>                               // 스트림 조작자
#include <vector>                                // vector 컨테이너
#include <string>                                // string 클래스
#include <numeric>                               // accumulate()
#include <algorithm>                             // min_element와 max_element
#include <random>                                // 무작위 숫자 생성

#include "Customer.h"
#include "Checkout.h"

using std::string;
using distribution = std::uniform_int_distribution<>;

// 서비스 시간을 막대 그래프로 출력
void histogram(const std::vector<int>& v, int min)
{
  string bar (60, '*');                          // 행에 출력할 *
  for (size_t i {}; i < v.size(); ++i)
  {
    std::cout << std::setw(3) << i+min << " "    // 서비스 시간은 index + min
      << std::setw(4) << v[i] << " "             // 발생 횟수 출력
      << bar.substr(0, v[i])                     // ...그리고 * 개수
      << (v[i] > static_cast<int>(bar.size()) ? "...": "")
      << std::endl;
  }
}

int main()
{
  std::random_device random_n;

  // 최소 최대 체크아웃 기간 설정 - 분 단위
  int service_t_min {2}, service_t_max {15};
  distribution service_t_d {service_t_min, service_t_max};

  // 마트 개점 시에 고객의 최소, 최대 숫자를 설정
  int min_customers {15}, max_customers {20};
  distribution n_1st_customers_d {min_customers, max_customers};

  // 고객이 도착하는 시간 간격의 최소, 최대 설정
  int min_arr_interval {1}, max_arr_interval {5};
  distribution arrival_interval_d {min_arr_interval, max_arr_interval};

  size_t n_checkouts {};
  std::cout << "마트 계산대 개수 입력: ";
  std::cin >> n_checkouts;
  if(!n_checkouts)
  {
    std::cout << "계산대 개수는 1 이상이어야 합니다. 1로 설정합니다." << std::endl;
    n_checkouts = 1;
  }

  std::vector<Checkout> checkouts {n_checkouts};
  std::vector<int> service_times(service_t_max-service_t_min+1);

  // 마트 개점할 때 기다리는 고객을 추가
  int count {n_1st_customers_d(random_n)};
  std::cout << "마트 개점 시에 대기 고객 수: " << count << std::endl;
  int added {};
  int service_t {};
  while (added++ < count)
  {
    service_t = service_t_d(random_n);
    std::min_element(std::begin(checkouts), std::end(checkouts))->add(Customer(service_t));
    ++service_times[service_t - service_t_min];
  }

  size_t time {};                                // 경과 시간 저장
  const size_t total_time {600};                 // 시뮬레이션 기간 - 분 단위
  size_t longest_q {};                           // 가장 긴 대기열 길이를 저장

  // 다음 고객이 도착할 때까지의 시간 간격
  int new_cust_interval {arrival_interval_d(random_n)};

  // total_time 분 동안 마트 시뮬레이션을 실행
  while (time < total_time)                      // 시간 만큼 루프 시뮬레이션
  {
    ++time;                                      // 1분씩 증가

    // 도착 간격이 0일 때 새 고객이 도착한다
    if (--new_cust_interval == 0)
    {
      service_t = service_t_d(random_n);         // 고객 서비스 시간을 무작위로 설정
      std::min_element(std::begin(checkouts), std::end(checkouts))->add(Customer(service_t));
      ++service_times[service_t - service_t_min];  // 서비스 시간을 기록한다

      // 가장 긴 대기열의 기록을 업데이트
      for (auto & checkout : checkouts)
        longest_q = std::max(longest_q, checkout.qlength());

      new_cust_interval = arrival_interval_d(random_n);
    }

    // 계산대에서의 시간을 업데이트- 각 큐에 첫 번째 고객을 처리
    for (auto & checkout : checkouts)
      checkout.time_increment();
  }

  std::cout << "최대 대기열 길이 = " << longest_q << std::endl;
  std::cout << "\n서비스 시간 막대 그래프:\n";
  histogram(service_times, service_t_min);

  std::cout << "\n오늘 총 고객 수: "
            << std::accumulate(std::begin(service_times), std::end(service_times), 0)
            << std::endl;
}
