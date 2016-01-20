//
// Coordinates.cpp for  in /home/maillo_a/rendu/cpp_nibbler
// 
// Made by Flavien Maillot
// Login   <maillo_a@epitech.net>
// 
// Started on  Tue Mar 31 18:44:45 2015 Flavien Maillot
// Last update Sun Apr  5 12:13:55 2015 Flavien Maillot
//

#include "Coordinates.hh"

Coordinates::Coordinates(int _x, int _y):
  x(_x), y(_y)
{
}

Coordinates::~Coordinates()
{
}

int	Coordinates::getX() const
{
  return (this->x);
}

void	Coordinates::setX(const int _x)
{
  this->x = _x;
}

int	Coordinates::getY() const
{
  return (this->y);
}

void	Coordinates::setY(const int _y)
{
  this->y = _y;
}
