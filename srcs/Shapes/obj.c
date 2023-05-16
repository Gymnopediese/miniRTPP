/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 19:35:19 by albaud            #+#    #+#             */
/*   Updated: 2023/05/16 01:25:26 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

// t_v3	e1, e2, s, h, q;
// float	a, f, u, v;
double	triange_function(t_ray *ray, t_triangle *triangle)
{
	t_v3	vects[5];
	float	vars[4];

	vects[0] = v_rm(&triangle->b, &triangle->a);
	vects[1] = v_rm(&triangle->c, &triangle->a);
	vects[3] = v_v3mult(&ray->direction, &vects[1]);
	vars[0] = v_dotp(&vects[0], &vects[3]);
	if (vars[0] > -0.00001 && vars[0] < 0.00001)
		return (-1);
	vars[1] = 1 / vars[0];
	vects[2] = v_rm(&ray->origin, &triangle->a);
	vars[2] = vars[1] * (v_dotp(&vects[2], &vects[3]));
	if (vars[2] < 0.0 || vars[2] > 1.0)
		return (-1);
	vects[4] = v_v3mult(&vects[2], &vects[0]);
	vars[3] = vars[1] * v_dotp(&ray->direction, &vects[4]);
	if (vars[3] < 0.0 || vars[2] + vars[3] > 1.0)
		return (-1);
	return (vars[1] * v_dotp(&vects[1], &vects[4]));
}

double	get_obj_hit(t_ray *local, const t_obj *obj, int *ind)
{
	int		i;
	double	min;
	double	t;

	i = -1;
	min = MAXFLOAT;
	while (++i < obj->obj->triangle_length)
	{
		t = triange_function(local, &obj->obj->triangle[i]);
		if (t < min && t >= 0)
		{
			*ind = i;
			min = t;
			break ;
		}
	}
	return (min);
}

int	get_obj_point(const t_ray *ray, const t_obj *obj, t_hit *hit, int full)
{
	t_ray	local;
	int		ind;
	double	min;

	global_to_local(ray, &local, obj);
	min = get_obj_hit(&local, obj, &ind);
	if (min == MAXFLOAT)
		return (-1);
	hit->ray.origin = v_ponline(&local.origin, &local.direction, min);
	if (full)
	{
		hit->normal = obj->obj->normales[ind];
		local_to_global(&hit->normal, obj);
	}
	local_to_global(&hit->ray.origin, obj);
	hit->color = (t_v3){(double)ind / obj->obj->triangle_length, 0, 0};
	hit->obj = obj;
	return (1);
}
