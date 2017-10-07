#include <vector>
#include <iostream>

template < typename T >
std::ostream &
operator << (std::ostream &out, const std::vector<T> &v)
{
  out << "{ ";

  for (auto it = v.begin(); it != (v.end() - 1); ++it)
    out << *it << ", ";

  out << *(v.end() - 1) << " }";

  return out;
}
