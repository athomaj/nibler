//
// IDisplayModule.hh for Nibbler in /home/maillo_a/rendu/cpp_nibbler
// 
// Made by Flavien Maillot
// Login   <maillo_a@epitech.net>
// 
// Started on  Tue Mar 24 15:35:15 2015 Flavien Maillot
// Last update Sun Apr  5 22:46:08 2015 Ferreira Cintia
//

#ifndef IDISPLAYMODULE_HH_
# define IDISPLAYMODULE_HH_

# include <iostream>
# include "../Nibbler.hh"
# include "../Snake.hh"
# include "../Map.hh"
# include "../Coordinates.hh"

class Nibbler;

class IDisplayModule
{
public:
  virtual ~IDisplayModule() {}

  virtual std::string const& getName() const = 0;
  virtual void		init(int const, int const) = 0;
  virtual void		stop() = 0;
  virtual void		display(std::vector<t_coord>& snake, const std::vector<t_map>& map) = 0;
  virtual t_event	getEvent(t_event) = 0;
};

#endif /* !IDISPLAYMODULE_HH_ */
