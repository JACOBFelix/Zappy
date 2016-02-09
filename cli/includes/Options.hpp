#pragma once

#include <vector>
#include <string>

class Options {
private:
  std::string _port;
  std::string _host;
  bool _gui;
  std::string _teamName;

public:
  Options();
  ~Options();
  Options(Options const& rhs);
  Options& operator=(Options const& rhs);

  bool parse(int const ac, char const *const *const args);

  std::string const& getPort(void) const;
  void setPort(std::string const& port);
  std::string const& getHost(void) const;
  void setHost(std::string const& host);
  bool getGui(void) const;
  void setGui(bool const gui);
  std::string const& getTeamName(void) const;
  void setTeamName(std::string const& teamName);
};
