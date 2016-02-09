#include <algorithm>
#include <iostream>
#include "libgen.h"
#include "Client.hpp"
#include "Options.hpp"
#include "Exceptions.hpp"

void fixRelativePath(std::string path) {
  path.erase(std::find(path.rbegin(), path.rend(), '/').base(), path.end());
  chdir(path.c_str());
}

int main(int const ac, char const *const * const av) {
  fixRelativePath(*av);
  try {
    Options options;
    if (!options.parse(ac, av))
      return EXIT_SUCCESS;
    Client cli(options);
    cli.run();
  } catch(ZappyException const& e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
