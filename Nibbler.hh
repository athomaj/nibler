/*
** nibbler.h for Nibbler in /home/ferrei_e/cpp_nibbler
** 
** Made by Ferreira Cintia
** Login   <ferrei_e@epitech.net>
** 
** Started on  Wed Mar 11 16:10:10 2015 Ferreira Cintia
// Last update Sun Apr  5 22:35:34 2015 julien athomas
*/

#ifndef NIBBLER_HH_
# define NIBBLER_HH_

# include <dlfcn.h>
# include <iostream>
# include <string>
# include <stdexcept>
# include <vector>
# include <cstdlib>
# include <unistd.h>
# include "Event.hh"
# include "library/IDisplayModule.hh"
# include "library/DLLoader.hpp"
# include "Map.hh"
# include "Stats.hh"
# include "Snake.hh"
# include "Parser.hh"

class Nibbler
{
private:
  int			height;
  int			width;
  bool			pause;
  IDisplayModule	*instance;
  Snake			snake;
  Stats			stats;
  Map			map;
  t_emap		type[8];
  void			(Snake::*fptr[8])();

  void			checkCurPos(t_event&, t_event&, int&);
  int			checkCollision();
  bool			endGame(int const);
  void			initAlgo(t_event&, t_event&, Parser&);
public:
  Nibbler(std::string const&, std::string const&, std::string const&);
  ~Nibbler();

  int			getHeight() const;
  int			getWidth() const;
  IDisplayModule	*getInstance() const;

  bool			is_numeric(std::string const&) const;

  bool			run();
};

#endif /* !NIBBLER_HH_ */
