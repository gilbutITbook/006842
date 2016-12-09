// Ex9_10.cpp
// 문자열 스트림을 사전 소스로 사용해서 단어의 애너그램을 찾는 예제
#include <iostream>                                      // 표준 스트림
#include <fstream>                                       // 파일 스트림
#include <iterator>                                      // 반복자, begin(), end()
#include <string>                                        // string 클래스
#include <set>                                           // set 컨테이너
#include <vector>                                        // vector 컨테이너
#include <algorithm>                                     // next_permutation()
#include <sstream>                                       // 문자열 스트림
using std::string;

int main()
{
  string file_in {"dictionary.txt"};
  std::ifstream in {file_in};
  if(!in)
  {
    std::cerr << file_in << " not open." << std::endl;
    exit(1);
  }
  std::stringstream instr;                              // 파일 내용을 위한 문자열 스트림
  std::copy(std::istreambuf_iterator<char>{in}, std::istreambuf_iterator<char>(),
                                                std::ostreambuf_iterator<char>{instr});
  in.close();                                           // 파일 닫기

  std::vector<string> words;
  string word;
  auto end_iter = std::istream_iterator<string> {};     // 끝 스트림 반복자
  while(true)
  {
    std::cout << "\nEnter a word, or Ctrl+z to end: ";
    if((std::cin >> word).eof()) break;

    string word_copy {word};
    do
    {
      instr.clear();                                 // 문자열 스트림 EOF 리셋
      instr.seekg(0);                                // 문자열 스트림 위치를 처음으로

                                                     // find()를 사용해 instr에서 word 찾기
      if(std::find(std::istream_iterator<string>(instr), end_iter, word) != end_iter)
        words.push_back(word);                       // 발견한 단어를 저장

      std::next_permutation(std::begin(word), std::end(word));
    } while(word != word_copy);

    std::copy(std::begin(words), std::end(words), std::ostream_iterator<string>{std::cout, " "});
    std::cout << std::endl;
    words.clear();                                   // 이전 애너그램 제거
  }
}
