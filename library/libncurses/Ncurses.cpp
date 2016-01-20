//
// ncurses.cpp for  in /home/maillo_a/rendu/cpp_nibbler/library/libncurses
// 
// Made by Flavien Maillot
// Login   <maillo_a@epitech.net>
// 
// Started on  Mon Mar 30 10:42:55 2015 Flavien Maillot
// Last update Sun Apr  5 23:04:06 2015 julien athomas
//

#include "Ncurses.hh"

Ncurses::Ncurses()
{
  this->name = std::string("Ncurses");
  this->framerate = 25;

  this->type[0] = KEY_LEFT;
  this->type[1] = KEY_RIGHT;
  this->type[2] = KEY_UP;
  this->type[3] = KEY_DOWN;
  this->type[4] = 27;
  this->type[5] = 32;
  this->type[6] = KEY_BACKSPACE;

  this->fptr[0] = &Ncurses::keyLeft;
  this->fptr[1] = &Ncurses::keyRight;
  this->fptr[2] = &Ncurses::keyUp;
  this->fptr[3] = &Ncurses::keyDown;
  this->fptr[4] = &Ncurses::keyEsc;
  this->fptr[5] = &Ncurses::keySpace;
  this->fptr[6] = &Ncurses::keyBackSpace;

  this->foodType[0] = FOOD;
  this->foodType[1] = FASTFOOD;
  this->foodType[2] = RANDFOOD;
  this->foodType[3] = POISONFOOD;
  this->foodType[4] = PASSMURAILLE;
  this->foodType[5] = TURTLEFOOD;
  this->foodType[6] = RABBITFOOD;
  this->foodType[7] = INSOLATION;

  this->typeEq[0] = '*';
  this->typeEq[1] = 'o';
  this->typeEq[2] = '?';
  this->typeEq[3] = '!';
  this->typeEq[4] = '$';
  this->typeEq[5] = '-';
  this->typeEq[6] = '+';
  this->typeEq[7] = 'I';
  this->typeEq[8] = 'X';
}

Ncurses::~Ncurses()
{
}

t_event	Ncurses::keyUp()
{
  return (UP);
}

t_event	Ncurses::keyDown()
{
  return (DOWN);
}

t_event	Ncurses::keyLeft()
{
  return (LEFT);
}

t_event	Ncurses::keyRight()
{
  return (RIGHT);
}

t_event	Ncurses::keyEsc()
{
  return (ESC);
}

t_event	Ncurses::keySpace()
{
  return (SPACE);
}

t_event	Ncurses::keyBackSpace()
{
  return (PAUSE);
}

const std::string&	Ncurses::getName() const
{
  return (this->name);
}

bool	Ncurses::check(const int hmax, const int wmax, const int height, const int width)
{
  if (hmax < height ||
      wmax < width)
    {
      this->stop();
      throw std::logic_error("Windows size too small");
    }
  return (true);
}

void	Ncurses::init(const int _width, const int _height)
{
  if (initscr() == NULL)
    throw std::logic_error("Init Ncurses failled");
  noecho();
  cbreak();
  curs_set(0);
  timeout(this->framerate);
  keypad(stdscr, TRUE);

  this->height = _height;
  this->width = _width;
  this->starty = (LINES - this->height) / 2;
  this->startx = (COLS - this->width) / 2;
  this->check(LINES, COLS, height, width);

  this->window = newwin(this->height + 1, this->width + 1, this->starty, this->startx);
  printw("Press esc to exit.%d %d", LINES, height);
  printw("Legend:\n"				\
	 "* : Nourriture Normale\n"		\
	 "o : Nourriture temps d'apparition limité\n"	\
	 "? : Nombre de maillon gagnés variables\n"	\
	 "! : Poison, pendant 1 min, -1 maillon toutes les 10 secs\n"
	 "$ : Passe muraille\n"
	 "- : Tortue\n"
	 "+ : Lapin\n"
	 "I : Insolation\n"
	 "X : Mur\n");
  refresh();
}

void	Ncurses::stop()
{
  delwin(this->window);
  endwin();
}

void	Ncurses::display(std::vector<t_coord>& snake, const std::vector<t_map>& map)
{
  int   i;

  wclear(this->window);
  this->displayMap(map);
  i = snake.size();
  while (--i > 0)
    {
      if (i == 1)
	mvwaddch(window, snake[i].y, snake[i].x, '@');
      else
	mvwaddch(window, snake[i].y, snake[i].x, '#');
    }
  box(window, 0, 0);
  wrefresh(window);
}

void	Ncurses::displayMap(const std::vector<t_map>& map)
{
  int	i;
  int	size;
  int	j;

  size = map.size();
  i = -1;
  while (++i < size)
    {
      j = -1;
      while (++j < 8)
	if (map[i].type == foodType[j])
	  mvwaddch(this->window, map[i].y, map[i].x, typeEq[j]);
    }
  mvwaddch(this->window, map[i].y, map[i].x, typeEq[8]);
}

t_event		Ncurses::getEvent(t_event current)
{
  int		key;
  int		i;

  i = -1;
  key = getch();
  while (++i < 7)
    if (type[i] == key)
      return ((this->*(fptr[i]))());
  return (current);
}

extern "C" IDisplayModule *	getLib()
{
  return (new Ncurses);
}
