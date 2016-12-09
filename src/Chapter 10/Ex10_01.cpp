// Ex10_01.cpp
// 최소 제곱 회귀
#include <numeric>                                       // accumulate(), inner_product()
#include <vector>                                        // vector 컨테이너
#include <iostream>                                      // 표준 스트림
#include <iomanip>                                       // 스트림 조작자
#include <fstream>                                       // 파일 스트림
#include <iterator>                                      // 반복자, begin(), end()
#include <string>                                        // string 클래스
using std::string;

int main()
{
  // 파일의 내용: country_name renewables_per_person kwh_cost
  string file_in {"renewables_vs_kwh_cost.txt"};
  std::ifstream in {file_in};

  if(!in)                                       // 파일이 있는지 확인
  {
    std::cerr << file_in << " not open." << std::endl;
    exit(1);
  }

  std::vector<double> x;                        // 1인당 재생 에너지
  std::vector<double> y;                        // 킬로와트 시간당 전기 요금

  // 파일을 읽어서 데이터를 보여준다
  std::cout << "   Country   " << " Watts per Head " << " kwh cost(cents) " << std::endl;
  while(true)
  {
    string country;
    double renewables {};
    double kwh_cost {};

    if((in >> country).eof()) break;                           // EOF 읽음 - 완료
    in >> renewables >> kwh_cost;
    x.push_back(renewables);
    y.push_back(kwh_cost);
    std::cout << std::left << std::setw(12) << country         // 레코드를 출력
              << std::right
              << std::fixed << std::setprecision(2) << std::setw(12) << renewables 
              << std::setw(16) << kwh_cost << std::endl;
  }

  auto n = x.size();                                            // 좌표의 개수
  auto sx = std::accumulate(std::begin(x), std::end(x), 0.0);   // x 값들의 합계
  auto sy = std::accumulate(std::begin(y), std::end(y), 0.0);   // y 값들의 합계
  auto mean_x = sx/n;                                           // x 값들의 평균
  auto mean_y = sy/n;                                           // y 값들의 평균

  // x*y 값들의 합계와 x 제곱의 합계
  auto sxy = std::inner_product(std::begin(x), std::end(x), std::begin(y), 0.0);
  auto sx_2 = std::inner_product(std::begin(x), std::end(x), std::begin(x), 0.0);

  double a {}, b {};                                            // 직선 계수
  auto num = n*sxy - sx*sy;                                     // a의 분자
  auto denom = n*sx_2 - sx*sx;                                  // a의 분모
  a = num / denom;
  b = mean_y - a*mean_x;
  std::cout << std:: fixed << std::setprecision(3) << "\ny = "  // 회귀 직션을 위한 
            << a << "*x + " << b << std::endl;                  // 공식을 출력
}
