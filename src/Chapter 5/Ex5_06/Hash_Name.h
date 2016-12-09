// Hash_Name.h 
// Ex5_06의 Name 객체를 해시하는 함수 객체 타입
#ifndef HASH_NAME_H
#define HASH_NAME_H
#include "Name.h"

class Hash_Name
{
public:
  size_t operator()(const Name& name) const {  return name.hash();  }
};
#endif