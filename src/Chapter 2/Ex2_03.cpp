// Ex2_03.cpp
// 벡터 컨테이너에서 용량이 어떻게 증가하는지 이해하기
#include <iostream>                             // 표준 스트림
#include <vector>                               // 벡터 컨테이너

int main()
{
  std::vector <size_t> sizes;                    // 원소들의 개수 기록
  std::vector <size_t> capacities;               // 용량 기록
  size_t el_incr {10};                           // 초기 원소 카운트 증가
  size_t incr_count {4 * el_incr};               // 원소 카운트의 증가 개수

  for (size_t n_elements {}; n_elements < incr_count; n_elements += el_incr)
  {
    std::vector<int> values(n_elements);
    std::cout << "\nAppending to a vector with " << n_elements << " initial elements:\n";
    sizes.push_back(values.size());
    size_t space {values.capacity()};
    capacities.push_back(space);

    // 용량이 증가할 때까지 원소들을 추가한다
    size_t count {};                             // 용량 증가 카운트
    size_t n_increases {10};
    while (count < n_increases)
    {
      values.push_back(22);                      // 새 원소를 추가
      if (space < values.capacity())             // 용량이 증가하고...
      {                                          // ...따라서 크기와 용량을 기록
        space = values.capacity();
        capacities.push_back(space);
        sizes.push_back(values.size());
        ++count;
      }
    }
    // 증가가 발생할 때 크기와 용량을 표시
    std::cout << "Size/Capacity: ";
    for (size_t i {}; i < sizes.size(); ++i)
      std::cout << sizes.at(i) << "/" << capacities.at(i) << "  ";
    std::cout << std::endl;
    sizes.clear();                               // 모든 원소 제거
    capacities.clear();                          // 모든 원소 제거
  }
}
