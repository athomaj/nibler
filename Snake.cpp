//
// Snake.cpp for  in /home/maillo_a/rendu/cpp_nibbler
// 
// Made by Flavien Maillot
// Login   <maillo_a@epitech.net>
// 
// Started on  Tue Mar 31 18:29:43 2015 Flavien Maillot
// Last update Sun Apr  5 17:14:11 2015 Flavien Maillot
//

#include <iostream>
#include "Snake.hh"

Snake::Snake()
{
  this->type[0] = UP;
  this->type[1] = DOWN;
  this->type[2] = RIGHT;
  this->type[3] = LEFT;

  this->fptr[0] = &Snake::up;
  this->fptr[1] = &Snake::down;
  this->fptr[2] = &Snake::right;
  this->fptr[3] = &Snake::left;

  this->fptrIns[0] = &Snake::left;
  this->fptrIns[1] = &Snake::right;
  this->fptrIns[2] = &Snake::down;
  this->fptrIns[3] = &Snake::up;
  this->level = 0;
}

Snake::~Snake()
{
}

std::vector<t_coord>&		Snake::updateCoord()
{
  return (this->coord);
}

void		Snake::setSnake(int const width, int const height, int size)
{
  int		i;
  int		midx;
  int		midy;
  t_coord	coo;

  ++size;
  midx = (width - size) / 2;
  midy = (height - 1) / 2;
  i = -1;
  while (++i < size)
    {
      coo.x = midx + 1;
      coo.y = midy;
      this->coord.insert(this->coord.begin(), coo);
    }
  this->width = width;
  this->height = height;
  this->initConfig();
}

void		Snake::initConfig()
{
  this->setSpeed(SPEED);
  this->prev = RIGHT;
  this->poison = 0;
  this->keymap = 0;
  this->speedinc = 0;
  this->config.insert(std::pair<t_emap, t_cnf>(PASSMURAILLE, this->constructConf()));
  this->config.insert(std::pair<t_emap, t_cnf>(INSOLATION, this->constructConf()));
  this->config.insert(std::pair<t_emap, t_cnf>(POISONFOOD, this->constructConf()));
}

t_cnf		Snake::constructConf() const
{
  t_cnf		conf;

  conf.active = false;
  conf.cooldown = 0;
  return (conf);
}

void		Snake::setKeymap(int const value)
{
  this->keymap = value;
}

int		Snake::getKeymap() const
{
  return (this->keymap);
}

void		Snake::setLevel(const int val)
{
  this->level = val;
}

void		Snake::setStats(int const value)
{
  if (value == 0)
    this->stats.setStats(false);
  else
    this->stats.setStats(true);
}

void		Snake::addRandLink()
{
  int		size;
  int		i;

  this->stats.increase(RANDFOOD);
  size = rand() % 5 + 1;
  i = -1;
  while (++i < size)
    this->addLink();
}

void		Snake::addFoodLink()
{
  this->stats.increase(FOOD);
  this->addLink();
}

void		Snake::addFastLink()
{
  this->stats.increase(FASTFOOD);
  this->addLink();
}

void		Snake::addLink()
{
  t_coord	coo;

  if (this->level == 3)
    this->speedLevel();
  coo.x = this->coord.back().x;
  coo.y = this->coord.back().y;
  this->coord.push_back(coo);
}

void		Snake::removeLink()
{
  this->coord.pop_back();
}

void		Snake::setSpeed(int const _speed)
{
  this->speed = _speed;
  if (this->speed < 0)
    this->speed = 0;
}

int		Snake::getSpeed() const
{
  return (this->speed);
}

void		Snake::setSpeedSpace()
{
  this->setSpeed(this->getSpeed() - 10000);
  this->speedinc += 10000;
  this->speedcooldown = this->getTime(3);
}

void		Snake::checkSpeedSpace()
{
  if (this->speedinc != 0 && this->isCooldown(this->speedcooldown) == true)
    {
      this->setSpeed(this->getSpeed() + this->speedinc);
      this->speedinc = 0;
    }
}

void		Snake::speedLevel()
{
  this->setSpeed(this->getSpeed() - 5000);
}

void		Snake::increaseSpeed()
{
  this->stats.increase(RABBITFOOD);
  this->setSpeed(this->getSpeed() - 20000);
}

void		Snake::decreaseSpeed()
{
  this->stats.increase(TURTLEFOOD);
  this->setSpeed(this->getSpeed() + 40000);
}

void		Snake::setPassMuraille()
{
  this->stats.increase(PASSMURAILLE);
  this->config[PASSMURAILLE].active = true;
  if (this->isCooldown(this->config[PASSMURAILLE].cooldown) == true)
    this->config[PASSMURAILLE].cooldown = this->getTime(10);
  else
    this->config[PASSMURAILLE].cooldown += 10;
}

