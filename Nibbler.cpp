//
// nibbler.cpp for Nibbler in /home/ferrei_e/cpp_nibbler
// 
// Made by Ferreira Cintia
// Login   <ferrei_e@epitech.net>
// 
// Started on  Wed Mar 11 16:07:30 2015 Ferreira Cintia
// Last update Sun Apr  5 22:32:06 2015 julien athomas
//

#include <unistd.h>
#include "Nibbler.hh"

Nibbler::Nibbler(std::string const& _height, std::string const& _width, std::string const& _library)
{
  DLLoader	<IDisplayModule>*dlloader =
    new DLLoader<IDisplayModule>(_library, std::string("getLib"));

  instance = dlloader->getInstance();
  this->is_numeric(_height);
  this->is_numeric(_width);
  this->pause = false;

  this->map.setWidth(atoi(_width.c_str()));
  this->map.setHeight(atoi(_height.c_str()));

  this->type[0] = FOOD;
  this->type[1] = FASTFOOD;
  this->type[2] = RANDFOOD;
  this->type[3] = PASSMURAILLE;
  this->type[4] = TURTLEFOOD;
  this->type[5] = RABBITFOOD;
  this->type[6] = INSOLATION;
  this->type[7] = POISONFOOD;

  this->fptr[0] = &Snake::addFoodLink;
  this->fptr[1] = &Snake::addFastLink;
  this->fptr[2] = &Snake::addRandLink;
  this->fptr[3] = &Snake::setPassMuraille;
  this->fptr[4] = &Snake::decreaseSpeed;
  this->fptr[5] = &Snake::increaseSpeed;
  this->fptr[6] = &Snake::setInsolation;
  this->fptr[7] = &Snake::setPoisonFood;
}

Nibbler::~Nibbler()
{
}

int	Nibbler::getHeight() const
{
  return (this->height);
}

int	Nibbler::getWidth() const
{
  return (this->width);
}

IDisplayModule*	Nibbler::getInstance() const
{
  return (this->instance);
}

bool		Nibbler::is_numeric(std::string const& value) const
{
  int		i;

  i = -1;
  while (++i < static_cast<int>(value.length()))
    if (isdigit(value[i]) == false)
      {
	if (i == 0 && value[i] == '-')
	  throw std::logic_error("Negative Value forbidden.");
	return (false);
      }
  return (true);
}

int		Nibbler::checkCollision()
{
  t_emap	status;
  int		i;

  status = this->map.inCollision(this->snake, (this->snake.updateCoord()[0]).x,
				 (this->snake.updateCoord()[0]).y);
  if (status == WALL)
    return (1);
  i = -1;
  while (++i < 8)
    if (type[i] == status)
      (this->snake.*(fptr[i]))();
  return (42);
}

void		Nibbler::initAlgo(t_event& direction, t_event& current, Parser& parser)
{
  this->instance->init(this->map.getWidth(), this->map.getHeight());
  this->snake.setSnake(this->map.getWidth(), this->map.getHeight(), 4);
  this->map.init();
  parser.run(this->snake, this->map);
  this->map.generate(this->snake);
  current = RIGHT;
  direction = current;
}

void		Nibbler::checkCurPos(t_event& direction, t_event& current, int& deus)
{
  current = this->instance->getEvent(SAME);
  if (current == LEFT || current == RIGHT || current == UP || current == DOWN || current == SAME)
    direction = current;
  else if (current == ESC || current == QUIT)
    deus = 0;
  else if (current == SPACE)
    this->snake.setSpeedSpace();
  else if (current == PAUSE)
    {
      this->pause = this->pause == true ? false : true;
      direction = SAME;
    }
}

bool		Nibbler::run()
{
  Parser	parser;
  t_event direction;
  t_event current;
  int deus = 42;

  initAlgo(direction, current, parser);
  while (deus == 42)
    {
      if (this->pause == false)
	this->snake.move();
      this->instance->display(this->snake.updateCoord(), this->map.getMap());
      if (this->pause == false)
	this->snake.changeDirection(direction);
      checkCurPos(direction, current, deus);
      if (deus != 0 && this->pause == false)
	{
	  deus = this->checkCollision();
	  this->map.checkAndUpdate(this->snake);
	  deus = this->snake.checkPoisonFood(deus);
	}
      usleep(this->snake.getSpeed());
    }
  return (endGame(deus));
}

bool		Nibbler::endGame(int const deus)
{
  this->instance->stop();
  if (deus == 0)
    std::cout << "Jeu quitté." << std::endl;
  else if (deus == 1)
    std::cout << "Touche un mur.\n" << std::endl;
  this->snake.getStats().display();
  return (true);
}
