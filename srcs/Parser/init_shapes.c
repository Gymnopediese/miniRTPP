/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shapes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 14:06:36 by albaud            #+#    #+#             */
/*   Updated: 2023/05/16 10:11:43 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	init_sphere(char **argv, t_obj *obj)
{
	if (ft_strtablen(argv) < 4)
		error("Wrong arguments number for a sphere\
: <pos> <radius> <scale>");
	obj->pos = ft_atovedo(argv[1], 0, 0);
	obj->scale.x = ft_atodor(argv[2], 0, 0);
	obj->scale.y = obj->scale.x;
	obj->scale.z = obj->scale.x;
	if (obj->scale.y < 0)
		error("Wrong diameter for a sphere");
	obj->color = ft_atovei(argv[3], 0, 255);
	bonus_parser(argv, obj, 4);
}

void	init_plan(char **argv, t_obj *obj)
{
	if (ft_strtablen(argv) < 4)
		error("Wrong arguments number for a plan or cube\
: <pos> <orientation> <color>");
	obj->pos = ft_atovedo(argv[1], 0, 0);
	obj->orientation = ft_atovedo(argv[2], -1, 1);
	obj->color = ft_atovei(argv[3], 0, 255);
	bonus_parser(argv, obj, 4);
}

void	init_cylindre(char **argv, t_obj *obj)
{
	ft_putnbrn(ft_strtablen(argv));
	if (ft_strtablen(argv) < 6)
		error("Wrong arguments number for a cylindrique object\
: <pos> <orientation> <radius> <hauteur> <color>");
	obj->pos = ft_atovedo(argv[1], 0, 0);
	obj->orientation = ft_atovedo(argv[2], -1, 1);
	obj->scale.x = ft_atodor(argv[3], 0, 0);
	obj->scale.y = obj->scale.x;
	if (obj->scale.x < 0)
		error("Wrong diameter for a cylindrique object");
	obj->scale.z = ft_atodor(argv[4], 0, 0);
	if (obj->scale.z < 0)
		error("Wrong hight for a cylindrique object");
	obj->color = ft_atovei(argv[5], 0, 255);
	bonus_parser(argv, obj, 6);
}

void	init_cone(char **argv, t_obj *obj)
{
	if (ft_strtablen(argv) < 6)
		error("Wrong arguments number for a cone");
	obj->pos = ft_atovedo(argv[1], 0, 0);
	obj->orientation = ft_atovedo(argv[2], -1, 1);
	obj->scale.x = ft_atodor(argv[3], 0, 0);
	obj->scale.y = obj->scale.x;
	if (obj->scale.x < 0)
		error("Wrong diameter for a cone");
	obj->scale.z = ft_atodor(argv[4], 0, 0);
	if (obj->scale.z < 0)
		error("Wrong hight for a cone");
	obj->color = ft_atovei(argv[5], 0, 255);
	bonus_parser(argv, obj, 6);
}
