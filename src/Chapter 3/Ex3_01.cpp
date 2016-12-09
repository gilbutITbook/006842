// Ex3_01.cpp

// 스택 컨테이너를 사용한 간단한 계산기

#include <cmath>                                 // pow() 함수
#include <iostream>                              // 표준 스트림
#include <stack>                                 // stack<T> 컨테이너
#include <algorithm>                             // remove()
#include <stdexcept>                             // runtime_error 익셉션
#include <string>                                // string 클래스
using std::string;

// 연산자 우선순위 값을 반환한다
inline size_t precedence(const char op)
{
  if (op == '+' || op == '-')
    return 1;
  if (op == '*' || op == '/')
    return 2;
  if (op == '^')
    return 3;
  throw std::runtime_error {string {"invalid operator in precedence() function: "} + op};
}

// 연산을 실행한다
double execute(std::stack<char>& ops, std::stack<double>& operands)
{
  double result {};
  double rhs {operands.top()};                  // 우항을 가져온다...
  operands.pop();                               // ...그리고 스택에서 삭제한다
  double lhs {operands.top()};                  // 좌항을 가져온다...
  operands.pop();                               // ...그리고 스택에서 삭제한다

  switch (ops.top())                            // 현재 연산자를 실행한다
  {
  case '+':
    result = lhs + rhs;
    break;
  case '-':
    result = lhs - rhs;
    break;
  case '*':
    result = lhs * rhs;
    break;
  case '/':
    result = lhs / rhs;
    break;
  case '^':
    result = std::pow(lhs, rhs);
    break;
  default:
    throw std::runtime_error {string{"invalid operator: "} + ops.top()};
  }
  ops.pop();                                    // 방금 실행한 연산자를 삭제한다
  operands.push(result);
  return result;
}

int main()
{
  std::stack<double> operands;           // 피연산자 푸시다운 스택
  std::stack<char> operators;            // 연산자 푸시다운 스택
  string exp;                            // 평가할 계산식
  std::cout << 
              "An arithmetic expression can include the operators +, -, *, /, and ^ for exponentiation."
            << std::endl;
  try
  {
    while (true)
    {
      std::cout << "Enter an arithmetic expression and press Enter - enter an empty line to end:" << std::endl;
      std::getline(std::cin, exp, '\n');
      if (exp.empty()) break;

      // 공백을 제거한다
      exp.erase(std::remove(std::begin(exp), std::end(exp), ' '), std::end(exp));

      size_t index {};                            // 문자열 식을 위한 인덱스

      // 모든 표현식에서 피연산자는 숫자로 시작해야 한다
      operands.push(std::stod(exp, &index));  // 스택에 첫 번째 피연산자(좌항, lhs)를 넣는다

      while (true)
      {
        operators.push(exp[index++]);             // 연산자를 스택에 넣는다

        // Get rhs operand
        size_t i {};                                      // 서브스트링의 인덱스
        operands.push(std::stod(exp.substr(index), &i));  // 우항 피연산자(rhs)를 넣는다
        index += i;                                       // 식의 인덱스를 증가

        if (index == exp.length())                    // 식의 끝에 도달했으면...
        {
          while (!operators.empty())                  // ...처리되지 않은 연산자를 실행
            execute(operators, operands);
          break;
        }

        // 여기까지 도달하면 처리할 연산자가 아직 남아 있다...
        // 이전 연산자와 같거나 더 높은 우선순위이면 실행한다
        while (!operators.empty() && precedence(exp[index]) <= precedence(operators.top())) 
          execute(operators, operands);                   //  이전 연산자를 실행한다
      }
      std::cout << "result = " << operands.top() << std::endl;
    }
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }
  std::cout << "Calculator ending..." << std::endl;
}
