#pragma once

#include <exception>
#include <string>

class ZappyException : public std::exception {
protected:
  std::string const _str;
  std::string const _type;

public:
  ZappyException(std::string const& str, std::string const& type = "");
  ~ZappyException() throw();
  const char *what() const throw();
};

class NetworkException : public ZappyException {
public:
  NetworkException(std::string const& str);
};

class ParserException : public ZappyException {
public:
  ParserException(std::string const& str);
};

class DisplayException : public ZappyException {
public:
  DisplayException(std::string const& str);
};

class ArgumentException : public ZappyException {
public:
  ArgumentException(std::string const& str);
};
