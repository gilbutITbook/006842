// Ex2_06.cpp
// 순방향 리스트 사용하기
#include <algorithm>                             // copy()
#include <iostream>                              // 표준 스트림
#include <forward_list>                          // forward_list 컨테이너
#include <iterator>                              // 스트림 반복자
#include "Box.h"

// 범위로 지정된 원소들을 나열하기
template<typename Iter>
void list_elements(Iter begin, Iter end)
{
  size_t perline {6};                            // 라인 당 출력할 최대 아이템 개수
  size_t count {};                               // 아이템 카운트
  while (begin != end)
  {
    std::cout << *begin++;
    if (++count % perline == 0)
    {
      std::cout << "\n";
    }
  }
  std::cout << std::endl;
}

int main()
{
  std::forward_list<Box> boxes;
  std::copy(std::istream_iterator<Box>(std::cin), std::istream_iterator<Box>(),
                                                                std::front_inserter(boxes));

  boxes.sort();                                    // 상자를 정렬
  std::cout << "\n정렬한 순차열:\n";
  // Box 객체를 보여주는 용도 - ostream 반복자를 사용
  std::copy(std::begin(boxes), std::end(boxes), std::ostream_iterator<Box>(std::cout, " "));
  std::cout << std::endl;

  // 더 많은 상자를 삽입
  std::forward_list<Box> more_boxes {Box {3, 3, 3}, Box {5, 5, 5}, Box {4, 4, 4}, Box {2, 2, 2}};
  boxes.insert_after(boxes.before_begin(), std::begin(more_boxes), std::end(more_boxes));
  std::cout << "더 많은 상자를 삽입한 순차열:\n";
  list_elements(std::begin(boxes), std::end(boxes));

  boxes.sort();                                    // 상자를 정렬
  std::cout << std::endl;
  std::cout << "다시 정렬한 순차열:\n";
  list_elements(std::begin(boxes), std::end(boxes));

  more_boxes.sort();
  boxes.merge(more_boxes);                         // 더 많은 상자를 병합
  std::cout << "more_boxes를 병합한 순차열:\n";
  list_elements(std::begin(boxes), std::end(boxes));

  boxes.unique();
  std::cout << "중복 삭제를 제거한 순차열:\n";
  list_elements(std::begin(boxes), std::end(boxes));

  // 작은 상자를 제거
  const double max_v {30.0};
  boxes.remove_if([max_v](const Box& box){ return box.volume() < max_v; });
  std::cout << "부피가 30 미만인 상제를 제거하고 정렬한 순차열:\n";
  list_elements(std::begin(boxes), std::end(boxes));
}
