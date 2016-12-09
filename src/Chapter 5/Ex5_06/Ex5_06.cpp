// Ex5_06.cpp
// unordered_multiset 컨테이너 사용 예제
#include <iostream>                              // 표준 스트림
#include <iomanip>                               // 스트림 조작자
#include <string>                                // string 클래스
#include <unordered_set>                         // unordered_multiset 컨테이너
#include <algorithm>                             // copy(), max(), find_if(), for_each()
#include <iterator>                              // ostream_iterator

  
#include "Name.h"
#include "Hash_Name.h"

using std::string;
using std::ostream_iterator;
using Names = std::unordered_multiset<Name, Hash_Name>;

// Create the elements representing friends
void make_friends(Names& names)
{
  // 중복 원소를 가져오면 중복 이름이 생성된다
  std::vector<string> first_names {"John", "John", "John", "Joan", "Joan", "Jim", "Jim", "Jean"};
  std::vector<string> second_names {"Smith", "Jones", "Jones", "Hackenbush", "Szczygiel"};

  for(const auto& name1 : first_names)
    for(const auto& name2 : second_names)
      names.emplace(name1, name2);
}

// List the container elements within bucket
void list_buckets(const Names& names)
{
  for(size_t n_bucket {} ; n_bucket < names.bucket_count(); ++n_bucket)
  {
    std::cout << "Bucket " << n_bucket << ":\n";
    std::copy(names.begin(n_bucket), names.end(n_bucket), std::ostream_iterator < Name > {std::cout, "  "});
    std::cout << std::endl;
  }
}

int main()
{
  Names pals {8};                                     // 8 buckets
  pals.max_load_factor(8.0);                          // Average no. of elements per bucket max
  make_friends(pals);                                 // Load up the container with Name objects
  list_buckets(pals);                                 // List the contents by bucket

  // Report the number of John Smith's that are pals
  Name js {"John", "Smith"};
  std::cout << "\nThere are " << pals.count(js) << " " << js << "'s.\n" << std::endl;

  // Remove all the John Jones's - we just don't get on...
  pals.erase(Name {"John", "Jones"});

  // Get rid of the Hackenbushes - they never invite us...
  while(true)
  {
    auto iter = std::find_if(std::begin(pals), std::end(pals),
                               [](const Name& name){ return name.get_second() == "Hackenbush"; });
    if(iter == std::end(pals))
      break;
    pals.erase(iter);
  }

  // List the friends we still have...
  size_t max_length {};                               // Stores the maximum name length
  std::for_each(std::begin(pals), std::end(pals),     // Find the maximum name length
            [&max_length](const Name name){ max_length = std::max(max_length, name.get_length()); });

  size_t count {};                                    // No. of names written out
  size_t perline {6};                                 // No. of names per line
  for(const auto& pal : pals)
  {
    std::cout << std::setw(max_length+2) << std::left << pal;
    if((++count % perline) == 0) std::cout << "\n";
  }
  std::cout << std::endl;
}