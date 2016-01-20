##
## Makefile for Nibbler in /home/ferrei_e/cpp_nibbler
## 
## Made by Ferreira Cintia
## Login   <ferrei_e@epitech.net>
## 
## Started on  Wed Mar 11 16:04:57 2015 Ferreira Cintia
## Last update Sun Apr  5 23:04:32 2015 julien athomas
##

SRCSDL=		libSDL/Sdl.cpp
SRCNCURSES=	libncurses/Ncurses.cpp
SRCOPENGL=	libopengl/Opengl.cpp

NAMESDL=	libsdl.so
NAMENCURSES=	libncurses.so
NAMEOPENGL=	libopengl.so

CC=		g++

RM=		rm -f

OBJSDL=		$(SRCSDL:.cpp=.o)
OBJNCURSES=	$(SRCNCURSES:.cpp=.o)
OBJOPENGL=	$(SRCOPENGL:.cpp=.o)


LIBSDL=		-lSDL

LIBOPENGL=	-lGL -lGLU -lglut

LIBNCURSES=	-lncurses

CXXFLAGS=	-W -Wall -Werror -Wextra -fPIC


all:	$(NAMENCURSES) $(NAMEOPENGL) $(NAMESDL)

$(NAMESDL):	$(OBJSDL)
		$(CC) -o $(NAMESDL) -shared $(OBJSDL) $(LIBSDL)

$(NAMENCURSES):	$(OBJNCURSES)
		$(CC) -o $(NAMENCURSES) -shared $(OBJNCURSES) $(LIBNCURSES)

$(NAMEOPENGL):	$(OBJOPENGL)
		$(CC) -o $(NAMEOPENGL) -shared $(OBJOPENGL) $(LIBOPENGL)

clean:
	$(RM) $(OBJSDL)
	$(RM) $(OBJNCURSES)
	$(RM) $(OBJOPENGL)

fclean:	clean
	$(RM) $(NAMESDL)
	$(RM) $(NAMENCURSES)
	$(RM) $(NAMEOPENGL)

re:	fclean all

.PHONY: all clean fclean re
