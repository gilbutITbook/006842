// Ex4_06.cpp
// unordered_map 컨테이너의 버킷 개수가 언제, 어떻게 증가하는지 분석하기
#include <iostream>                                 // 표준 스트림
#include <iomanip>                                  // 스트림 조작자
#include <string>                                   // string 클래스
#include <unordered_map>                            // unordered_map 컨테이너
#include <vector>                                   // vector 컨테이너
#include <algorithm>                                // max_element() 알고리즘

using std::string;
using std::unordered_map;

// 각 버킷에 있는 원소의 개수를 출력
void list_bucket_counts(const std::vector<size_t>& counts)
{
  for(size_t i {}; i < counts.size(); ++i)
  {
    std::cout << "bucket[" << std::setw(2) << i << "] = " << counts[i] << "  ";
    if((i + 1) % 6 == 0) std::cout << '\n';
  }
  std::cout << std::endl;
}

int main()
{
  unordered_map<string, size_t> people;
  float mlf {people.max_load_factor()};             // 현재 최대 로드 팩터
  size_t n_buckets {people.bucket_count()};         // 컨테이너의 버킷 개수

  std::vector<size_t> bucket_counts (n_buckets);    // 버킷당 저장된 원소 개수를 기록
  string name {"Name"};                             // 키 - 값은 나중에 추가됨
  size_t value {};                                  // 원소 값
  size_t max_count {8192};                          // 삽입할 수 있는 원소의 최대 개수
  auto lf = people.load_factor();                   // 현재 로드 팩터
  bool rehash {false};                              // 재해시가 발생할 때를 기록

  while(mlf <= 1.5f)                                // 최대 로드 팩터가 1.5가 될 때까지 루프를 수행
  {
    std::cout << "\n\n***************New Container***************"
              << "\nNumber of buckets: " << n_buckets
              << "  Maximum load factor: " << mlf << std::endl;

    // 컨테이너에 최대 원소까지 삽입
    for(size_t n_elements {}; n_elements < max_count; ++n_elements)
    {
      lf = people.load_factor();                               // 삽입 전 로드 팩터
      people.emplace("name" + std::to_string(++value), value);
      auto new_count = people.bucket_count();                  // 현재 버킷 개수

      if(new_count > n_buckets)                                // 버킷 개수가 증가하면...
      {                                                        // 정보를 출력
        std::cout << "\nBucket count increased to " << new_count
                  << ". Load factor was " << lf << " and is now " << people.load_factor()
                  << "\nMaximum elements in a bucket was "
                  << *std::max_element(std::begin(bucket_counts), std::end(bucket_counts))
                  << std::endl;

        if(n_buckets <= 64)
        {
          std::cout << "Bucket counts before increase were: " << std::endl;
          list_bucket_counts(bucket_counts);
        }

        n_buckets = new_count;                                  // 버킷 개수 업데이트
        bucket_counts = std::vector<size_t> (n_buckets);        // 버킷 개수를 위한 새 벡터
        rehash = true;                                          // 재해시 발생을 기록
      }

      // 현재 버킷 개수를 기록
      for(size_t i {}; i < n_buckets; ++i)
        bucket_counts[i] = people.bucket_size(i);

      if(rehash)                                                // 컨테이너가 재해시되었다면...
      {                                                         // ...정보를 출력
        rehash = false;                                         // 재해시 표시를 초기화

        std::cout << "\nRehashed container. Bucket count is " << n_buckets 
                  << ". Element count is " << people.size()
                  << "\nMaximum element count in a bucket is now "
                  << *std::max_element(std::begin(bucket_counts), std::end(bucket_counts)) 
                  << std::endl;

        if(n_buckets <= 64)                                     // 버킷이 64개라면...
        {
          std::cout << "\nBucket counts after rehash are:\n";
          list_bucket_counts(bucket_counts);
        }
      }
    }

    std::cout << "Final state for this container is:\n"
              << "Bucket count: " << people.bucket_count()
              << "  Element count: " << people.size()
              << "  Maximum element count in a bucket: "
              << *std::max_element(std::begin(bucket_counts), std::end(bucket_counts))
              << std::endl;

    value = 1;                                                  // 키 접미어를 초기화
    people = unordered_map<string, size_t>();                   // 빈 컨테이너를 새로 할당
    n_buckets = people.bucket_count();
    bucket_counts = std::vector < size_t >(n_buckets);          // 버킷 개수를 위한 새 벡터
    mlf += 0.25f;                                               // 최대 로드 팩터 증가...
    people.max_load_factor(mlf);                                // ...컨테이너에 증가 값을 설정
  }
}
