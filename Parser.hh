//
// Parser.hh for  in /home/maillo_a/rendu/cpp_nibbler
// 
// Made by Flavien Maillot
// Login   <maillo_a@epitech.net>
// 
// Started on  Sat Apr  4 22:39:43 2015 Flavien Maillot
// Last update Sun Apr  5 12:26:16 2015 Flavien Maillot
//

#ifndef PARSER_HH_
# define PARSER_HH_

# include <iostream>
# include <string>
# include <fstream>
# include <sstream>
# include <map>
# include "Snake.hh"

# define FILENAME "snake.conf"
# define UNUSED __attribute__((unused))

class Parser;

typedef bool (Parser::*parserPtr)(Snake&, Map&, std::string const&) const;

class Parser
{
private:
  std::string	file;
  std::map<std::string, parserPtr>	ptrMet;

  std::vector<std::string>		splitString(std::string, const std::string&) const;
  int					getInt(const std::string&) const;
  bool					openAndReadFile(Snake&, Map&);
  //Pointeur sur methode
  bool		food(Snake&, Map&, std::string const&) const;
  bool		fastfood(Snake&, Map&, std::string const&) const;
  bool		randfood(Snake&, Map&, std::string const&) const;
  bool		poisonfood(Snake&, Map&, std::string const&) const;
  bool		passmuraille(Snake&, Map&, std::string const&) const;
  bool		turtlefood(Snake&, Map&, std::string const&) const;
  bool		rabbitfood(Snake&, Map&, std::string const&) const;
  bool		insolation(Snake&, Map&, std::string const&) const;
  bool		keymap(Snake&, Map&, std::string const&) const;
  bool		level(Snake&, Map&, std::string const&) const;
  bool		wall(Snake&, Map&, std::string const&) const;
  bool		username(Snake&, Map&, std::string const&) const;
  bool		stats(Snake&, Map&, std::string const&) const;
public:
  Parser();
  ~Parser();
  bool		run(Snake&, Map&);
};

#endif /* !PARSER_HH_ */
