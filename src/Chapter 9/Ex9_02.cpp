// Ex9_02.cpp
// Using output stream iterator function members
#include <iostream>                                      // 표준 스트림
#include <iterator>                                      // 반복자, begin(), end()
#include <vector>                                        // vector 컨테이너
#include <algorithm>                                     // copy() 알고리즘
#include <string>
using std::string;

int main()
{
  std::vector<string> words {"The", "quick", "brown", "fox", "jumped", "over", "the", "lazy", "dog"};

  // 일반적인 반복자 표기법을 사용해 words 컨테이너에 쓰기
  std::ostream_iterator<string> out_iter1 {std::cout};   // 출력 구분자 없는 반복자
  for(const auto& word : words)
  {
    *out_iter1++ = word;                                 // 단어를 쓰기
    *out_iter1++ = " ";                                  // 구분자를 쓰기
  }
  *out_iter1++ = "\n";                                   // 새 줄을 쓰기

  // 다시 반복자를 사용해서 words 컨테이너에 쓰기
  for(const auto& word : words)
  {
    (out_iter1 = word) = " ";                            // 단어와 구분자를 쓰기 
  }
  out_iter1 = "\n";                                      // 새 줄을 쓰기

  // copy()를 사용해 words 컨테이너에 쓰기
  std::ostream_iterator<string> out_iter2 {std::cout, " "};
  std::copy(std::begin(words), std::end(words), out_iter2);
  out_iter2 = "\n";
}
