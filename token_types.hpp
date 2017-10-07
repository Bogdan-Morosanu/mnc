#ifndef TOKEN_TYPES
#define TOKEN_TYPES

#include <string>
#include <regex>
#include <variant>

namespace mnc {

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

  namespace detail {

    // ---- structs holding regexes and names for tokens ----
    
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

    struct KeyWordHolder {

      static const std::string&
      pattern()
      {
	static const std::string p = "fun";
	return p;
      }

      static const std::string&
      name()
      {
	static const std::string n = "keyword";
	return n;
      }

    };

  }

  /// integer literal token
  using IntLit = Token<detail::IntLitHolder>;

  /// indentifier token
  using Ident = Token<detail::IdentHolder>; 
  
  /// operator token
  using Operator = Token<detail::OperatorHolder>;

  /// keyword token
  using KeyWord = Token<detail::KeyWordHolder>;
  
  /// a variable token type
  using VarToken = std::variant<IntLit, Ident, Operator, KeyWord>;

}
#endif
