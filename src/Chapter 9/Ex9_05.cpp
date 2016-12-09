// Ex9_05.cpp
// 스트림 반복자를 사용해 파일 내용을 복제하기
#include <iostream>                                      // 표준 스트림
#include <fstream>                                       // 파일 스트림
#include <iterator>                                      // 반복자, begin(), end()
#include <string>                                        // string 클래스
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
  string file_out {"dictionary_copy.txt"};
  std::ofstream out {file_out, std::ios_base::out | std::ios_base::trunc };
  std::copy(std::istream_iterator<string> {in}, std::istream_iterator<string> {},
                                                std::ostream_iterator<string> {out, " "});
  in.clear();                                              // EOF를 정리
  std::cout << "Original file length: " << in.tellg() << std::endl;
  std::cout << "File copy length: " << out.tellp() << std::endl;
  in.close();
  out.close();
}
