//
// ncurses.hh for  in /home/maillo_a/rendu/cpp_nibbler/library/libncurses
// 
// Made by Flavien Maillot
// Login   <maillo_a@epitech.net>
// 
// Started on  Mon Mar 30 10:43:41 2015 Flavien Maillot
// Last update Sun Apr  5 22:55:34 2015 julien athomas
//

#ifndef NCURSES_HH_
# define NCURSES_HH_

#include <ncurses.h>
#include "../../Nibbler.hh"

class Ncurses : public IDisplayModule
{
private:
  std::string	name;
  WINDOW	*window;
  int		framerate;
  int		height;
  int		width;
  int		startx;
  int		starty;
  int		type[7];
  t_emap	foodType[8];
  char		typeEq[9];
  t_event	(Ncurses::*fptr[7])();
  bool		check(const int, const int, const int, const int);
  void		displayMap(const std::vector<t_map>& map);
  t_event	keyUp();
  t_event	keyDown();
  t_event	keyRight();
  t_event	keyLeft();
  t_event	keyEsc();
  t_event	keySpace();
  t_event	keyBackSpace();

public:
  Ncurses();
  virtual ~Ncurses();

  virtual std::string const& getName() const;
  virtual void		init(const int, const int);
  virtual void		stop();
  virtual void		display(std::vector<t_coord>& snake, const std::vector<t_map>& map);
  virtual t_event	getEvent(t_event);
};

#endif /* !NCURSES_HH_ */
