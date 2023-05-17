# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: albaud <albaud@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/19 14:57:19 by albaud            #+#    #+#              #
#    Updated: 2023/05/17 13:49:07 by albaud           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= miniRT
MAIN		= srcs/main.c srcs/Background/gradient.c srcs/Bonus/disperse.c srcs/Bonus/obj_parser.c srcs/Parser/atoi_life.c srcs/Parser/bonus_parser.c srcs/Parser/init_objs.c srcs/Parser/init_shapes.c srcs/Parser/init_shapes_2.c srcs/Parser/parser.c srcs/Parser/parser_utils.c srcs/RayTracing/colors.c srcs/RayTracing/hit_objects.c srcs/RayTracing/ray_tracing.c srcs/Shapes/capsule.c srcs/Shapes/cone.c srcs/Shapes/cube.c srcs/Shapes/cylindre.c srcs/Shapes/hyperboloid.c srcs/Shapes/hyperboloid2.c srcs/Shapes/obj.c srcs/Shapes/paraboloid.c srcs/Shapes/paraboloid2.c srcs/Shapes/plan.c srcs/Shapes/sphere.c srcs/Shapes/torus.c srcs/ShapesUtils/bonus.c srcs/ShapesUtils/general.c srcs/ShapesUtils/poly_solver.c srcs/ShapesUtils/poly_solver2.c srcs/ShapesUtils/poly_solver3.c srcs/ShapesUtils/poly_solver4.c srcs/ShapesUtils/shapes_utils.c srcs/TransformationMatriciel/global_local_convertion.c srcs/TransformationMatriciel/inverse.c srcs/TransformationMatriciel/m_mult.c srcs/TransformationMatriciel/matrix.c srcs/TransformationMatriciel/rotation.c srcs/TransformationMatriciel/transform.c srcs/Utils/debug.c srcs/Utils/errors.c srcs/Utils/get_mlx.c srcs/Utils/init.c srcs/Utils/inputs.c srcs/Utils/iterate_objects.c srcs/Utils/v_utils.c
OBJS		= $(patsubst srcs/%.c, objs/%.o, $(MAIN))
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
		${CC} ${CFLAGS} ${LIBS} ${FRAMEWORK} -o ${NAME} ${OBJS} ${LIB}

c		:
		find srcs/*.c srcs/*/*.c | grep -v *vectors* | grep -v *minilibx_macos* | tr '\n' ' ' 

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