bool		Snake::isPassMuraille()
{
  if (this->config[PASSMURAILLE].active == true &&
      this->isCooldown(this->config[PASSMURAILLE].cooldown) == false)
    return (true);
  this->config[PASSMURAILLE].active = false;
  return (false);
}

void		Snake::setInsolation()
{
  this->stats.increase(INSOLATION);
  this->config[INSOLATION].active = true;
  if (this->isCooldown(this->config[INSOLATION].cooldown) == true)
    this->config[INSOLATION].cooldown = this->getTime(20);
  else
    this->config[INSOLATION].cooldown += 20;
}

bool		Snake::isInsolation()
{
  if (this->config[INSOLATION].active == true &&
      this->isCooldown(this->config[INSOLATION].cooldown) == false)
    return (true);
  this->config[INSOLATION].active = false;
  return (false);
}

void		Snake::setPoisonFood()
{
  this->stats.increase(POISONFOOD);
  this->config[POISONFOOD].active = true;
  if (this->isCooldown(this->config[POISONFOOD].cooldown) == true)
    this->config[POISONFOOD].cooldown = this->getTime(60);
  else
    this->config[POISONFOOD].cooldown += 60;
  this->poison += 60;
}

bool		Snake::isPoisonFood()
{
  if (this->config[POISONFOOD].active == true &&
      this->isCooldown(this->config[POISONFOOD].cooldown) == false)
    return (true);
  this->config[POISONFOOD].active = false;
  return (false);
}

int		Snake::checkPoisonFood(int const deus)
{
  if (this->isPoisonFood() == true &&
      (this->poison >= this->getCooldown(this->config[POISONFOOD].cooldown)))
    {
      this->poison -= 10;
      this->removeLink();
      if (this->coord.size() == 0)
	return (2);
    }
  return (deus);
}

int		Snake::getCooldown(time_t const val) const
{
  return (difftime(val, time(NULL)));
}

bool		Snake::isCooldown(time_t const val) const
{
  return ((difftime(val, time(NULL)) > 0) ? (false) : (true));
}

void		Snake::setUsername(std::string username)
{
  this->stats.setUsername(username);
}

time_t		Snake::getTime(int const val) const
{
  time_t	timer;

  if (time(&timer) == -1)
    throw std::logic_error("Error during set Cooldown.");
  timer += val;
  return (timer);
}

void		Snake::move()
{
  int		i;

  i = this->coord.size();
  while (--i > 0)
    this->coord[i] = this->coord[i - 1];
}

void		Snake::changeDirection(t_event const event)
{
  this->stats.updateSize(this->coord.size() - 1);
  this->checkSpeedSpace();
  if (this->keymap == 0)
    {
      this->twoDirection(event);
      return ;
    }
  if (event == SAME)
    {
      this->fourDirection(this->prev);
      return ;
    }
  this->prev = event;
  this->fourDirection(this->prev);
}

void		Snake::twoDirection(t_event const event)
{
  if (event == SAME)
    {
      this->fourDirection(this->prev);
      return ;
    }
  if (event == RIGHT)
    {
      this->prev = (this->prev == 3 ? static_cast<t_event>(this->prev - 3)
		    : static_cast<t_event>(this->prev + 1));
      this->fourDirection(this->prev);
    }
  else if (event == LEFT)
    {
      this->prev = (this->prev == 0 ? static_cast<t_event>(this->prev + 3)
		    : static_cast<t_event>(this->prev - 1));
      this->fourDirection(this->prev);
    }
}

void		Snake::fourDirection(t_event const event)
{
  int		i;

  i = -1;
  while (++i < 4)
    if (event == type[i])
      this->isInsolation() == true ? (this->*(fptrIns[i]))() : (this->*(fptr[i]))();
}

void		Snake::left()
{
  int		x;

  x = this->coord[0].x;
  if (this->isPassMuraille() == true)
    (x - 1 == 0) ? (x = (this->width) - 1) : (--x);
  else
    --x;
  this->coord[0].x = x;
}

void		Snake::right()
{
  int		x;

  x = this->coord[0].x;
  if (this->isPassMuraille() == true)
    (x + 1 == this->width) ? (x = 1) : (++x);
  else
    ++x;
  this->coord[0].x = x;
}

void		Snake::up()
{
  int		y;

  y = this->coord[0].y;
  if (this->isPassMuraille() == true)
    (y - 1 == 0) ? (y = (this->height) - 1) : (--y);
  else
    --y;
  this->coord[0].y = y;
}

void		Snake::down()
{
  int		y;

  y = this->coord[0].y;
  if (this->isPassMuraille() == true)
    (y + 1 == this->height) ? (y = 1) : (++y);
  else
    ++y;
  this->coord[0].y = y;
}

Stats		Snake::getStats() const
{
  return (this->stats);
}

void		Snake::debug() const
{
  int           i;
  int           size;

  size = this->coord.size();
  i = -1;
  while (++i < size)
    {
      std::cout << "["<< this->coord[i].x << "][" << this->coord[i].y << "]" << std::endl;
    }
}
