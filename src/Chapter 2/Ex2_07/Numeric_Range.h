// Numeric_Range.h for Ex2_07
// 범위를 위한 클래스 템플릿과 범위 지정을 위한 반복자 클래스 템플릿을 정의
#ifndef NUMERIC_RANGE_H
#define NUMERIC_RANGE_H

#include <exception>                             // 표준 익셉션 타입
#include <iterator>                              // 반복자 타입
#include <type_traits>                           // 컴파일 타임 타입 체킹

template <typename T> class Numeric_Iterator;    // 템플릿 타입 정의

// 숫자 범위를 정의
template<typename T>
class Numeric_Range
{
  static_assert(std::is_integral<T>::value || std::is_floating_point<T>::value,
                                 "Numeric_Range type argument must be numeric.");

  friend class Numeric_Iterator <T>;

private:
  T start;                                       // 범위에서 첫 번째 값
  T step;                                        // 연속 값의 증가값
  size_t count;                                  // 범위에 있는 값의 개수

public:
  explicit Numeric_Range(T first=0, T incr=1, size_t n=2) : start {first}, step {incr}, count {n}{}

  // 범위에 대한 시작 반복자를 반환
  Numeric_Iterator<T> begin(){ return Numeric_Iterator<T>(*this); }

  // 범위에 대한 끝 반복자를 반환
  Numeric_Iterator<T> end()
  {
    Numeric_Iterator<T> end_iter(*this);
    end_iter.value = start + count*step;          // 끝 반복자 값은 마지막에서 하나 더 지나간 값
    return end_iter;
  }
};

// 반복자 클래스 템플릿 - 순방향 반복자
template<typename T>
class Numeric_Iterator : public std::iterator <std::forward_iterator_tag, T>
{
  friend class Numeric_Range <T>;

private:
  Numeric_Range<T>& range;                       // 이 반복자 범위에 대한 참조
  T value;                                       // 참조가 가리키는 값

public:
  explicit Numeric_Iterator(Numeric_Range<T>& a_range) : range {a_range}, value {a_range.start} {};

  // 할당 연산자
  Numeric_Iterator& operator=(const Numeric_Iterator& src)
  {
    range = src.range;
    value = src.value;
  }

  // 반복자를 역참조한다
  T& operator*() 
  {
    // 값이 마지막에서 하나 더 뒤라면 이 값은 끝 반복자다
    if (value == static_cast<T>(range.start + range.count*range.step))
    {
      throw std::logic_error("Cannot dereference an end iterator.");
    }
    return value;
  }

  // 전치 증가 연산자
  Numeric_Iterator& operator++()
  {
    // 값이 마지막에서 하나 더 뒤라면 이 값은 끝 반복자다
    if (value == static_cast<T>(range.start + range.count*range.step))
    {
      throw std::logic_error("Cannot increment an end iterator.");
    }
    value += range.step;                         // 범위 스텝만큼 값을 증가
    return *this;
  }

  // 후치 증가 연산자
  Numeric_Iterator operator++(int)
  {
    // 값이 마지막에서 하나 더 뒤라면 이 값은 끝 반복자다
    if (value == static_cast<T>(range.start + range.count*range.step))
    {
      throw std::logic_error("Cannot increment an end iterator.");
    }
    auto temp = *this;
    value += range.step;                         // 범위 스텝만큼 값을 증가
    return temp;                                 // 증가되기 전의 반복자
  }

  // 비교
  bool operator<(const Numeric_Iterator& iter) const { return value < iter.value; }
  bool operator==(const Numeric_Iterator& iter) const { return value == iter.value; }
  bool operator!=(const Numeric_Iterator& iter) const { return value != iter.value; }
  bool operator>(const Numeric_Iterator& iter) const { return value > iter.value; }
  bool operator<=(const Numeric_Iterator& iter) const { *this < iter || *this == iter;}
  bool operator>=(const Numeric_Iterator& iter) const { *this > iter || *this == iter;}
};
#endif
