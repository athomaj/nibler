//
// sdl.cpp for nibbler in /home/ferrei_e/cpp_nibbler/library/libSDL
// 
// Made by Ferreira Cintia
// Login   <ferrei_e@epitech.net>
// 
// Started on  Mon Mar 30 17:41:26 2015 Ferreira Cintia
// Last update Sun Apr  5 22:51:27 2015 Ferreira Cintia
//

#include "Sdl.hh"

Sdl::Sdl()
{
  this->name = std::string("Sdl");
  this->framerate = 32;

  this->type[0] = FOOD;
  this->type[1] = FASTFOOD;
  this->type[2] = RANDFOOD;
  this->type[3] = POISONFOOD;
  this->type[4] = PASSMURAILLE;
  this->type[5] = TURTLEFOOD;
  this->type[6] = RABBITFOOD;
  this->type[7] = INSOLATION;
  this->type[8] = WALL;

  this->fptr[0] = &Sdl::imgFood;
  this->fptr[1] = &Sdl::imgFastFood;
  this->fptr[2] = &Sdl::imgRandFood;
  this->fptr[3] = &Sdl::imgPoisonFood;
  this->fptr[4] = &Sdl::imgPassMur;
  this->fptr[5] = &Sdl::imgTurtleFood;
  this->fptr[6] = &Sdl::imgRabbitFood;
  this->fptr[7] = &Sdl::imgInsolation;
  this->fptr[8] = &Sdl::imgWall;

  this->keyType[0] = SDLK_ESCAPE;
  this->keyType[1] = SDLK_RIGHT;
  this->keyType[2] = SDLK_LEFT;
  this->keyType[3] = SDLK_UP;
  this->keyType[4] = SDLK_DOWN;
  this->keyType[5] = SDLK_SPACE;
  this->keyType[6] = SDLK_BACKSPACE;

  this->keyFptr[0] = &Sdl::escape;
  this->keyFptr[1] = &Sdl::right;
  this->keyFptr[2] = &Sdl::left;
  this->keyFptr[3] = &Sdl::up;
  this->keyFptr[4] = &Sdl::down;
  this->keyFptr[5] = &Sdl::space;
  this->keyFptr[6] = &Sdl::pause;
}

Sdl::~Sdl()
{

}

t_event	Sdl::escape() const
{
  return (ESC);
}

t_event	Sdl::space() const
{
  return (SPACE);
}

t_event	Sdl::pause() const
{
  return (PAUSE);
}

t_event	Sdl::right() const
{
  return (RIGHT);
}

t_event	Sdl::left() const
{
  return (LEFT);
}

t_event	Sdl::up() const
{
  return (UP);
}

t_event	Sdl::down() const
{
  return (DOWN);
}

void    Sdl::imgFood(std::string& name) const
{
  name = FOODBMP;
}

void    Sdl::imgFastFood(std::string& name) const
{
  name = FASTFOODBMP;
}

void    Sdl::imgRandFood(std::string& name) const
{
  name = RANDFOODBMP;
}

void    Sdl::imgPoisonFood(std::string& name) const
{
  name = POISONFOODBMP;
}

void    Sdl::imgPassMur(std::string& name) const
{
  name = PASSMURBMP;
}

void    Sdl::imgTurtleFood(std::string& name) const
{
  name = TURTLEFOODBMP;
}

void    Sdl::imgRabbitFood(std::string& name) const
{
  name = RABBITFOODBMP;
}

void    Sdl::imgInsolation(std::string& name) const
{
  name = INSOLATIONBMP;
}

void    Sdl::imgWall(std::string& name) const
{
  name = WALLBMP;
}

const std::string&	Sdl::getName() const
{
  return (this->name);
}

bool	Sdl::check(const int height, const int width) const
{
  if (height < MIN || width < MIN || height > MAX || width > MAX)
    throw std::logic_error("Window impossible.");
  return (true);
}

void	Sdl::init(const int _width, const int _height)
{
  this->check(_height, _width);
  width = _width;
  height = _height;
  if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
      std::cout << "Error SDL_Init" << std::endl;
      exit(0);
    }
  this->window = SDL_SetVideoMode((_width * 10), (_height * 10), this->framerate, SDL_HWSURFACE);
  if (this->window == NULL)
    std::cout << "Error SDL_SetVideoMode" << std::endl;
  SDL_WM_SetCaption("Snake", NULL);
  SDL_FillRect(this->window, NULL, 0x000000);
  objet = SDL_CreateRGBSurface(0, 20, 20, 32, 0, 0, 0, 0);
}

void	Sdl::stop()
{
  SDL_FreeSurface(objet);
  SDL_FreeSurface(window);
  SDL_Quit();
}

void		Sdl::display(std::vector<t_coord>& snake, const std::vector<t_map>& map)
{
  unsigned int	i;
  SDL_Rect	pos;

  SDL_FillRect(this->window, NULL, 0x000000);
  displayMap(map);
  pos.x = snake[0].x * 10;
  pos.y = snake[0].y * 10;
  SDL_FillRect(objet, NULL, SDL_MapRGB(objet->format, 0, 255, 0));
  SDL_BlitSurface(objet, NULL, this->window, &pos);
  i = 1;
  while (++i < snake.size())
    {
      pos.x = snake[i].x * 10;
      pos.y = snake[i].y * 10;
      SDL_FillRect(objet, NULL, SDL_MapRGB(objet->format, 0, 0, 255));
      SDL_BlitSurface(objet, NULL, this->window, &pos);
    }
  SDL_Flip(this->window);
}

void		Sdl::whichImg(std::string& name, t_emap const type)
{
  int		i;

  i = -1;
  while (++i < 9)
    if (type == this->type[i])
      {
	(this->*(fptr[i]))(name);
	return ;
      }
}

void		Sdl::displayMap(const std::vector<t_map>& map)
{
  unsigned int	i;
  SDL_Rect	pos;
  SDL_Surface	*image;
  std::string	name;

  image = NULL;
  i = -1;
  while (++i < map.size())
    {
      pos.x = map[i].x * 10;
      pos.y = map[i].y * 10;
      whichImg(name, map[i].type);
      image = SDL_LoadBMP(name.c_str());
      SDL_SetColorKey(image, SDL_SRCCOLORKEY, SDL_MapRGB(image->format, 0, 0, 255));
      SDL_BlitSurface(image, NULL, this->window, &pos);
    }
}

t_event	Sdl::keyEvent(int const type)
{
  int	i;

  i = -1;
  while (++i < NBKEY)
    if (type == keyType[i])
      return ((this->*(keyFptr[i]))());
  return (SAME);
}

t_event	Sdl::getEvent(t_event current)
{
  SDL_Event event;

  SDL_PollEvent(&event);
  if (event.type == SDL_QUIT)
    return (QUIT);
  else if (event.type == SDL_KEYDOWN)
    return (keyEvent(event.key.keysym.sym));
  return (current);
}

extern "C" IDisplayModule*	getLib()
{
  IDisplayModule*	lib = new Sdl;

  return (lib);
}
