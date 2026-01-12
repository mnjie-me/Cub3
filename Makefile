# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anruiz-d <anruiz-d@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/05 01:21:59 by anruiz-d          #+#    #+#              #
#    Updated: 2026/01/12 14:46:08 by anruiz-d         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# --- Project Name --- #

NAME		:=	cub3D
NAME_BONUS	:=	cub3D_bonus

# --- Directories --- #

DIR_SRCS	:=	srcs
DIR_OBJS	:=	objs
DIR_OBJS_B	:=	objs_bonus
DIR_INC		:=	includes
DIR_BONUS	:=	bonus
DIR_LIB		:=	libft
DIR_MLX_U	:=	mlx_linux
DIR_MLX_M	:=	mlx

# --- Libft and Mlx --- #

LIBFT	:=	$(DIR_LIB)/libft.a
MLX_U	:=	$(DIR_MLX_U)/libmlx_Linux.a
MLX_M	:=	$(DIR_MLX_M)/libmlx.a

# --- Source Files --- #

SRC_FILES = parser/parse_scene.c \
			parser/utils_scene.c \
			parser/utils_elements.c \
            parser/parse_elements.c \
			parser/parse_map.c \
			parser/utils_map.c \
            parser/validate_map.c \
			parser/utils_validate.c \
			engine/init_data.c \
            engine/raycast.c \
			engine/utils.c \
			engine/draw_wall.c \
			engine/textures.c \
			engine/player.c \
			clean/utils_clean.c \
			clean/utils_free.c

SRC_MAIN	= cub3.c

SRC_FILES_BONUS	=	bonus/cub3d_bonus.c	\
					bonus/minimap_bonus.c \
					bonus/draw_map_bonus.c \
					bonus/draw_fov_bonus.c \
					bonus/utils_bonus.c \
					bonus/draw_player_bonus.c \
					bonus/draw_lines_fov_bonus.c \
					bonus/raycast_minimap_bonus.c 

# --- Object Files --- #

SRCS 		:=	$(addprefix $(DIR_SRCS)/, $(SRC_FILES))
SRCS_BONUS	:= 	$(addprefix $(DIR_SRCS)/, $(SRC_FILES_BONUS))
OBJS		:=	$(addprefix $(DIR_OBJS)/, $(SRC_FILES:.c=.o))
OBJS_MAIN	:=	$(addprefix $(DIR_OBJS)/, $(SRC_MAIN:.c=.o)) $(OBJS)
OBJS_BONUS	:=	$(addprefix $(DIR_OBJS_B)/, $(notdir $(SRC_FILES_BONUS:.c=.o))) $(OBJS)

# --- Compiler and tools --- #

CC 		:= cc
CFLAGS 	:= -Wall -Wextra -Werror
MKDIR	:= mkdir -p

# --- Include --- # 

INCLUDES = -I$(DIR_INC) -I$(DIR_INC)/bonus -I$(DIR_LIB)

# --- OS Detect --- # 

UNAME_S	:=	$(shell uname -s)

# --- MLX by SO --- #

ifeq ($(UNAME_S), Darwin)
	MLX_DIR		:=	$(DIR_MLX_M)
	MLX_LIB		:=	$(MLX_M)
	MLX_INC		:=	-I$(DIR_MLX_M)
	MLX_LINK	:=	-L$(DIR_MLX_M) -lmlx -framework OpenGL -framework AppKit
else
	MLX_DIR		:=	$(DIR_MLX_U)
	MLX_LIB		:=	$(MLX_U)
	MLX_INC		:=	-I$(DIR_MLX_U)
	MLX_LINK	:=	-L$(DIR_MLX_U) -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz
endif

INCLUDES += $(MLX_INC)

# --- Rules --- #

all: 	$(NAME)

bonus:	$(NAME_BONUS)

${NAME}: $(OBJS_MAIN) $(LIBFT) $(MLX_LIB)
		@$(CC) $(CFLAGS) $(OBJS_MAIN) -L$(DIR_LIB) -lft $(MLX_LINK) -o $(NAME)
		@echo "Built $(NAME)"

$(NAME_BONUS):	$(OBJS_BONUS) $(LIBFT) $(MLX_LIB)
				@$(CC) $(CFLAGS) $(OBJS_BONUS) -L$(DIR_LIB) -lft $(MLX_LINK) -o $(NAME_BONUS)
				@echo "Built $(NAME_BONUS)"

# --- Compile libft and mlx --- #

$(LIBFT):
		@$(MAKE) -C $(DIR_LIB)

$(MLX_LIB):
		@$(MAKE) -C $(MLX_DIR)

# --- Create objs/%.o --- #

$(DIR_OBJS)/%.o: $(DIR_SRCS)/%.c
	@$(MKDIR) $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(DIR_OBJS_B)/%.o: $(DIR_SRCS)/$(DIR_BONUS)/%.c
	@$(MKDIR) $(DIR_OBJS_B)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
		@$(MAKE) -C $(DIR_LIB) clean --no-print-directory --silent
		@rm -f ${OBJS}
		@rm -f $(OBJS_MAIN)
		@rm -f $(OBJS_BONUS)

fclean: clean
		@$(MAKE) -C $(DIR_LIB) fclean --no-print-directory --silent
		@rm -rf $(DIR_OBJS)
		@rm -rf $(DIR_OBJS_B)
		@rm -f $(NAME) $(NAME_BONUS)

re:		fclean all

re_bonus:	fclean bonus

.PHONY: all bonus clean fclean re re_bonus
