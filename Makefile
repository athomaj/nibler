##
## Makefile for Nibbler in /home/ferrei_e/cpp_nibbler
## 
## Made by Ferreira Cintia
## Login   <ferrei_e@epitech.net>
## 
## Started on  Wed Mar 11 16:04:57 2015 Ferreira Cintia
## Last update Sun Apr  5 23:04:26 2015 julien athomas
##

SRC=		Coordinates.cpp				\
		Map.cpp					\
		Nibbler.cpp				\
		Snake.cpp				\
		Stats.cpp				\
		Parser.cpp				\
		main.cpp				\

NAME=		nibbler

CC=		g++

RM=		rm -f

OBJ=		$(SRC:.cpp=.o)

CXXFLAGS=	-W -Wall -Werror -Wextra

LIB=		-ldl

LIBRARY=	library/library

all:	$(NAME) $(LIBRARY)

$(NAME):$(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LIB)

$(LIBRARY):
	make -C library

clean:
	$(RM) $(OBJ)
	make clean -C library

fclean:	clean
	$(RM) $(NAME)
	make fclean -C library

re:	fclean all

.PHONY: all clean fclean re
