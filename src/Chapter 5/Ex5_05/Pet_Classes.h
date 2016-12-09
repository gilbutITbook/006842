// 예제 Ex5_05를 위한 Pet_Classes.h
// 애완동물을 정의한 클래스
#ifndef PET_CLASSES_H
#define PET_CLASSES_H
#include <string>                                // string 클래스
#include <cstring>                               // strcmp()
using std::string;

class Pet
{
protected:
  string name {};

public:
  virtual ~Pet(){}                               // 기반 클래스의 virtual 소멸자
  const string& get_name() const { return name;  }

   virtual bool operator<(const Pet& pet) const
  {
    auto result = std::strcmp(typeid(*this).name(), typeid(pet).name());
    return (result < 0) || ((result == 0) && (name < pet.name));
  }
  friend std::ostream& operator<<(std::ostream& out, const Pet& pet);
};

class Cat : public Pet
{
public:
  Cat() = default;
  Cat(const string& cat_name)
  {
    name = cat_name;
  }
};

class Dog : public Pet
{
public:
  Dog() = default;
  Dog(const string& dog_name)
  {
    name = dog_name;
  }
};

class Mouse : public Pet
{
public:
  Mouse() = default;
  Mouse(const string& mouse_name)
  {
    name = mouse_name;
  }
};

inline std::ostream& operator<<(std::ostream& out, const Pet& pet)
{
  return out << "A " <<
    string {typeid(pet).name()}.erase(0,6) << " called " << pet.name;
}
#endif