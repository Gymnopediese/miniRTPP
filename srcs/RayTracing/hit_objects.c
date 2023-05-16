/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_objects.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 18:19:16 by albaud            #+#    #+#             */
/*   Updated: 2023/05/16 17:47:16 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	hit_any_obj(const t_scene *scene, t_ray *r, double d)
{
	t_list	*objects;
	t_hit	hit;

	objects = scene->objects;
	while (objects)
	{
		if (get_point(r, objects->data, &hit, 0)
			&& v_dist(&r->origin, &hit.ray.origin) < d
			&& v_dist(&r->origin, &hit.ray.origin) > 0)
		{
			return (1);
		}
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
		if (get_point(r, obj, hit, 0))
			min = is_nearer(min, r, hit, &cobj);
		objects = objects->next;
	}
	if (min == MAXFLOAT)
		return (0);
	get_point(r, cobj, hit, 1);
	return (1);
}
