//
// Map.hh for  in /home/maillo_a/rendu/cpp_nibbler
// 
// Made by Flavien Maillot
// Login   <maillo_a@epitech.net>
// 
// Started on  Wed Apr  1 16:52:13 2015 Flavien Maillot
// Last update Sun Apr  5 22:35:46 2015 julien athomas
//

#ifndef MAP_HH_
# define MAP_HH_

# include <iostream>
# include <vector>
# include <map>
# include <stdexcept>
# include <ctime>
# include <cstdlib>
# include "Emap.hh"
# include "Snake.hh"

# define LIMITGEN 2000
# define NBWALL 5

# define NBFOOD 1
# define COFOOD 86400
# define LAFOOD 0
# define LUFOOD 100
# define NBFASTFOOD 1
# define COFASTFOOD 5
# define LAFASTFOOD 0
# define LUFASTFOOD 100
# define NBRANDFOOD 1
# define CORANDFOOD 10
# define LARANDFOOD 20
# define LURANDFOOD 50
# define NBPOISONFOOD 1
# define COPOISONFOOD 20
# define LAPOISONFOOD 50
# define LUPOISONFOOD 20
# define NBPASSMURAILLE 1
# define COPASSMURAILLE 10
# define LAPASSMURAILLE 50
# define LUPASSMURAILLE 20
# define NBTURTLEFOOD 1
# define COTURTLEFOOD 20
# define LATURTLEFOOD 50
# define LUTURTLEFOOD 40
# define NBRABBITFOOD 1
# define CORABBITFOOD 10
# define LARABBITFOOD 50
# define LURABBITFOOD 40
# define NBINSOLATION 1
# define COINSOLATION 20
# define LAINSOLATION 20
# define LUINSOLATION 20

typedef struct	s_map
{
  t_emap	type;
  int		x;
  int		y;
  time_t	cooldown;
}		t_map;

typedef struct	s_mapcnf
{
  bool		active;
  int		qte;
  time_t	cooldown;
  time_t	laptime;
  int		luck;
  time_t	nextappear;
}		t_mapcnf;

class Map
{
private:
  std::vector<t_map>	map;
  std::map<t_emap, t_mapcnf>	conf;
  int			width;
  int			height;
  bool			active;
public:
  Map();
  ~Map();

  std::vector<t_map>&	updateMap();
  const std::vector<t_map>&	getMap() const;

  //Initialisation
  void			init();
  t_mapcnf		constructConf(const int, const int, const int, const int) const;
  void			updateConf(const t_emap, const int, const int, const int, const int);
  void			reduceQte();
  void			setQte(const t_emap, const int);

  //Getter et Setter
  void			setActive(const bool);
  void			setWidth(const int);
  int			getWidth() const;
  void			setHeight(const int);
  int			getHeight() const;

  //Verification et action par tours
  void			checkAndUpdate(Snake const& snake);
  void			checkAndGenerate(Snake const& snake);
  bool			checkLuck(const int) const;

  //Gestion cooldown & laptime
  void			checkCooldown(Snake const& snake);
  time_t		getCooldown(t_emap const type);
  bool			isCooldown(t_map const& point) const;
  time_t		getLaptime(int const) const;
  bool			isLaptime(t_mapcnf const&) const;

  //Gestion collision
  bool			snakeCollision(Snake& snake, int const, int const) const;
  bool			headCollision(Snake& snake, int const, int const) const;
  t_emap		inCollision(Snake& snake, int const x, int const y);
  bool			inFullCollision(Snake&, int const x, int const y);

  //Gestion Génération
  void			setObj(t_emap const type, int const posx, int const posy);
  t_emap		eraseObj(Snake const& snake, int const pos);
  void			generateElem(Snake snake, t_emap const elem, int const nb);
  bool			generate(Snake& snake);

  //Debug
  void			debug() const;
};


/*
type = type de nourriture (détermine le cooldown)
cooldown = date en seconde où la nourriture disparaitra.
*/

#endif /* !MAP_HH_ */
