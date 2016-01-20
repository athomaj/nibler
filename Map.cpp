//
// Map.cpp for  in /home/maillo_a/rendu/cpp_nibbler
// 
// Made by Flavien Maillot
// Login   <maillo_a@epitech.net>
// 
// Started on  Wed Apr  1 16:52:42 2015 Flavien Maillot
// Last update Sun Apr  5 23:21:50 2015 julien athomas
//

#include <cstdio>
#include "Map.hh"

Map::Map()
{
}

Map::~Map()
{
}

std::vector<t_map>&	Map::updateMap()
{
  return (this->map);
}

const std::vector<t_map>&	Map::getMap() const
{
  return (this->map);
}

void		Map::init()
{
  this->conf.insert(std::pair<t_emap, t_mapcnf>(FOOD,
						this->constructConf(NBFOOD, COFOOD, LAFOOD, LUFOOD)));
  this->conf.insert(std::pair<t_emap,
		    t_mapcnf>(FASTFOOD,
			      this->constructConf(NBFASTFOOD, COFASTFOOD, LAFASTFOOD, LUFASTFOOD)));
  this->conf.insert(std::pair<t_emap,
		    t_mapcnf>(RANDFOOD,
			      this->constructConf(NBRANDFOOD, CORANDFOOD, LARANDFOOD, LURANDFOOD)));
  this->conf.insert(std::pair<t_emap,
		    t_mapcnf>(POISONFOOD,
			      this->constructConf(NBPOISONFOOD, COPOISONFOOD, LAPOISONFOOD, LUPOISONFOOD)));
  this->conf.insert(std::pair<t_emap,
		    t_mapcnf>(PASSMURAILLE,
			      this->constructConf(NBPASSMURAILLE, COPASSMURAILLE, LAPASSMURAILLE, LUPASSMURAILLE)));
  this->conf.insert(std::pair<t_emap,
		    t_mapcnf>(TURTLEFOOD,
			      this->constructConf(NBTURTLEFOOD, COTURTLEFOOD, LATURTLEFOOD, LUTURTLEFOOD)));
  this->conf.insert(std::pair<t_emap,
		    t_mapcnf>(RABBITFOOD,
			      this->constructConf(NBRABBITFOOD, CORABBITFOOD, LARABBITFOOD, LURABBITFOOD)));
  this->conf.insert(std::pair<t_emap,
		    t_mapcnf>(INSOLATION,
			      this->constructConf(NBINSOLATION, COINSOLATION, LAINSOLATION, LUINSOLATION)));
  this->conf.insert(std::pair<t_emap,
		    t_mapcnf>(WALL, this->constructConf(1, 86400, 0, 100)));
}

t_mapcnf	Map::constructConf(const int qte, const int cooldown, const int laptime, const int luck) const
{
  t_mapcnf	conf;

  conf.active = true;
  conf.qte = qte;
  conf.cooldown = cooldown;
  conf.laptime = laptime;
  conf.luck = luck;
  conf.nextappear = this->getLaptime(laptime);
  return (conf);
}

void		Map::updateConf(const t_emap type, const int qte, const int cooldown, const int laptime, const int luck)
{
  this->conf[type].qte = qte;
  this->conf[type].cooldown = cooldown;
  this->conf[type].laptime = laptime;
  this->conf[type].luck = luck;
  this->conf[type].nextappear = this->getLaptime(laptime);
}

void		Map::reduceQte()
{
  std::map<t_emap, t_mapcnf>::iterator it;

  it = this->conf.begin();
  while (it != conf.end())
    {
      if (it->second.qte > 1)
	this->setQte(it->first, 1);
      ++it;
    }
}

void		Map::setQte(const t_emap type, const int val)
{
  this->conf[type].qte = val;
}

void		Map::setActive(const bool etat)
{
  this->active = etat;
}

void		Map::setWidth(const int _width)
{
  this->width = _width;
}

int		Map::getWidth() const
{
  return (this->width);
}

void		Map::setHeight(const int _height)
{
  this->height = _height;
}

int		Map::getHeight() const
{
  return (this->height);
}

void		Map::checkAndUpdate(Snake const& snake)
{
  this->checkCooldown(snake);
  this->checkAndGenerate(snake);
}

void		Map::checkAndGenerate(Snake const& snake)
{
  std::map<t_emap, t_mapcnf>::iterator it;

  it = this->conf.begin();
  while (it != conf.end())
    {
      if (it->second.active == true && this->isLaptime(it->second) == true)
	{
	  if (this->checkLuck(it->second.luck) == true)
	    {
	      this->generateElem(snake, it->first, it->second.qte);
	    }
	  else
	    it->second.nextappear = this->getLaptime(it->second.laptime);
	}
      ++it;
    }
}

bool		Map::checkLuck(const int luck) const
{
  int		val;

  val = rand() % 100;
  if (val < luck)
    return (true);
  return (false);
}

void		Map::checkCooldown(Snake const& snake)
{
  int		i;
  int		size;

  i = -1;
  size = this->map.size();
  while (++i < size)
    {
      if (this->isCooldown(this->map[i]) == true)
	{
	  this->eraseObj(snake, i);
	  size = this->map.size();
	  --i;
	}
    }
}

