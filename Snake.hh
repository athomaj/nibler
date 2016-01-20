//
// Snake.hh for  in /home/maillo_a/rendu/cpp_nibbler
// 
// Made by Flavien Maillot
// Login   <maillo_a@epitech.net>
// 
// Started on  Tue Mar 31 18:26:49 2015 Flavien Maillot
// Last update Sun Apr  5 22:35:26 2015 julien athomas
//

#ifndef SNAKE_HH_
# define SNAKE_HH_

# include <vector>
# include <map>
# include <cstdlib>
# include "Event.hh"
# include "Coordinates.hh"
# include "Emap.hh"
# include "Stats.hh"

class Map;

//KEYMAP 0 : left right
//       1 : left right up down
# define KEYMAP 1
# define SPEED 80000
//Vitesse normal

typedef struct	s_cnf
{
  bool		active;
  time_t	cooldown;
}		t_cnf;

class Snake
{
private:
  std::vector<t_coord>	coord;
  int			speed;
  time_t		speedcooldown;
  int			speedinc;
  int			level;
  int			keymap;
  int			width;
  int			height;
  int			poison;
  t_event		prev;
  Stats			stats;
  std::map<t_emap, t_cnf>	config;
  t_event		type[4];
  void			(Snake::*fptr[4])();
  void			(Snake::*fptrIns[4])();

  //Déplacement
  void			left();
  void			right();
  void			up();
  void			down();
  //Initialisation
  void			initConfig();
  t_cnf			constructConf() const;
  //Check
  bool			isCooldown(time_t const) const;
  time_t		getTime(int const) const;
  void			checkSpeedSpace();
  void			speedLevel();
public:
  Snake();
  ~Snake();

  std::vector<t_coord>&	updateCoord();

  //Initialisation
  void			setSnake(int const width, int const height, int const size);

  //Setter et Getter
  void			setKeymap(const int);
  int			getKeymap() const;
  void			setLevel(const int);
  void			setStats(const int);
  void			addRandLink();
  void			addFoodLink();
  void			addFastLink();
  void			addLink();
  void			removeLink();
  void			setSpeed(int const _speed);
  int			getSpeed() const;
  void			setSpeedSpace();
  void			increaseSpeed();
  void			decreaseSpeed();
  void			setPassMuraille();
  void			setInsolation();
  void			setPoisonFood();
  int			getCooldown(time_t const) const;
  void			setUsername(std::string);
  Stats			getStats() const;
  //Check
  bool			isPassMuraille();
  bool			isInsolation();
  bool			isPoisonFood();
  int			checkPoisonFood(int const);

  //Déplacement du snake
  void			move();
  void			changeDirection(t_event const direction);
  void			twoDirection(t_event const direction);
  void			fourDirection(t_event const direction);

  //Juste pour le debug
  void			debug() const;
};

# include "Map.hh"

#endif /* !SNAKE_HH_ */
