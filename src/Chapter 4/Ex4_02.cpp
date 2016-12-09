// Ex4_02.cpp 
// 단어 빈도수 알아내기
#include <iostream>                               // 표준 스트림
#include <iomanip>                                // 스트림 조작자
#include <string>                                 // string 클래스
#include <sstream>                                // istringstream
#include <algorithm>                              // replace_if(), for_each()
#include <map>                                    // map 컨테이너
#include <cctype>                                 // isalpha()
#include <iterator>                               // istream_iterator

using std::string;

int main()
{
  std::cout << "Enter some text and enter * to end:\n";
  string text_in {};
  std::getline(std::cin, text_in, '*');

  // 비알파벳 문자는 공백으로 치환한다
  std::replace_if(std::begin(text_in), std::end(text_in),
                                                 [](const char& ch){ return !isalpha(ch); }, ' ');

  std::istringstream text(text_in);             // 텍스트 입력 문자열을 스트림으로
  std::istream_iterator<string> begin(text);    // 스트림 반복자 
  std::istream_iterator<string> end;            // 끝 스트림 반복자

  std::map<string, size_t> words;               // 단어와 단어 빈도를 저장할 맵
  size_t max_len {};                            // 단어 최대 길이

  // 단어를 가져와 맵에 저장하고 최대 길이를 찾는다
  std::for_each(begin, end, [&max_len, &words](const string& word)
                            {  words[word]++;
                               max_len = std::max(max_len, word.length());
                            });

  // 단어와 단어 빈도를 출력한다
  size_t per_line {4}, count {};
  for(const auto& w : words)
  {
    std::cout << std::left << std::setw(max_len + 1) << w.first
              << std::setw(3) << std::right << w.second << "  ";

    if(++count % per_line == 0)  std::cout << std::endl;
  }
  std::cout << std::endl;
}  
