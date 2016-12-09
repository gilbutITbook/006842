// Ex4_07을 위한 템플릿

// 모든 원소를 출력한다
template<typename Container>
void list_elements(const Container& container)
{
  for(const auto& element : container)
    std::cout << element.first << "  " << element.second << std::endl;
}

// 범위로 지정된 원소들을 출력한다
template<typename T>
void list_range(const T& pr)
{
  if(pr.first != pr.second)
  {
    for(auto iter = pr.first; iter != pr.second; ++iter)
      std::cout << "  " << iter->first << "  " << iter->second << std::endl;
  }
  else
    std::cout << "No records found.\n";
}

// 키보드에서 입력받은 키를 갖는 원소를 찾는다 - C++14 버전
/*
template<typename Container>
auto find_elements(const Container& container)
{
  typename Container::key_type key {};
  std::cin >> key;
  auto pr = container.equal_range(key);
  return pr;
}
*/

// 키보드에서 입력받은 키를 갖는 원소를 찾는다 - C++11 버전
template<typename Container>
auto find_elements(const Container& container) -> std::pair<typename Container::const_iterator, typename Container::const_iterator>
{
  typename Container::key_type key {};
  std::cin >> key;
  auto pr = container.equal_range(key);
  return pr;
}