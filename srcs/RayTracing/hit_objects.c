/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_objects.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bphilago <bphilago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 18:19:16 by albaud            #+#    #+#             */
/*   Updated: 2023/05/15 12:27:50 by bphilago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	hit_any_obj(const t_scene *scene, t_ray *r)
{
	t_list	*objects;
	t_obj	*obj;

	objects = scene->objects;
	while (objects)
	{
		obj = objects->data;
		if (scene->is_intersections[obj->id - SHAPE_START](r, obj))
			return (1);
		objects = objects->next;
	}
	return (0);
}

double	is_nearer(double min, t_ray *r, t_hit *hit, t_obj **obj)
{
	double	t;

	t = v_dist(&r->origin, &hit->ray.origin);
	if (t < min)
	{
		*obj = (t_obj *)hit->obj;
		return (t);
	}
	return (min);
}

int	hit_obj(t_scene *scene, t_ray *r, t_hit *hit)
{
	t_list	*objects;
	t_obj	*obj;
	t_obj	*cobj;
	double	min;

	min = MAXFLOAT;
	objects = scene->objects;
	while (objects)
	{
		obj = objects->data;
		if (scene->get_hit_point[obj->id - SHAPE_START](r, obj, hit))
			min = is_nearer(min, r, hit, &cobj);
		objects = objects->next;
	}
	if (min == MAXFLOAT)
		return (0);
	scene->get_hit_point[cobj->id - 3](r, cobj, hit);
	return (1);
}
