//
// main.cpp for  in /home/athoma_j/rendu/cpp_nibbler
// 
// Made by julien athomas
// Login   <athoma_j@epitech.net>
// 
// Started on  Sun Apr  5 22:31:48 2015 julien athomas
// Last update Sun Apr  5 22:32:09 2015 julien athomas
//

#include "Nibbler.hh"

int	main(int ac, char **av)
{
  if (ac != 4)
    {
      std::cerr << "\033[0;31;40mUsage: " << std::string(av[0]) << " HEIGHT WIDTH LIBRARY \033[0m" << std::endl;
      return (1);
    }
  try {
    std::string a(av[1]);
    std::string b(av[2]);
    std::string c(av[3]);
    Nibbler nibbler(a, b, c);
    nibbler.run();
  }
  catch (std::exception & e)
    {
      std::cerr << "\033[0;31;40m" << e.what() << "\033[0m" << std::endl;
      return (1);
    }
  return (0);
}
