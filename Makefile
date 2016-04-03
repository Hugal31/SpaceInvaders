##
## Makefile for pong
##
## Made by Alexis Bertholom
## Login   bertho_d
## Email   <alexis.bertholom.jd@gmail.com>
##
## Started on  Wed Jul  1 22:37:51 2015 Alexis Bertholom
## Last update Thu Jul  9 14:38:38 2015 Alexis Bertholom
##

NAME		= pong

LIBD		= lib/
SRCD		= src/
INCD		= include/

_LIB_ERRORD	= error/
_LIB_DISPLAYD	= display/
_LIB_CONTEXTD	= $(_LIB_DISPLAYD)context/

_LIB_CONTEXTSRC	= $(_LIB_CONTEXTD)Input.cpp \
		  $(_LIB_CONTEXTD)SDLContext.cpp \
		  $(_LIB_CONTEXTD)SDLWindow.cpp \
		  $(_LIB_ERRORD)SDLError.cpp

_LIB_DISPLAYSRC	= $(_LIB_DISPLAYD)Image.cpp \
		  $(_LIB_DISPLAYD)SDLDisplay.cpp \
		  $(_LIB_CONTEXTSRC)

_LIB_ERRORSRC	= $(_LIB_ERRORD)FileError.cpp \
		  $(_LIB_ERRORD)GenericError.cpp \
		  $(_LIB_ERRORD)LogicError.cpp \
		  $(_LIB_ERRORD)StdError.cpp

_LIB_SRC	= $(_LIB_DISPLAYSRC) \
		  $(_LIB_ERRORSRC)

LIBSRC		= $(_LIB_SRC:%.cpp=$(LIBD)$(SRCD)%.cpp)

SRC		= $(SRCD)main.cpp \
		  $(LIBSRC)

OBJ		= $(SRC:%.cpp=%.o)

CXXINCLUDES	+= -I$(INCD)
CXXINCLUDES	+= -I$(LIBD)$(INCD)
CXXINCLUDES	+= -I$(LIBD)$(INCD)$(_LIB_ERRORD)
CXXINCLUDES	+= -I$(LIBD)$(INCD)$(_LIB_DISPLAYD)
CXXINCLUDES	+= -I$(LIBD)$(INCD)$(_LIB_CONTEXTD)

CXXFLAGS	+= -std=gnu++11
CXXFLAGS	+= -pedantic
CXXFLAGS	+= -Wall
CXXFLAGS	+= -Wextra
CXXFLAGS	+= -O2

LDFLAGS		+= -lSDL2
LDFLAGS		+= -lSDL2main

CXX		= g++
RM		= rm -vf

all: $(NAME)

$(NAME): $(OBJ)
	@echo $(CXX) $(LDFLAGS) -o $(NAME)
	@$(CXX) $(OBJ) $(LDFLAGS) -o $(NAME)

clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)

re: fclean
	$(MAKE)

%.o: %.cpp
	@echo $(CXX) -c $(CXXFLAGS) $<
	@$(CXX) -c $(CXXFLAGS) $(CXXINCLUDES) $< -o $@
