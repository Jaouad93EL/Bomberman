CC      = gcc
SDL_FLAGS = -I/usr/include/SDL2 -D_REENTRANT
CFLAGS  = -Wextra -Wall -Werror $(SDL_FLAGS)
LDFLAGS = -lpthread 

ifeq ($(shell uname), Linux)
	LDFLAGS  += -L/usr/lib/x86_64-linux-gnu -lSDL2 -lSDL2_image -lSDL2_ttf
endif

ifeq ($(shell uname), Darwin)
	LDFLAGS += -lSDL2 -lSDL2_image -lSDL2_ttf
endif


RM		= rm -f
TARGET	= bomberman

SRC		=	$(wildcard *.c)

OBJ		= $(SRC:.c=.o)

.PHONY: all $(TARGET) clean fclean re

all : $(TARGET)

$(TARGET): $(OBJ) 
	@$(CC) $(OBJ) -o $@ $(LDFLAGS) 

/%.o : /%.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(TARGET)

re : fclean all