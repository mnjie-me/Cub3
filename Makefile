NAME	= cub3

SRCS 	= srcs/cub3.c srcs/parser/parse_scene.c srcs/parser/utils_scene.c srcs/parser/utils_elements.c \
			srcs/parser/parse_elements.c srcs/parser/parse_map.c srcs/parser/utils_map.c \
			srcs/parser/validate_map.c srcs/parser/utils_validate.c srcs/engine/raycast.c

OBJS 	= ${SRCS:.c=.o}

CC 		= gcc
CFLAGS 	= -Wall -Wextra -Werror

INCLUDES = -I mlx_linux -I libft -I includes -I usr/include

.c.o:
		@${CC} ${CFLAGS} ${INCLUDES} -c -o $@ $<

all: 	${NAME}

${NAME}: ${OBJS}
		@make re -C libft --no-print-directory
		@make -C mlx_linux --no-print-directory
		@$(CC) $(CFLAGS) ${OBJS} -Llibft -lft -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz ${INCLUDES} -o ${NAME}

${NAME_BONUS}: ${OBJSB}
		@make re -C libft --no-print-directory
		@make -C mlx_linux --no-print-directory
		@$(CC) $(CFLAGS) ${OBJSB} -Llibft -lft -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz ${INCLUDES} -o ${NAME_BONUS}
clean:
		@make clean -C libft --no-print-directory
		@rm -f ${OBJS}
		@rm -f ${OBJSB}

fclean: clean
		@make fclean -C libft
		@rm -f $(NAME)
		@rm -f $(NAME_BONUS)

re:		fclean all

bonus: ${NAME_BONUS}

re_bonus: fclean bonus

.PHONY: all clean fclean re re_bonus bonus