time_t		Map::getCooldown(const t_emap type)
{
  time_t	timer;

  if (time(&timer) == -1)
    throw std::logic_error("Error during set Cooldown.");

  timer += this->conf[type].cooldown;
  return (timer);
}

bool		Map::isCooldown(t_map const& point) const
{
  return ((difftime(point.cooldown, time(NULL)) > 0) ? (false) : (true));
}

time_t		Map::getLaptime(int const laptime) const
{
  time_t	timer;

  if (time(&timer) == -1)
    throw std::logic_error("Error during set Cooldown.");
  timer += laptime;
  return (timer);
}

bool		Map::isLaptime(t_mapcnf const& conf) const
{
  return ((difftime(conf.nextappear, time(NULL)) > 0) ? (false) : (true));
}

bool		Map::snakeCollision(Snake& snake, int const x, int const y) const
{
  int		i;
  int		size;

  i = 0;
  size = snake.updateCoord().size();
  while (++i < size - 1)
    {
      if ((snake.updateCoord())[i].x == x &&
	  (snake.updateCoord())[i].y == y)
	return (true);
    }
  return (false);
}

bool		Map::headCollision(Snake& snake, int const x, int const y) const
{
  if (snake.updateCoord().front().x == x &&
      snake.updateCoord().front().y == y)
    return (true);
  return (false);
}

t_emap		Map::inCollision(Snake& snake, int const x, int const y)
{
  int		i;
  int		max;

  if (x == 0 || x == this->width || y == 0 || y == this->height)
    return (WALL);
  i = -1;
  max = this->map.size();
  while (++i < max)
    {
      if (this->map[i].x == x && this->map[i].y == y)
	{
	  if (this->active == true && (this->map[i].type == FOOD ||
				       this->map[i].type == FASTFOOD ||
				       this->map[i].type == RANDFOOD ||
				       this->map[i].type == POISONFOOD ||
				       this->map[i].type == PASSMURAILLE ||
				       this->map[i].type == TURTLEFOOD ||
				       this->map[i].type == RABBITFOOD ||
				       this->map[i].type == INSOLATION))
	    {
	      return (this->eraseObj(snake, i));
	    }
	  if (this->map[i].type == WALL && snake.isPassMuraille() == true)
	    return (EMPTY);
	  return (this->map[i].type);
	}
    }
  if (this->snakeCollision(snake, x, y) == true)
    return (WALL);
  return (EMPTY);
}

bool		Map::inFullCollision(Snake& snake, int const x, int const y)
{
  if (this->inCollision(snake, x, y) != EMPTY)
    return (true);
  return (this->headCollision(snake, x, y));
}

void		Map::setObj(t_emap const type, int const posx, int const posy)
{
  t_map		point;

  point.type = type;
  point.x = posx;
  point.y = posy;
  point.cooldown = this->getCooldown(type);
  this->map.push_back(point);
}

t_emap		Map::eraseObj(__attribute__((unused))Snake const& snake, int const i)
{
  t_emap	typefood;

  typefood = this->map[i].type;
  this->map.erase(this->map.begin() + i);
  this->conf[typefood].active = true;
  this->conf[typefood].nextappear = this->getLaptime(this->conf[typefood].laptime);
  return (typefood);
}

void		Map::generateElem(Snake snake, t_emap const elem, int const nb)
{
  int		i;
  int		x;
  int		y;
  int		limit;

  this->active = false;
  i = -1;
  limit = -1;
  while (++i < nb && limit < LIMITGEN)
    {
      ++limit;
      x = rand() % (this->width - 1) + 1;
      y = rand() % (this->height - 1) + 1;
      if (this->inFullCollision(snake, x, y) == false)
	this->setObj(elem, x, y);
      else
	--i;
    }
  this->conf[elem].active = false;
  this->active = true;
}

bool		Map::generate(Snake& snake)
{
  srand(time(NULL));
  this->generateElem(snake, FOOD, this->conf[FOOD].qte);
  this->generateElem(snake, FASTFOOD, this->conf[FASTFOOD].qte);
  this->generateElem(snake, RANDFOOD, this->conf[RANDFOOD].qte);
  this->generateElem(snake, POISONFOOD, this->conf[POISONFOOD].qte);
  this->generateElem(snake, PASSMURAILLE, this->conf[PASSMURAILLE].qte);
  this->generateElem(snake, TURTLEFOOD, this->conf[TURTLEFOOD].qte);
  this->generateElem(snake, RABBITFOOD, this->conf[RABBITFOOD].qte);
  this->generateElem(snake, INSOLATION, this->conf[INSOLATION].qte);
  this->generateElem(snake, WALL, this->conf[WALL].qte);
  this->reduceQte();
  return (true);
}

void		Map::debug() const
{
  int		i;
  int		size;

  size = this->map.size();
  i = -1;
  while (++i < size)
    {
      std::cout << "x["<< this->map[i].x << "]y[" << this->map[i].y << "] T = " << this->map[i].type << std::endl;
    }

  std::map<t_emap, t_mapcnf>::const_iterator it;

  it = this->conf.begin();
  while (it != conf.end())
    {
      std::cout << it->first << " " << it->second.active << " " << it->second.qte << " " << std::endl;
      ++it;
    }
}
