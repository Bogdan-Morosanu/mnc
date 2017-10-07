#ifndef MNC_TOKENISER
#define MNC_TOKENISER

#include <string>
#include <vector>
#include <regex>
#include <variant>

#include "token_types.hpp"

namespace mnc {

  /// split a string using whitespace as delimiters
  std::vector<std::string>
  space_split(const std::string &str);

  /// class matching strings to tokens
  template < typename T >
  class TokenMatcher {
  public:

    bool matches(const std::string &str)
    {
      return std::regex_match(str, T::pattern());
    }
  };

  /// class mapping strings to vector of tokens
  class Tokeniser {
  public:

    Tokeniser()
      : int_lit_match()
      , keyword_match()
      , ident_match()
      , op_match()
    { }

    /// parse string STR into tokens
    std::vector<VarToken>
    tokenise(const std::string &str)
    {
      return str_to_token(space_split(str));
    }
    
  private:

    std::vector<VarToken>
    str_to_token(const std::vector<std::string> &str_vec);
    
    TokenMatcher<IntLit> int_lit_match;

    TokenMatcher<KeyWord> keyword_match;
    
    TokenMatcher<Ident> ident_match;

    TokenMatcher<Operator> op_match;
    
  };
}

#endif
