// Ex6_02.cpp
// 정렬과 내부 병합
#include <iostream>                              // 표준 스트림
#include <string>                                // string 클래스
#include <algorithm>                             // sort(), inplace_merge()
#include <functional>                            // greater<T>
#include <vector>                                // vector 컨테이너
#include <utility>                               // pair 템플릿 타입
#include <map>                                   // map 컨테이너
#include <iterator>                              // 스트림과 back_inserter
#include "Account.h"
#include "Transaction.h"
#include "Compare_Names.h"

using std::string;
using first_name = string;
using second_name = string;
using Name = std::pair<first_name, second_name>;
using Account_Number = size_t;

// 계좌 소유자의 이름을 읽어온다
Name get_holder_name(Account_Number number)
{
  std::cout << "Enter the holder's first and second names for account number " << number << ": ";
  string first{};
  string second{};
  std::cin >> first >> second;
  return std::make_pair(first, second);
}

int main()
{
  std::vector<Transaction> transactions;

  std::cout << "Enter each transaction as:\n"
    << "   5 digit account number   amount   credit(true or false).\n"
    << "Enter Ctrl+Z to end.\n";

  // 거래의 첫 번쩨 세트를 읽어온다
  std::copy(std::istream_iterator<Transaction> {std::cin}, std::istream_iterator<Transaction> {},
    std::back_inserter(transactions));
  std::cin.clear();                              // 스트림의 EOF 플래그를 정리한다

                                                 // 첫 번째 세트를 계좌번호 내림차순으로 정렬한다
  std::stable_sort(std::begin(transactions), std::end(transactions), std::greater<>());

  // 거래를 출력한다
  std::cout << "First set of transactions after sorting...\n";
  std::copy(std::begin(transactions), std::end(transactions),
    std::ostream_iterator<Transaction>{std::cout, "\n"});


  // 거래의 두 번째 세트를 읽어온다
  std::cout << "\nEnter more transactions:\n";
  std::copy(std::istream_iterator<Transaction> {std::cin}, std::istream_iterator<Transaction> {},
    std::back_inserter(transactions));
  std::cin.clear();                              // 스트림의 EOF 플래그를 정리한다

                                                 // 거래를 출력한다
  std::cout << "\nSorted first set of transactions with second set appended...\n";
  std::copy(std::begin(transactions), std::end(transactions),
    std::ostream_iterator<Transaction>{std::cout, "\n"});

  // 두 번째 세트를 계좌번호 내림차순으로 정렬한다
  auto iter = std::is_sorted_until(std::begin(transactions), std::end(transactions),
    std::greater<>());
  std::stable_sort(iter, std::end(transactions), std::greater<>());

  // 거래를 출력한다
  std::cout << "\nSorted first set of transactions with sorted second set appended...\n";
  std::copy(std::begin(transactions), std::end(transactions),
    std::ostream_iterator<Transaction>{std::cout, "\n"});

  // 내부에서 거래를 병합한다
  std::inplace_merge(std::begin(transactions), iter, std::end(transactions), std::greater<>());

  // 거래를 출력한다
  std::cout << "\nMerged sets of transactions...\n";
  std::copy(std::begin(transactions), std::end(transactions),
    std::ostream_iterator<Transaction>{std::cout, "\n"});

  // 필요할 때 Account 객체를 생성하면서 거래를 처리한다
  std::map<Account_Number, Account> accounts;
  for (const auto& tr : transactions)
  {
    Account_Number number = tr.get_acc_number();
    auto iter = accounts.find(number);
    if (iter == std::end(accounts))
      iter = accounts.emplace(number, Account{number, get_holder_name(number)}).first;

    if (iter->second.apply_transaction(tr))
    {
      auto name = iter->second.get_name();
      std::cout << "\nAccount number " << number
        << " for " << name.first << " " << name.second << " is overdrawn!\n"
        << "The concept is that you bank with us - not the other way round, so fix it!\n"
        << std::endl;
    }
  }

  // 계좌를 벡터 컨테이너로 복제한다
  std::vector<Account> accs;
  for (const auto& pr : accounts)
    accs.push_back(pr.second);

  // 이름순으로 정렬한 후에 계좌들을 출력한다
  std::stable_sort(std::begin(accs), std::end(accs), Compare_Names());
  std::copy(std::begin(accs), std::end(accs), std::ostream_iterator < Account > {std::cout, "\n"});
}
