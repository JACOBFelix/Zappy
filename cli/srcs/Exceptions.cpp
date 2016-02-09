#include "Exceptions.hpp"

ZappyException::ZappyException(std::string const& str, std::string const& type) :
  std::exception(), _str(str), _type(type) {}

ZappyException::~ZappyException() throw() {}

const char *ZappyException::what(void) const throw() {
  return (_type + _str).c_str();
}

NetworkException::NetworkException(std::string const& str) : ZappyException(str, "Network error : ") {}

ParserException::ParserException(std::string const& str) : ZappyException(str, "Parser error : ") {}

DisplayException::DisplayException(std::string const& str) : ZappyException(str + "\nYou can try to launch the progam with --no-gui option", "Display error: ") {}

ArgumentException::ArgumentException(std::string const& str) : ZappyException(str, "Argument error: ") {}
