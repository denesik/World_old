#include "StringIntern.h"



StringIntern operator+(const StringIntern &a, const StringIntern &b)
{
  return StringIntern(a.get() + b.get());
}
