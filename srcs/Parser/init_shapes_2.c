/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shapes_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 10:19:08 by albaud            #+#    #+#             */
/*   Updated: 2023/05/17 09:22:35 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	init_torus(char **argv, t_obj *obj)
{
	if (ft_strtablen(argv) < 4)
		error("Wrong arguments number for a torus/donut\
: <pos> <orientation> <color>");
	obj->pos = ft_atovedo(argv[1], 0, 0);
	obj->orientation = ft_atovedo(argv[2], -1, 1);
	obj->color = ft_atovedo(argv[3], 0, 255);
	bonus_parser(argv, obj, 4);
}

void	init_object(char **argv, t_obj *obj)
{
	if (ft_strtablen(argv) < 3)
		error("Wrong arguments number for a object: <pos> <.obj>");
	obj->pos = ft_atovedo(argv[1], 0, 0);
	obj->orientation = (t_v3){0, 0, 0};
	obj->color = (t_v3){0, 0, 0};
	obj->obj = obj_parser(argv[2]);
	bonus_parser(argv, obj, 3);
}
