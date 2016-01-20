//
// DLLoader.hpp for  in /home/maillo_a/rendu/cpp_nibbler
// 
// Made by Flavien Maillot
// Login   <maillo_a@epitech.net>
// 
// Started on  Tue Mar 24 15:43:43 2015 Flavien Maillot
// Last update Sun Apr  5 18:52:34 2015 Ferreira Cintia
//

#ifndef DLLOADER_HPP_
# define DLLOADER_HPP_

# include <dlfcn.h>
# include <stdio.h>
# include "IDisplayModule.hh"

template <typename T>
class DLLoader
{
private:
  void		*handle;
  std::string	entryPoint;
public:
  DLLoader(std::string const& libName, std::string const& entryPoint)
  {
    if ((this->handle = dlopen(libName.c_str(), RTLD_LAZY)) == NULL)
      throw std::logic_error("Failed to open library.");
    this->entryPoint = entryPoint;
  }
  ~DLLoader()
  {
    dlclose(this->handle);
  }
  T* getInstance()
  {
    void	*func;
    T*		(*fdisp)();

    func = dlsym(this->handle, entryPoint.c_str());
    fdisp = reinterpret_cast<T* (*)()>(func);
    return (fdisp());
  }
};

#endif /* !DLLOADER_HPP_ */
