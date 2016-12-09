// Ex4_04.cpp
// tuple과 pair 사용하기
#include <iostream>                                        // 표준 스트림
#include <iomanip>                                         // 스트림 조작자
#include <string>                                          // string 클래스
#include <cctype>                                          // toupper()
#include <map>                                             // map 컨테이너
#include <vector>                                          // vector 컨테이너
#include <tuple>                                           // tuple 템플릿
#include <algorithm>                                       // sort() 템플릿

using std::string;
using Name = std::pair < string, string >;                 // 이름 pair를 정의
using DOB = std::tuple <size_t, size_t, size_t>;           // 월, 일, 연도 tuple
using Details = std::tuple < DOB, size_t, string > ;       // 출생일(DOB), 키(인치), 직업
using Element_type = std::map<Name, Details>::value_type;  // map 원소의 타입
using People = std::map<Name, Details>;                    // people 컨테이너의 타입

// 표준 입력에서 people 정보를 입력 받기
void get_people(People& people)
{
  string first {}, second {};                              // 이름 입력을 저장
  size_t month {}, day {}, year {};                        // DOB 입력을 저장
  size_t height {};                                        // 키 입력을 저장
  string occupation {};                                    // 직업 입력을 저장
  char answer {'Y'};

  while(std::toupper(answer) == 'Y')
  {
    std::cout << "Enter a first name and a second name: ";
    std::cin >> std::ws >> first >> second;

    std::cout << "Enter date of birth as month day year (integers): ";
    std::cin >> month >> day >> year;
    DOB dob {month, day, year};                            // DOB tuple을 생성

    std::cout << "Enter height in inches: ";
    std::cin >> height; 
    
    std::cout << "Enter occupation: ";
    std::getline(std::cin >> std::ws, occupation, '\n');

    // Name pair와 tuple 객체를 담는 pair를 맵 원소로 내부에서 생성
    people.emplace(std::make_pair(Name {first, second}, std::make_tuple(dob, height, occupation)));

    std::cout << "Do you want to enter another(Y or N): ";
    std::cin >> answer;
  }
}

// 이름, 출생일(date-of-birth, DOB), 직업를 출력
void list_DOB_Job(const People& people)
{
  DOB dob;
  string occupation {};
  std::cout << '\n';
  for(auto iter = std::begin(people); iter != std::end(people); ++iter)
  {
    std::tie(dob, std::ignore, occupation) = iter->second;
    std::cout << std::setw(20) << std::left << (iter->first.first + " " + iter->first.second)
      << "DOB: " << std::right << std::setw(2) << std::get<0>(dob) << "-"
      << std::setw(2) << std::setfill('0') << std::get<1>(dob) << "-"
      << std::setw(4) << std::get<2>(dob) << std::setfill(' ')
      << "  Occupation: " << occupation << std::endl;
  }
}

// 함수 객체로 결정해서 선택한 순차열에 있는 맵 원소를 출력
template<typename Compare>
void list_sorted_people(const People& people, Compare comp)
{
  std::vector<const Element_type*> folks;
  for(const auto& pr : people)
    folks.push_back(&pr);

  // 포인터로 원소들을 비교하는 람다
  auto ptr_comp = 
       [&comp](const Element_type* pr1, const Element_type* pr2)->bool
              {  return comp(*pr1, *pr2);  };

  std::sort(std::begin(folks), std::end(folks), ptr_comp); // 원소에 대한 포인터를 정렬

  // 정렬된 원소들을 출력
  DOB dob {};
  size_t height {};
  string occupation {};
  std::cout << '\n';

  for(const auto& p : folks) 
  {
    std::tie(dob, height, occupation) = p->second;
    std::cout << std::setw(20) << std::left << (p->first.first + " " + p->first.second)
      << "DOB: " << std::right << std::setw(2) << std::get<0>(dob) << "-"
      << std::setw(2) << std::setfill('0') << std::get<1>(dob) << "-"
      << std::setw(4) << std::get<2>(dob) << std::setfill(' ')
      << "  Height: " << height
      << "  Occupation: " << occupation << std::endl;
  }
}

int main()
{
  std::map<Name, Details> people;                     // people의 레코드
  get_people(people);                                 // people을 모두 읽는다

  std::cout << "\nThe DOB & jobs are: \n";
  list_DOB_Job(people);                               // 이름, 출생일, 직업을 출력

  // 사람들을 키로 비교하는 걸로 정의
  auto comp = [](const Element_type& pr1, const Element_type& pr2)
  {
    return std::get<1>(pr1.second) < std::get<1>(pr2.second);
  };

  std::cout << "\nThe people in height order are : \n";
  list_sorted_people(people, comp);
}
