#ifndef MNC_IO_HELPERS
#define MNC_IO_HELPERS

#include <vector>
#include <iostream>
#include <variant>

#include "tokeniser.hpp"

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

template < typename PatternHolder >
std::ostream &
operator << (std::ostream &out, const mnc::Token<PatternHolder> &tkn)
{
  return out << "<" << tkn.name() << ": '" << tkn.str() << "'>";
}

template < typename T, typename ... Ts >
std::ostream &
operator << (std::ostream &out, const std::variant<T, Ts...> &v)
{
  return std::visit([&out](auto x) -> std::ostream&
		    {
		      return out << x;
		    }, v);
}

#endif
