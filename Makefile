# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: albaud <albaud@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/19 14:57:19 by albaud            #+#    #+#              #
#    Updated: 2023/05/11 12:00:28 by albaud           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= miniRT
#MAIN 		= dammier.c shapes/transform.c shapes/rotation.c shapes/inverse.c utils/threading.c disperse.c main.c ray_tracing.c uvmapping.c background/gradient.c gui/gui.c parser/atoi_life.c parser/init_objs.c parser/init_shapes.c parser/init_shapes_2.c parser/parser.c parser/parser_utils.c shapes/cone.c shapes/cylindre.c shapes/hyperboloid.c shapes/hyperboloid2.c shapes/matrix.c shapes/paraboloid.c shapes/paraboloid2.c shapes/plan.c shapes/sphere.c utils/debug.c utils/errors.c utils/inputs.c utils/iterate_objects.c utils/v_utils.c
MAIN		= $(wildcard srcs/*.c) $(wildcard srcs/*/*.c)  #TOREMOVEEEEEEEE
OBJS		= $(patsubst srcs/%.c, objs/%.o, $(MAIN))
#OBJS		= ${MAIN:.c=.o}
LIB 		= libs/koflibc/libft.a libs/vector3d/vlib.a
CC			= /usr/bin/gcc -g
CFLAGS		= -Wall -Wextra -Werror
FRAMEWORK	= -framework OpenGL -framework AppKit
LIBS		= -Llibs/minilibx_macos -lmlx -Llibs/koflibc -lft
SANITIZE	= -fsanitize=address -static-libsan
OBJ_DIR		= objs
SRC_DIR		= srcs


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

all		: ${NAME}

$(NAME)	: ${OBJS}
		make -C libs/koflibc
		make -C libs/vector3d
		make -C libs/minilibx_macos
		echo ${OBJS}
		${CC} ${CFLAGS} ${LIBS} ${FRAMEWORK} -o ${NAME} ${OBJS} ${LIB}

c		:
		find *.c */*.c | grep -v *vectors* | grep -v *minilibx_macos* | tr '\n' ' ' 

recompile :
	make re -C koflibc
	make re -C minilibx_macos
	make re

clean	:
		rm -rf $(OBJ_DIR)
fclean	:	clean
		rm -f ${NAME} 
re:		fclean all

lclean	: fclean
		rm -f ${LIB}
relib	: lclean all

leak	: fclean ${LIB}
		${CC} ${CFLAGS} ${SANITIZE} ${MINILIBX} -o ${NAME} ${MAIN} ${LIB}

run		: all
		./miniRT rt_files/test.rt