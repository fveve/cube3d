NAME = cub3d

CC = cc

CFLAGS += -g -Wall -Wextra -Werror  -I/usr/include -Imlx_linux -IInclude  -Imlx

HEADER = cube3d.h

LIB = -Lmlx_linux -lmlx_Linux -lXext -lX11 -lm  -IO3 -lz -L/usr/lib

ERROR = check_error

GNL = get_next_line

MAIN = main

INITIALIZATION = parse_map init_data

TOOLS = exit_manager tools debug gnl_tools

SRC = $(addsuffix .c, $(addprefix src/GNL/, $(GNL)))\
		$(addsuffix .c, $(addprefix src/Initialization/, $(INITIALIZATION)))\
		$(addsuffix .c, $(addprefix src/Tools/, $(TOOLS)))\
		$(addsuffix .c, $(addprefix src/Main/, $(MAIN)))\
		$(addsuffix .c, $(addprefix src/Error/, $(ERROR)))\

OBJ = $(SRC:c=o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "\033[0;32mCube3d Compiled !"
	@$(CC) $(CFLAGS)  $(OBJ) $(LIB) -o $(NAME)
	@echo "\n\033[0mCube3d to execute the program !"

%.o: %.c
	@printf "\033[0;33mGenerating Cube3d objects... %-33.33s\r\n" $@
	@${CC} ${CFLAGS} -c $< -o $@

clean:
	@echo "\nRemoving binaries..."
	@rm -f $(OBJ)
	@echo "\033[0m"

fclean:
	@echo "Deleting objects..."
	@rm -f $(OBJ)
	@echo "\nDeleting executable..."
	@rm -f $(NAME)
	@echo "\033[0m"

re: fclean all


.PHONY: clean fclean re 