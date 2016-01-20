//
// Stats.hh for  in /home/maillo_a/rendu/cpp_nibbler
// 
// Made by Flavien Maillot
// Login   <maillo_a@epitech.net>
// 
// Started on  Mon Mar 30 12:01:24 2015 Flavien Maillot
// Last update Sun Apr  5 12:30:10 2015 Flavien Maillot
//

#ifndef STATS_HH_
# define STATS_HH_

# include <iostream>
# include <map>
# include <iterator>
# include "Emap.hh"

class Stats
{
private:
  bool			active;
  std::string		username;
  int			maxsize;
  int			minsize;
  std::map<t_emap, int>	food;
public:
  Stats(const std::string& _username="Anonymous");
  ~Stats();

  std::string	getUsername() const;
  void		setUsername(const std::string& _username);
  void		setStats(const bool);
  void		increase(t_emap);
  void		updateMaxSize(const int);
  int		getMaxSize() const;
  void		updateMinSize(const int);
  int		getMinSize() const;
  void		updateSize(const int);

  void		display() const;
};

#endif /* !STATS_HH_ */
