//
// Opengl.cpp for  in /Users/julien/rendu/cpp_nibbler/library/libopengl
// 
// Made by julien athomas
// Login   <julien@epitech.net>
// 
// Started on  Thu Apr  2 14:39:54 2015 julien athomas
// Last update Sun Apr  5 23:37:12 2015 julien athomas
//

#include "Opengl.hh"

t_event g_event = RIGHT;
float eyey=4.0f, eyez = 10.0f;

OpenGL::OpenGL() :
  name("OpenGL")
{
  this->type[0] = FOOD;
  this->type[1] = FASTFOOD;
  this->type[2] = RANDFOOD;
  this->type[3] = POISONFOOD;
  this->type[4] = PASSMURAILLE;
  this->type[5] = TURTLEFOOD;
  this->type[6] = RABBITFOOD;
  this->type[7] = INSOLATION;
  this->type[8] = WALL;

  this->fptr[0] = &OpenGL::colorFood;
  this->fptr[1] = &OpenGL::colorFastFood;
  this->fptr[2] = &OpenGL::colorRandFood;
  this->fptr[3] = &OpenGL::colorPoisonFood;
  this->fptr[4] = &OpenGL::colorPassMur;
  this->fptr[5] = &OpenGL::colorTurtleFood;
  this->fptr[6] = &OpenGL::colorRabbitFood;
  this->fptr[7] = &OpenGL::colorInsolation;
  this->fptr[8] = &OpenGL::colorWall;
}

void	OpenGL::colorFood() const
{
  glColor3f(1, 0, 0);
}

void	OpenGL::colorFastFood() const
{
  glColor3f(0, 1, 0);
}

void	OpenGL::colorRandFood() const
{
  glColor3f(0, 0, 1);
}

void	OpenGL::colorPoisonFood() const
{
  glColor3f(1, 1, 0);
}

void	OpenGL::colorPassMur() const
{
  glColor3f(0, 1, 1);
}

void	OpenGL::colorTurtleFood() const
{
  glColor3f(1, 1, 1);
}

void	OpenGL::colorRabbitFood() const
{
  glColor3f(0.3, 0.6, 0.5);
}

void	OpenGL::colorInsolation() const
{
  glColor3f(0, 0.8, 0.8);
}

void	OpenGL::colorWall() const
{
  glColor3f(0.5, 0.5, 0.5);
}

OpenGL::~OpenGL()
{

}

std::string const& OpenGL::getName() const
{
  return (this->name);
}

void    upEvent()
{
  g_event = UP;
}

void	downEvent()
{
  g_event = DOWN;
}

void	rightEvent()
{
  g_event = RIGHT;
}

void	leftEvent()
{
  g_event = LEFT;
}

void		OpenGL::foodColor(int const type)
{
  int		i;

  i = -1;
  while (++i < 9)
    if (type == this->type[i])
      {
	(this->*(fptr[i]))();
	return ;
      }
}

void		OpenGL::drawStuff(const std::vector<t_map>& map)
{
  unsigned int	i;
  float		tmpx;
  float		tmpy;

  i = -1;
  while (++i < map.size())
    {
      tmpx = static_cast<float>(map[i].x) / 10.0 - (this->width / 20.0);
      tmpy = static_cast<float>(map[i].y) / 10.0 - (this->height / 20.0);
      glPushMatrix();
      foodColor(map[i].type);
      glTranslatef(tmpx, 0.0f, tmpy);
      glutSolidSphere(0.07f,10,10);
      glPopMatrix();
    }
}

void		OpenGL::drawPlane(const std::vector<t_map>& map)
{
  float	z;
  float size;

  drawStuff(map);
  size = this->width / 20.0;
  glPushMatrix();
  glColor3f(0.7, 0.7, 0.7);
  glBegin(GL_LINES);
  z = -(this->height / 20.0);
  while (z <= this->height / 20.0)
    {
      glVertex3f(-size, 0.0, z);
      glVertex3f(size, 0.0, z);
      z += 0.25;
    }
  z = -size;
  while (z <= size)
    {
      glVertex3f(z, 0.0, -this->height / 20.0);
      glVertex3f(z, 0.0, this->height / 20.0);
      z += 0.25;
    }
  glEnd();
  glPopMatrix();
}

