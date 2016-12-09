// Ex5_04.cpp 
// 단어 빈도수 알아내기
#include <iostream>                               // 표준 스트림
#include <iomanip>                                // 스트림 조작자
#include <string>                                 // string 클래스
#include <sstream>                                // istringstream
#include <algorithm>                              // replace_if(), for_each()
#include <set>                                    // set 컨테이너
#include <iterator>                               // advance()
#include <cctype>                                 // isalpha()

using std::string;

int main()
{
  std::cout << "Enter some text and enter * to end:\n";
  string text_in {};
  std::getline(std::cin, text_in, '*');

  // 알파벳을 제외한 문자를 공백으로 바꾼다
  std::replace_if(std::begin(text_in), std::end(text_in), [](const char& ch){ return !isalpha(ch); }, ' ');

  std::istringstream text(text_in);             // 텍스트 입력 문자열을 스트림으로 변환
  std::istream_iterator<string> begin(text);    // 스트림 반복자 
  std::istream_iterator<string> end;            // 끝 스트림 반복자

  std::multiset<string> words;                  // 단어를 저장할 컨테이너
  size_t max_len {};                            // 단어 최대 길이

  // 단어를 가져와 컨테이너에 저장하고 최대 길이를 찾는다
  std::for_each(begin, end, [&max_len, &words](const string& word)
                            {  words.emplace(word);
                               max_len = std::max(max_len, word.length());
  });

  size_t per_line {4},                           // 한 줄당 출력할 단어 수
         count {};                               // 단어 출력 개수
  
  for(auto iter = std::begin(words); iter != std::end(words); iter = words.upper_bound(*iter))
  {
    std::cout << std::left << std::setw(max_len + 1) << *iter
              << std::setw(3) << std::right << words.count(*iter) << "  ";
    if(++count % per_line == 0)  std::cout << std::endl;
  }
  std::cout << std::endl;
}
