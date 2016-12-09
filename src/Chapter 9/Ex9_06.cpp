// Ex9_06.cpp
// 스트림 반복자에 count_if()를 사용해 단어 빈도를 세는 예제
#include <iostream>                                        // 표준 스트림
#include <iterator>                                        // 반복자, begin(), end()
#include <iomanip>                                         // 스트림 조작자
#include <fstream>                                         // ifstream
#include <algorithm>                                       // count_if()
#include <string>
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
  string letters {"abcdefghijklmnopqrstuvwxyz"};
  const size_t perline {9};
  for(auto ch : letters)
  {
    std::cout << ch << ": "
      << std::setw(5)
      << std::count_if(std::istream_iterator<string>{in}, std::istream_iterator<string>{},
                                                          [&ch](const string& s)
                                                          { return s[0] == ch; })
      << (((ch - 'a' + 1) % perline) ? " " : "\n");
    in.clear();                                            // EOF를 정리하고...
    in.seekg(0);                                           // ... 처음으로 돌아간다
  }
  std::cout << std::endl;
}
