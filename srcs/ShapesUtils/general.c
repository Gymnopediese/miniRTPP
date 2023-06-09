/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 18:55:09 by albaud            #+#    #+#             */
/*   Updated: 2023/05/16 16:46:24 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	get_solution(const t_ray *local,
	const t_obj *obj, t_hit *hit, double sols[4])
{
	int		i;
	int		ind;
	double	min;

	min = MAXFLOAT;
	i = -1;
	while (++i < 6)
	{
		if (sols[i] < 0 || sols[i] > min || sols[i] != sols[i])
			continue ;
		hit->ray.origin = v_ponline(&local->origin, &local->direction, sols[i]);
		if (obj->funcs->condition(hit))
		{
			min = sols[i];
			ind = i;
		}
	}
	if (min == MAXFLOAT)
		return (-1);
	hit->ray.origin = v_ponline(&local->origin, &local->direction, min);
	return (ind);
}

void	get_full_data(const t_obj *obj, t_hit *hit, int ind)
{
	t_ray	normal;

	obj->funcs->normal(hit, &normal, ind);
	local_to_global(&normal.origin, obj);
	local_to_global(&normal.direction, obj);
	hit->normal = v_rm(&normal.direction, &normal.origin);
	get_color(obj, hit, ind);
}

int	get_point(const t_ray *ray, const t_obj *obj, t_hit *hit, int full)
{
	t_ray	local;
	double	sols[6];
	double	ind;

	if (obj->id == OBJECT)
		return (get_obj_point(ray, obj, hit, full));
	ind = -1;
	while (++ind < 6)
		sols[(int)ind] = -1;
	global_to_local(ray, &local, obj);
	obj->funcs->function(&local, sols);
	ind = get_solution(&local, obj, hit, sols);
	if (ind == -1)
		return (0);
	if (full)
		get_full_data(obj, hit, ind);
	local_to_global(&hit->ray.origin, obj);
	hit->obj = obj;
	return (1);
}
