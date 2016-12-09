// Ex2_02A.cpp
// vector 컨테이너에 저장된 문자열 정렬하기
#include <iostream>                         // 표준 스트림
#include <string>                           // string 타입
#include <algorithm>                        // swap()과 copy() 함수
#include <vector>                           // 벡터
#include <iterator>                         // 반복자
using std::string;
using std::vector;

// 직접 구현한 알고리즘: 반복자로 지정한 범위를 정렬한다
template<typename RandomIter>
void bubble_sort(RandomIter start, RandomIter last)
{
  std::cout << "정렬을 시작합니다." << std::endl;
  bool out_of_order {false};                // 값들이 정렬되지 않았으면 true
  while (true)
  {
    for (auto first = start + 1; first != last; ++first)
    {
      if (*(first - 1) > *first)
      { // 정렬되지 않았으니 값을 교환한다
        std::swap(*first, *(first - 1));
        out_of_order = true;
      }
    }
    if (!out_of_order)                      // 정렬된 상태이면(교환이 필요 없음)...
      break;                                // ...완료...
    out_of_order = false;                   // ...그렇지 않으면, 다시 반복.
  }
}

int main()
{
  vector<string> words;                     // 정렬할 단어를 저장
  words.reserve(10);                        // 요소들을 위한 공간 할당
  std::cout << "단어는 공백으로 구분해서 입력하세요. 종료하려면 다음 줄에서 Ctrl+Z을 입력하세요:" << std::endl;
  std::copy(std::istream_iterator < string > {std::cin}, std::istream_iterator < string > {},
    std::back_inserter(words));

  bubble_sort(std::begin(words), std::end(words));  // Sort the words array

  // 정렬된 벡터를 출력
  std::cout << "오름차순으로 정렬된 단어:" << std::endl;
  std::copy(std::begin(words), std::end(words), std::ostream_iterator < string > {std::cout, " "});
  std::cout << std::endl;

  // words 벡터에서 요소들을 이동해서 새 벡터를 생성
  vector<string> words_copy {std::make_move_iterator(std::begin(words)),
    std::make_move_iterator(std::end(words))};
  std::cout << "\nwords에서 요소들을 이동한 후에 words_copy의 내용:" << std::endl;
  std::copy(std::begin(words_copy), std::end(words_copy),  std::ostream_iterator < string > {std::cout, " "});
  std::cout << std::endl;

  // words 벡터의 요소들에 무슨 일이 일어났는지 알아보기...
  std::cout << "\nwords 벡터는 요소 " << words.size() << "개를 갖고 있습니다\n";
  if (!words.front().length())
    std::cout << "첫 번째 요소는 빈 문자열 객체입니다." << std::endl;

  std::cout << "첫 번째 요소는 \"" << words.front() <<  "\"입니다." << std::endl;
}