void		OpenGL::drawSnake(std::vector<t_coord>& snake) const
{
  unsigned int	i;
  float	tmpx;
  float	tmpy;

  i = 0;
  tmpx = snake[i].x / 10.0 - (this->width / 20.0);
  tmpy = snake[i].y / 10.0 - (this->height / 20.0);
  glPushMatrix();
  glColor3f(0, 1, 0);
  glTranslatef(tmpx, 0.0f, tmpy);
  glutSolidSphere(0.1f,15,15);
  glPopMatrix();
  while (++i < snake.size())
    {
      tmpx = snake[i].x / 10.0 - (this->width / 20.0);
      tmpy = snake[i].y / 10.0 - (this->height / 20.0);
      glPushMatrix();
      glColor3f(0, 0, 1);
      glTranslatef(tmpx, 0.0f, tmpy);
      glutSolidSphere(0.1f,10,10);
      glPopMatrix();
    }
}

void renderScene()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  gluLookAt(0, eyey, eyez,
  	    0, 0, 0,
  	    0.0f, 1.0f,  0.0f);
  glutSwapBuffers();
}

void	quitEvent()
{
  g_event = QUIT;
}

void	spaceEvent()
{
  g_event = SPACE;
}

void    incCamY()
{
  eyey += 0.1f;
}

void	decCamY()
{
  eyey -= 0.1f;
}

void	incCamZ()
{
  eyez += 0.1f;
}

void	decCamZ()
{
  eyez -= 0.1f;
}

void	myPause()
{
  g_event = PAUSE;
}

void processNormalKeys(unsigned char key, UNUSED int x, UNUSED int y)
{
  void		(*fptr[7])();
  unsigned char	type[7];
  int		i;

  fptr[0] = &quitEvent;
  fptr[1] = &spaceEvent;
  fptr[2] = &incCamY;
  fptr[3] = &decCamY;
  fptr[4] = &incCamZ;
  fptr[5] = &decCamZ;
  fptr[6] = &myPause;
  type[0] = 27;
  type[1] = ' ';
  type[2] = 'z';
  type[3] = 's';
  type[4] = 'q';
  type[5] = 'd';
  type[6] = 8;

  i = -1;
  while (++i < 7)
    if (type[i] == key)
      {
	fptr[i]();
	return ;
      }
}

void processSpecialKeys(int key, UNUSED int xx, UNUSED int yy)
{
  void		(*fptr[4])();
  int		type[4];
  int		i;

  fptr[0] = &upEvent;
  fptr[1] = &downEvent;
  fptr[2] = &rightEvent;
  fptr[3] = &leftEvent;
  type[0] = GLUT_KEY_UP;
  type[1] = GLUT_KEY_DOWN;
  type[2] = GLUT_KEY_RIGHT;
  type[3] = GLUT_KEY_LEFT;
  i = -1;
  while (++i < 4)
    if (type[i] == key)
      {
	fptr[i]();
	return ;
      }
}

void changeSize(int w, int h)
{
  float ratio;

  ratio = w * 1.0 / h;
  if (h == 0)
    h = 1;
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glViewport(0, 0, w, h);
  gluPerspective(45,ratio,1,100);
  glMatrixMode(GL_MODELVIEW);
}

void OpenGL::render(std::vector<t_coord>& snake, const std::vector<t_map>& map)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  gluLookAt(0, eyey, eyez,
  	    0, 0, 0,
  	    0.0f, 1.0f,  0.0f);
  drawPlane(map);
  drawSnake(snake);
  glutSwapBuffers();
}

void	OpenGL::init(const int width, const int height)
{
  int argc = 1;
  char *argv[1];

  argv[0] = strdup("nibbler");
  this->width = width;
  this->height = height;
  check();
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowPosition(100,100);
  glutInitWindowSize(width * 20, height * 20);
  glutCreateWindow("Opengl-Nibbler");
  glutDisplayFunc(renderScene);
  glutReshapeFunc(changeSize);
  glutIdleFunc(renderScene);
  glutKeyboardFunc(processNormalKeys);
  glutSpecialFunc(processSpecialKeys);
  glEnable(GL_DEPTH_TEST);
}

void	OpenGL::stop()
{

}

void	OpenGL::display(std::vector<t_coord>& snake, const std::vector<t_map>& map)
{
  this->render(snake, map);
  glutMainLoopEvent();
}

void	OpenGL::setSnake(UNUSED std::vector<t_coord>& snake, UNUSED int size)
{
}

t_event	OpenGL::getEvent(UNUSED t_event event)
{
  return (g_event);
}

void	OpenGL::check() const
{
  if (this->height > 400 || this->width > 400)
    throw std::logic_error("Windows size too Big");
  else if (this->height < 20 || this->width < 20)
    throw std::logic_error("Windows size too Small");
}

extern "C" IDisplayModule *	getLib()
{
  return (new OpenGL);
}
