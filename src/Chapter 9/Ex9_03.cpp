// Ex9_03.cpp
// 단어의 애너그램을 찾는 예제
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
  // 파일의 단어들을 set 컨테이너로 읽어들인다
  string file_in {"dictionary.txt"};
  std::ifstream in {file_in};
  if(!in)
  {
    std::cerr << file_in << " not open." << std::endl;
    exit(1);
  }
  std::set<string> dictionary {std::istream_iterator<string>(in), 
                               std::istream_iterator<string>()};
  std::cout << dictionary.size() << " words in dictionary." << std::endl;

  std::vector<string> words;
  string word;
  while(true)
  {
    std::cout << "\nEnter a word, or Ctrl+z to end: ";
    if((std::cin >> word).eof()) break;
    string word_copy {word};
    do
    {
      if(dictionary.count(word))
        words.push_back(word);
      std::next_permutation(std::begin(word), std::end(word));
    } while(word != word_copy);

    std::copy(std::begin(words), std::end(words), 
                std::ostream_iterator<string>{std::cout, " "});
    std::cout << std::endl;
    words.clear();                                              // 이전 순열을 제거
  }
  in.close();                                                   // 파일 닫기
}
