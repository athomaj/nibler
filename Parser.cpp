//
// Parser.cpp for  in /home/maillo_a/rendu/cpp_nibbler
// 
// Made by Flavien Maillot
// Login   <maillo_a@epitech.net>
// 
// Started on  Sat Apr  4 22:39:25 2015 Flavien Maillot
// Last update Sun Apr  5 23:20:59 2015 julien athomas
//

#include "Parser.hh"

Parser::Parser()
{
  this->file = FILENAME;
  this->ptrMet.insert(std::pair<std::string, parserPtr>
		     ("FOOD", &Parser::food));
  this->ptrMet.insert(std::pair<std::string, parserPtr>
		     ("FASTFOOD", &Parser::fastfood));
  this->ptrMet.insert(std::pair<std::string, parserPtr>
		     ("RANDFOOD", &Parser::randfood));
  this->ptrMet.insert(std::pair<std::string, parserPtr>
		     ("POISONFOOD", &Parser::poisonfood));
  this->ptrMet.insert(std::pair<std::string, parserPtr>
		     ("PASSMURAILLE", &Parser::passmuraille));
  this->ptrMet.insert(std::pair<std::string, parserPtr>
		     ("TURTLEFOOD", &Parser::turtlefood));
  this->ptrMet.insert(std::pair<std::string, parserPtr>
		     ("RABBITFOOD", &Parser::rabbitfood));
  this->ptrMet.insert(std::pair<std::string, parserPtr>
		     ("INSOLATION", &Parser::insolation));
  this->ptrMet.insert(std::pair<std::string, parserPtr>
		     ("KEYMAP", &Parser::keymap));
  this->ptrMet.insert(std::pair<std::string, parserPtr>
		     ("LEVEL", &Parser::level));
  this->ptrMet.insert(std::pair<std::string, parserPtr>
		      ("WALL", &Parser::wall));
  this->ptrMet.insert(std::pair<std::string, parserPtr>
		      ("USERNAME", &Parser::username));
  this->ptrMet.insert(std::pair<std::string, parserPtr>
		      ("STATS", &Parser::stats));
}

Parser::~Parser()
{
}

bool		Parser::openAndReadFile(Snake& snake, Map& map)
{
  std::ifstream	filetmp("snake.conf");
  std::string	line;
  std::map<std::string, parserPtr>::const_iterator it;
  int		wb;

  if (!filetmp)
    throw std::logic_error("Could not open the file: " + std::string(this->file));
  while (getline(filetmp, line, '\n'))
    {
      wb = 0;
      for (it = this->ptrMet.begin(); it != this->ptrMet.end() && wb != 1; ++it)
	{
	  if (line.compare(0, it->first.length(), it->first) == 0)
	    {
	      line.erase(line.begin(), line.begin() + (it->first.length() + 1));
	      (this->*(it->second))(snake, map, line);
	      wb = 1;
	    }
	}
    }
  return (true);
}

bool	Parser::run(Snake& snake, Map& map)
{
  return (this->openAndReadFile(snake, map));
}

std::vector<std::string>	Parser::splitString(std::string line, const std::string& delim) const
{
  std::vector<std::string>	result;
  size_t			pos;

  pos = 0;
  while ((pos = line.find(delim)) != std::string::npos)
    {
      result.push_back(line.substr(0, pos));
      line.erase(0, pos + delim.size());
    }
  result.push_back(line);
  return (result);
}

int		Parser::getInt(const std::string& value) const
{
  std::stringstream val(value);
  int			result;

  val >> result;
  return (result);
}

bool	Parser::food(UNUSED Snake& snake, Map& map, std::string const& line) const
{
  std::vector<std::string> result;

  result = this->splitString(line, std::string(","));
  if (result.size() != 4)
    return (false);
  map.updateConf(FOOD, getInt(result[0]), getInt(result[1]), getInt(result[2]), getInt(result[3]));
  return (true);
}

