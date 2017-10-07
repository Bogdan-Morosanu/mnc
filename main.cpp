#include "tokeniser.hpp"
#include "io-helpers.hpp"

#include <iostream>
#include <cstdlib>

int main(int argc, char **argv)
{
  if (argc != 2) {
    std::cerr << "usage " << *argv << " <string to tokenise>" << std::endl;
    std::exit(EXIT_FAILURE);
  }

  std::cout << mnc::tokenise(argv[1]) << std::endl;

  return 0;
}
