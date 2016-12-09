#ifndef QUOTATIONS_H
#define QUOTATIONS_H
#include <vector>                                          // vector 컨테이너
#include <string>                                          // string 클래스
#include <exception>                                       // out_of_range 익셉션

class Quotations
{
private:
  std::vector<std::string> quotes;                         // 명언들을 저장할 컨테이너

public:
  // 문자열 리터럴로 생성된 새 명언을 저장한다
  Quotations& operator<<(const char* quote)
  {
    quotes.emplace_back(quote);
    return *this;
  }

  // string 객체에서 벡터로 새 명언을 복제한다
  Quotations& operator<<(const std::string& quote)
  {
    quotes.push_back(quote);
    return *this;
  }

  // 명언을 벡터로 이동한다
  Quotations& operator<<(std::string&& quote)
  {
    quotes.push_back(std::move(quote));
    return *this; 
  }

  // 인덱스로 지정한 명언을 반환한다
  std::string& operator[](size_t index)
  {
    if(index < quotes.size())
      return quotes[index];
    else
      throw std::out_of_range {"Invalid index to quotations."};
  }

  size_t size() const {  return quotes.size();  }          // 명언의 개수를 반환

  // 명언의 시작 반복자를 반환한다
  std::vector<std::string>::iterator begin()
  {
    return std::begin(quotes);
  }

  // 명언의 const 시작 반복자를 반환한다
  std::vector<std::string>::const_iterator begin() const
  {
    return std::begin(quotes);
  }

  // 명언의 끝 반복자를 반환한다
  std::vector<std::string>::iterator end()
  {
    return std::end(quotes); 
  }

  // 명언의 const 끝 반복자를 반환한다
  std::vector<std::string>::const_iterator end() const
  {
    return std::end(quotes);
  }
};
#endif