bool	Parser::fastfood(UNUSED Snake& snake, Map& map, std::string const& line)const
{
  std::vector<std::string> result;

  result = this->splitString(line, std::string(","));
  if (result.size() != 4)
    return (false);
  map.updateConf(FASTFOOD, getInt(result[0]), getInt(result[1]), getInt(result[2]), getInt(result[3]));
  return (true);
}

bool	Parser::randfood(UNUSED Snake& snake, Map& map, std::string const& line)const
{
  std::vector<std::string> result;

  result = this->splitString(line, std::string(","));
  if (result.size() != 4)
    return (false);
  map.updateConf(RANDFOOD, getInt(result[0]), getInt(result[1]), getInt(result[2]), getInt(result[3]));
  return (true);
}

bool	Parser::poisonfood(UNUSED Snake& snake, Map& map, std::string const& line)const
{
  std::vector<std::string> result;

  result = this->splitString(line, std::string(","));
  if (result.size() != 4)
    return (false);
  map.updateConf(POISONFOOD, getInt(result[0]), getInt(result[1]), getInt(result[2]), getInt(result[3]));
  return (true);
}

bool	Parser::passmuraille(UNUSED Snake& snake, Map& map, std::string const& line)const
{
  std::vector<std::string> result;

  result = this->splitString(line, std::string(","));
  if (result.size() != 4)
    return (false);
  map.updateConf(PASSMURAILLE, getInt(result[0]), getInt(result[1]), getInt(result[2]), getInt(result[3]));
  return (true);
}

bool	Parser::turtlefood(UNUSED Snake& snake, Map& map, std::string const& line)const
{
  std::vector<std::string> result;

  result = this->splitString(line, std::string(","));
  if (result.size() != 4)
    return (false);
  map.updateConf(TURTLEFOOD, getInt(result[0]), getInt(result[1]), getInt(result[2]), getInt(result[3]));
  return (true);
}

bool	Parser::rabbitfood(UNUSED Snake& snake, Map& map, std::string const& line)const
{
  std::vector<std::string> result;

  result = this->splitString(line, std::string(","));
  if (result.size() != 4)
    return (false);
  map.updateConf(RABBITFOOD, getInt(result[0]), getInt(result[1]), getInt(result[2]), getInt(result[3]));
  return (true);
}

bool	Parser::insolation(UNUSED Snake& snake, Map& map, std::string const& line)const
{
  std::vector<std::string> result;

  result = this->splitString(line, std::string(","));
  if (result.size() != 4)
    return (false);
  map.updateConf(INSOLATION, getInt(result[0]), getInt(result[1]), getInt(result[2]), getInt(result[3]));
  return (true);
}

bool	Parser::wall(UNUSED Snake& snake, Map& map, std::string const& line)const
{
  int	result;

  result = getInt(line);
  map.updateConf(WALL, result, 86400, 0, 100);
  return (true);
}

bool	Parser::keymap(Snake& snake, UNUSED Map& map, std::string const& line)const
{
  snake.setKeymap(getInt(line));
  return (true);
}

bool	Parser::username(Snake& snake, UNUSED Map& map, std::string const& line)const
{
  snake.setUsername(line);
  return (true);
}

bool	Parser::stats(Snake& snake, UNUSED Map& map, std::string const& line)const
{
  snake.setStats(getInt(line));
  return (true);
}

bool	Parser::level(Snake& snake, Map& map, std::string const& line)const
{
  int	level;

  level = this->getInt(line);
  snake.setSpeed(80000);
  if (level == 0)
    {
      snake.setSpeed(100000);
      map.setQte(POISONFOOD, 0);
      map.setQte(PASSMURAILLE, 0);
      map.setQte(TURTLEFOOD, 0);
      map.setQte(RABBITFOOD, 0);
      map.setQte(INSOLATION, 0);
      map.setQte(WALL, 0);
    }
  else if (level == 1)
    {
      map.setQte(POISONFOOD, 0);
      map.setQte(PASSMURAILLE, 0);
      map.setQte(TURTLEFOOD, 0);
      map.setQte(RABBITFOOD, 0);
      map.setQte(INSOLATION, 0);
    }
  else if (level == 3)
    snake.setLevel(3);
  return (true);
}

