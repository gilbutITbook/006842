// Ex8_02
// seed_seq 객체로 생성한 값
#include <random>                                        // seed_seq, random_device
#include <iostream>                                      // 표준 스트림
#include <iterator>                                      // 반복자
#include <string>                                        // string 클래스
using std::string;

// seed_seq 객체에서 정수를 생성하고 출력한다
void gen_and_list(std::seed_seq& ss, const string title = "Values:", size_t count = 8)
{
  std::vector<unsigned int> values(count);
  ss.generate(std::begin(values), std::end(values));
  std::cout << title << std::endl;
  std::copy(std::begin(values), std::end(values), 
                                       std::ostream_iterator<unsigned int>{std::cout, " "});
  std::cout << std::endl;
}

int main()
{
  std::random_device rd {};                                // 비결정적인 소스 - 희망 사항!
  std::seed_seq seeds1;                                    // 기본 생성자
  std::seed_seq seeds2 {3, 4, 5};                          // 연속 정수에서
  std::seed_seq seeds3 {rd(), rd()};

  std::vector<unsigned int> data {25, 36, 47, 58};             
  std::seed_seq seeds4(std::begin(data), std::end(data));  // 범위에서
  gen_and_list(seeds1, "seeds1");
  gen_and_list(seeds1, "seeds1 again");
  gen_and_list(seeds1, "seeds1 again", 12);
  gen_and_list(seeds2, "seeds2");
  gen_and_list(seeds3, "seeds3");
  gen_and_list(seeds3, "seeds3 again");
  gen_and_list(seeds4, "seeds4");
  gen_and_list(seeds4, "seeds4 again");
  gen_and_list(seeds4, "seeds4 yet again", 12);
  gen_and_list(seeds4, "seeds4 for the last time", 6);
}
