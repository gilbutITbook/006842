// Ex9_09.cpp
// 스트림 버퍼 반복자를 사용해 파일을 복제하는 예제
#include <iostream>                                        // 표준 스트림
#include <iterator>                                        // 반복자, begin(), end()
#include <fstream>                                         // 파일 스트림
#include <string>                                          // string 클래스
using std::string;

int main()
{
  string file_name {"dictionary.txt"};
  std::ifstream file_in {file_name};
  if(!file_in)
  {
    std::cerr << file_name << " not open." << std::endl;
    exit(1);
  }
  string file_copy {"dictionary_copy.txt"};
  std::ofstream file_out {file_copy, std::ios_base::out | std::ios_base::trunc};

  std::istreambuf_iterator<char> in {file_in};             // 입력 스트림 버퍼 반복자
  std::istreambuf_iterator<char> end_in;                   // 끝 스트림 버퍼 반복자
  std::ostreambuf_iterator<char> out {file_out};           // 출력 스트림 버퍼 반복자
  while(in != end_in)
    out = *in++;                                           // in에서 out으로 문자를 복제

  std::cout << "File copy completed." << std::endl;

  file_in.close();                                         // 파일 닫기
  file_out.close();                                        // 파일 닫기
}
