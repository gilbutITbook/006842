// Ex9_04.cpp
// 사전 파일을 다시 읽으면서 단어의 애너그램을 찾기

#include <iostream>                                      // 표준 스트림
#include <fstream>                                       // 파일 스트림
#include <iterator>                                      // 반복자, begin(), end()
#include <string>                                        // string 클래스
#include <set>                                           // set 컨테이너
#include <vector>                                        // vector 컨테이너
#include <algorithm>                                     // next_permutation()
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
  auto end_iter = std::istream_iterator<string> {};

  std::vector<string> words;
  string word;
  while(true)
  {
    std::cout << "\nEnter a word, or Ctrl+z to end: ";
    if((std::cin >> word).eof()) break;
    string word_copy {word};
    do
    {
      in.seekg(0);                                              // 파일은 시작 위치로

      // find() 알고리즘을 사용해 애너그램 검사에 필요한 파일을 읽는다
      if(std::find(std::istream_iterator<string>(in), end_iter, word) != end_iter)
        words.push_back(word);
      else
        in.clear();                                             // EOF 초기화

      std::next_permutation(std::begin(word), std::end(word));
    } while(word != word_copy);

    std::copy(std::begin(words), std::end(words), std::ostream_iterator<string>{std::cout, " "});
    std::cout << std::endl;
    words.clear();                                              // 이전 순열을 제거
  }
  in.close();                                                   // 파일 닫기
}
