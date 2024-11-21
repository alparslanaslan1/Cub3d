NAME	= cub3D

CC		= cc

RM		= rm -rf

CFLAGS	= -Wall -Wextra -Werror -g

SRC = 	src/main.c				\
		src/control.c			\
		src/exit.c				\
		src/utils.c				\
		src/control2.c			\
		src/init.c				\
		src/game_play.c			\
		src/ray.c				\
		src/movement.c			\
		src/create.c			\
		src/utils2.c			\

LIBFT = libft/libft.a
MLX = minilibx/libmlx.a

LINUX_OBJ_FLAG = -Imlx_linux -O3 -DESC=65307 -DW=119 -DS=115 -DA=97 -DD=100 -DRIGHT=65363 -DLEFT=65361
MACOS_OBJ_FLAG = -Imlx -DESC=53 -DW=13 -DS=1 -DA=0 -DD=2 -DRIGHT=124 -DLEFT=123

MACOS_FLAG = -framework OpenGL -framework AppKit
LINUX_FLAG = -Imlx_linux -lXext -lX11 -lm -lz
OBJ_DIR = .objs


ifeq ($(shell uname), Linux)
	MLXFLAG = $(LINUX_FLAG)
	CFLAGS += $(LINUX_OBJ_FLAG)
else
	MLXFLAG = $(MACOS_FLAG)
	CFLAGS += $(MACOS_OBJ_FLAG)
endif

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

all : $(NAME)

$(NAME): $(MLX) $(LIBFT) $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBFT) $(MLX) $(MLXFLAG)

$(OBJ_DIR)/%.o : %.c
	@mkdir -p $(@D)
	@echo -e "\033[2J\033[H"
	@echo "\033[1;32mCompiling : \033[1;34m$<\033[0m"
	@sleep 0.01
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C libft

$(MLX):
	@$(MAKE) -C minilibx

clean:
	@$(RM) $(OBJ_DIR)
	@$(MAKE) -C libft clean

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C libft fclean
	@$(MAKE) -C minilibx clean
re: fclean all

norm:
	@if norminette $(SRC) libft inc | grep -q "Error"; then \
		echo "Norminette: \033[31m[KO]\033[0m"; \
		norminette $(SRC) libft inc | grep "Error"; \
	else \
		echo "Norminette: libft \033[32m[OK]\033[0m"; \
	fi

.PHONY: all fclean clean re
