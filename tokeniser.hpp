#ifndef MNC_TOKENISER
#define MNC_TOKENISER

#include <string>
#include <vector>
#include <regex>
#include <variant>

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

  /// class encapsulating a Token in the source code
  template < typename PatternHolder >
  class Token {
  public:
    
    Token() = default;

    explicit
    Token(const std::string &raw_str)
      : raw_str(raw_str) { }

    /// the source code string responsible for this token.
    const std::string&
    str() const
    {
      return raw_str;
    }

    /// regex pattern this token type matches against
    static const std::regex&
    pattern()
    {
      static const std::regex pat(PatternHolder::pattern());
      return pat;
    }

    /// return a string representing the name of the token
    static const std::string &
    name()
    {
      return PatternHolder::name();
    }
    
  private:

    /// the source code string responsible for this token.
    std::string raw_str;

  };
  
  struct IntLitHolder {

    static const std::string&
    pattern()
    {
      static const std::string p = "[0-9]+";
      return p;
    }

    static const std::string&
    name()
    {
      static const std::string n = "int";
      return n;
    }

  };

  /// integer literal token
  using IntLit = Token<IntLitHolder>;

  struct IdentHolder {

    static const std::string&
    pattern()
    {
      static const std::string p = "[a-zA-Z_][a-zA-Z0-9_]*";
      return p;
    }

    static const std::string&
    name()
    {
      static const std::string n = "ident";
      return n;
    }

  };
  
  /// indentifier token
  using Ident = Token<IdentHolder>; 

  struct OperatorHolder {

    static const std::string&
    pattern()
    {
      static const std::string p = "[+-/=<>:?!~&*(){}\\[\\]]+";
      return p;
    }

    static const std::string&
    name()
    {
      static const std::string n = "op";
      return n;
    }

  };

  /// operator token
  using Operator = Token<OperatorHolder>;

  /// a variable token type
  using VarToken = std::variant<IntLit, Ident, Operator>;

  /// class mapping strings to vector of tokens
  class Tokeniser {
  public:

    Tokeniser()
      : int_lit_match()
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

    TokenMatcher<Ident> ident_match;

    TokenMatcher<Operator> op_match;
    
  };
}

#endif
