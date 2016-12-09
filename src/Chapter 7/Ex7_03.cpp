// Ex7_03.cpp
// 단어의 문자들로 모든 조합을 구하기
#include <iostream>                                      // 표준 스트림
#include <iterator>                                      // 반복자, begin(), end()
#include <string>                                        // string 클래스
#include <vector>                                        // vector 컨테이너
#include <algorithm>                                     // next_permutation()
using std::string;

int main()
{
  std::vector<string> words;
  string word;
  while(true)
  {
    std::cout << "\nEnter a word, or Ctrl+z to end: ";
    if((std::cin >> word).eof()) break;
    string word_copy {word};
    do
    {
      words.push_back(word);
      std::next_permutation(std::begin(word), std::end(word));
    } while(word != word_copy);

    size_t count{}, max{8};
    for(const auto& wrd : words)
      std::cout << wrd << ((++count % max == 0) ? '\n' : ' ');
    std::cout << std::endl;
    words.clear();                                         // 이전 순열을 제거
  }
}