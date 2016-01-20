//
// sdl.hh for nibbler in /home/ferrei_e/cpp_nibbler/library/libSDL
// 
// Made by Ferreira Cintia
// Login   <ferrei_e@epitech.net>
// 
// Started on  Mon Mar 30 17:42:40 2015 Ferreira Cintia
// Last update Sun Apr  5 18:14:36 2015 julien athomas
//

#ifndef SDL_HH_
# define SDL_HH_

# include <SDL/SDL.h>
# include "../../Nibbler.hh"

# define NBKEY 7
# define MIN 50
# define MAX 200

# define FOODBMP "./library/libSDL/food.bmp"
# define FASTFOODBMP "./library/libSDL/fastfood.bmp"
# define RANDFOODBMP "./library/libSDL/potion_rand.bmp"
# define POISONFOODBMP "./library/libSDL/poison.bmp"
# define PASSMURBMP "./library/libSDL/potion_pass.bmp"
# define TURTLEFOODBMP "./library/libSDL/turtle.bmp"
# define RABBITFOODBMP "./library/libSDL/rabbit.bmp"
# define INSOLATIONBMP "./library/libSDL/potion_inso.bmp"
# define WALLBMP "./library/libSDL/wall.bmp"

class Sdl : public IDisplayModule
{
private:
  std::string	name;
  SDL_Surface	*window;
  SDL_Surface	*objet;
  int		framerate;
  int		height;
  int		width;
  int		startx;
  int		starty;
  t_emap	type[9];
  void		(Sdl::*fptr[9])(std::string&) const;
  int		keyType[NBKEY];
  t_event	(Sdl::*keyFptr[NBKEY])() const;

  bool		check(const int, const int) const;
  void		displayMap(const std::vector<t_map>& map);

  void          imgFood(std::string&) const;
  void          imgFastFood(std::string&) const;
  void          imgRandFood(std::string&) const;
  void          imgPoisonFood(std::string&) const;
  void          imgPassMur(std::string&) const;
  void          imgTurtleFood(std::string&) const;
  void          imgRabbitFood(std::string&) const;
  void          imgInsolation(std::string&) const;
  void          imgWall(std::string&) const;

  void		whichImg(std::string&, t_emap const);
  t_event	keyEvent(int const);
  t_event	escape() const;
  t_event	right() const;
  t_event	left() const;
  t_event	up() const;
  t_event	down() const;
  t_event	space() const;
  t_event	pause() const;
public:
  Sdl();
  virtual ~Sdl();

  virtual std::string const& getName() const;
  virtual void		init(const int, const int);
  virtual void		stop();
  virtual void		display(std::vector<t_coord>& snake, const std::vector<t_map>& map);
  virtual e_event	getEvent(t_event);
};

#endif /* !SDL_HH_ */
