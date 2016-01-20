//
// Opengl.hh for  in /Users/julien/rendu/cpp_nibbler/library/libopengl
// 
// Made by julien athomas
// Login   <julien@epitech.net>
// 
// Started on  Thu Apr  2 14:40:19 2015 julien athomas
// Last update Sun Apr  5 16:05:08 2015 julien athomas
//

#ifndef OPENGL_HH_
# define OPENGL_HH_

# include <GL/glut.h>
# include <GL/freeglut.h>

# define UNUSED __attribute__((unused))
# include <cstring>
# include "../../Nibbler.hh"
# include <unistd.h>

class OpenGL : public IDisplayModule
{
public:
  OpenGL();
  ~OpenGL();
  virtual std::string const& getName() const;
  virtual void init(const int, const int);
  virtual void stop();
  virtual void display(std::vector<t_coord>& snake, const std::vector<t_map>& map);
  virtual void setSnake(std::vector<t_coord>& snake, int size);
  virtual t_event getEvent(t_event);
  void		render(std::vector<t_coord>& snake, const std::vector<t_map>& map);
  void		drawPlane(const std::vector<t_map>& map);
  void		drawSnake(std::vector<t_coord>& snake) const;
  void		drawStuff(const std::vector<t_map>& map);
  void		foodColor(int const);

  void		colorFood() const;
  void		colorFastFood() const;
  void		colorRandFood() const;
  void		colorPoisonFood() const;
  void		colorPassMur() const;
  void		colorTurtleFood() const;
  void		colorRabbitFood() const;
  void		colorInsolation() const;
  void		colorWall() const;
private:
  void		check() const;
  std::string	name;
  int		height;
  int		width;
  t_emap	type[9];
  void		(OpenGL::*fptr[9])() const;
};

#endif
