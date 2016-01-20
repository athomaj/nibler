//
// Stats.cpp for  in /home/maillo_a/rendu/cpp_nibbler
// 
// Made by Flavien Maillot
// Login   <maillo_a@epitech.net>
// 
// Started on  Mon Mar 30 17:28:17 2015 Flavien Maillot
// Last update Sun Apr  5 12:30:09 2015 Flavien Maillot
//

#include "Stats.hh"

Stats::Stats(const std::string& _username)
{
  this->username = _username;
  this->maxsize = 4;
  this->minsize = 4;
  this->active = true;
  this->food.insert(std::pair<t_emap, int>(FOOD, 0));
  this->food.insert(std::pair<t_emap, int>(FASTFOOD, 0));
  this->food.insert(std::pair<t_emap, int>(RANDFOOD, 0));
  this->food.insert(std::pair<t_emap, int>(POISONFOOD, 0));
  this->food.insert(std::pair<t_emap, int>(PASSMURAILLE, 0));
  this->food.insert(std::pair<t_emap, int>(TURTLEFOOD, 0));
  this->food.insert(std::pair<t_emap, int>(RABBITFOOD, 0));
}

Stats::~Stats()
{
}

std::string	Stats::getUsername() const
{
  return (this->username);
}

void		Stats::setUsername(const std::string& _username)
{
  this->username = _username;
}

void		Stats::setStats(const bool status)
{
  this->active = status;
}

void		Stats::increase(const t_emap type)
{
  this->food[type] += 1;
}

void		Stats::updateSize(const int size)
{
  if (size > this->maxsize)
    this->maxsize = size;
  if (this->minsize > size)
    this->minsize = size;
}

void		Stats::updateMaxSize(const int size)
{
  if (size > this->maxsize)
    maxsize = size;
}

int		Stats::getMaxSize() const
{
  return (this->maxsize);
}

void		Stats::updateMinSize(const int size)
{
  if (this->minsize > size)
    this->minsize = size;
}

int		Stats::getMinSize() const
{
  return (this->minsize);
}

void		Stats::display() const
{
  std::map<t_emap, int>::const_iterator it;

  if (this->active == true)
    {
      std::cout << ":: STATISTIQUES DE JEU ::" << std::endl;
      std::cout << "Username | Taille max | Taille min | Food | FastFood | Rand | Poison | Pass | Tortue | Lapin |" << std::endl;
      std::cout << username << " | " << maxsize << " | " << minsize << " | ";
      for (it = this->food.begin(); it != this->food.end(); ++it)
	std::cout << it->second << " | ";
      std::cout << std::endl;
    }
}
