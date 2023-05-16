/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:52:40 by albaud            #+#    #+#             */
/*   Updated: 2023/05/12 07:37:30 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

//this file will be removed before the correction

void	print_vector(t_v3 a, char *name)
{
	printf("%s(%f, %f, %f)\n", name, a.x, a.y, a.z);
}

void	print_camera(t_camera *a)
{
	ft_putendl("printing camera");
	print_vector(a->pos, "position:\t");
	print_vector(a->orientaion, "orientation:\t");
	printf("fov:\t\t%f\n", a->fov);
}

void	print_ambiance(t_ambiance *a)
{
	ft_putendl("printing ambiance");
	printf("ratio:\t\t%f\n", a->ratio);
	print_vector(a->color, "color:\t\t");
}

void	print_light(t_light *a)
{
	ft_putendl("printing light");
	print_vector(a->pos, "position\t");
	printf("ratio:\t\t%f\n", a->ratio);
	print_vector(a->color, "color\t\t");
}

void	print_object(t_obj *a)
{
	printf("printing object id %i\n", a->id);
	print_vector(a->pos, "position\t");
	print_vector(a->scale, "scale\t\t");
	print_vector(a->orientation, "orientation\t");
	print_vector(a->color, "color:\t\t");
}

void	print_scene(t_scene *i)
{
	t_list	*l;

	l = i->objects;
	print_ambiance(i->ambiance);
	print_camera(i->camera);
	print_light(i->light);
	while (l)
	{
		print_object((t_obj *)l->data);
		l = l->next;
	}
}
