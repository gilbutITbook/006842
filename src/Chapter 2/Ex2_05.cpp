// Ex2_05.cpp
// 리스트로 작업하기
#include <iostream>
#include <list>
#include <string>
#include <functional>

using std::list;
using std::string;

// 범위로 지정된 원소들을 나열하기
template<typename Iter>
void list_elements(Iter begin, Iter end)
{
  while (begin != end)
    std::cout << *begin++ << std::endl;
}

int main()
{
  std::list<string> proverbs;

  // 속담을 읽어들이기
  std::cout << "Enter a few proverbs and enter an empty line to end:" << std::endl;
  string proverb;
  while (getline(std::cin, proverb, '\n'), !proverb.empty())
    proverbs.push_front(proverb);

  std::cout << "Go on, just one more:" << std::endl;
  getline(std::cin, proverb, '\n');
  proverbs.emplace_back(proverb);

  std::cout << "\nThe elements in the list in reverse order are:" << std::endl;
  list_elements(std::rbegin(proverbs), std::rend(proverbs));

  proverbs.sort();                               // 속담을 오름차순으로 정렬
  std::cout << "\nYour proverbs in ascending sequence are:" << std::endl;
  list_elements(std::begin(proverbs), std::end(proverbs));

  proverbs.sort(std::greater<>());            // 속담을 내림차순으로 정렬
  std::cout << "\nYour proverbs in descending sequence:" << std::endl;
  list_elements(std::begin(proverbs), std::end(proverbs));
}
