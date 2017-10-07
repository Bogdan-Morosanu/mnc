#include "tokeniser.hpp"

#include <cctype>

namespace mnc {
  
  std::vector<std::string>
  tokenise(const std::string &str)
  {
    auto b = str.begin();
    auto e = str.end();

    std::vector<std::string> retval(1);
    enum State { PREVIOUS_BLANK, PREVIOUS_NON_BLANK };

    // fix the warts of C's old function... (we don't care about EOF)
    auto isspace = [](unsigned char c) { return std::isspace(c) != 0; };

    State s = isspace(*b) ? PREVIOUS_BLANK : PREVIOUS_NON_BLANK;
    for ( ; b != e; ++b) {
      switch (s) {
      case PREVIOUS_BLANK:
	if (isspace(*b)) {
	  // just glob up whitespace

	} else {
	  // state change and start new string.
	  s = PREVIOUS_NON_BLANK;
	  retval.emplace_back(&*b, std::size_t(1)); 

	}
	break;
	
      case PREVIOUS_NON_BLANK:
	if (isspace(*b)) {
	  // state change
	  s = PREVIOUS_BLANK;

	} else {
	  // just keep adding to the existing string
	  retval.back().push_back(*b);
	}
	break;
      }
    }

    return retval;
  }
}

