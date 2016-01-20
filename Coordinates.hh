//
// Coordinates.hh for  in /home/maillo_a/rendu/cpp_nibbler
// 
// Made by Flavien Maillot
// Login   <maillo_a@epitech.net>
// 
// Started on  Tue Mar 31 18:35:14 2015 Flavien Maillot
// Last update Sun Apr  5 12:13:51 2015 Flavien Maillot
//

#ifndef COORDINATES_HH_
# define COORDINATES_HH_

typedef struct	s_coord
{
  int		x;
  int		y;
}		t_coord;

class Coordinates
{
private:
  int	x;
  int	y;
public:
  Coordinates(int, int);
  ~Coordinates();

  int	getX() const;
  void	setX(const int);
  int	getY() const;
  void	setY(const int);
  int&	updateX();
  int&	updateY();
};

#endif /* !COORDINATES_HH_ */
