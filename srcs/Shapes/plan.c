/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plan.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 12:50:34 by albaud            #+#    #+#             */
/*   Updated: 2023/05/11 01:41:07 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

// int	plan_intersect(t_ray *r, t_obj *plan, t_hit *hit)
// {
// 	double	x;
// 	t_ray	ray;

// 	global_to_local(r, &ray, plan);
// 	x = (v_norm(&plan->pos) - v_dotp(&plan->orientation, &ray.origin))
// 		/ v_dotp(&plan->orientation, &ray.direction);
// 	hit->normal = plan->orientation;
// 	hit->ray.origin = v_ponline(&ray.origin, &ray.direction, x);
// 	//local_to_global(&hit->normal, plan);
// 	hit->obj = plan;
// 	local_to_global(&hit->ray.origin, plan);
// 	return (1);
// }

int	get_plan_hit_point(const t_ray *ray, const t_obj *plan, t_hit *hit)
{
	double	denom;
	t_v3	p0l0;
	double	t;
	t_ray	r;

	global_to_local(ray, &r, plan);
	denom = v_dotp(&plan->orientation, &r.direction);
	if (denom <= 1e-6)
		return (0);
	p0l0 = v_mult(&r.origin, &plan->pos);
	t = v_dotp(&p0l0, &plan->orientation) / denom;
	if (denom <= 1e-6)
		return (0);
	hit->ray.origin = v_ponline(&r.origin, &r.direction, t);
	local_to_global(&hit->ray.origin, plan);
	hit->normal = plan->orientation;
	hit->obj = plan;
	return (1);
}

// a = plan->orientation.x;
// 	b = plan->orientation.y;
// 	c = plan->orientation.z;
// 	d = - (a * plan->pos.x + b * plan->pos.y + c * plan->pos.y);
// 	x = - (a * ray->origin.x + b * ray->origin.y + c * ray->origin.z - d)
// 		/ (a * ray->direction.x + b * ray->direction.y
// 			+ c * ray->direction.z - d);
// 	//printf("%f %f %f %f %f\n", a, b, c, d, x);
// 	*hit = v_ponline(&ray->origin, &ray->direction, x);
// 	//print_vector(*hit, "salame: ");

// t_hit	*sphere_reflection(t_hit *hit, t_v3 *origine)
// {
// 	double	bc;
// 	t_v3	ba;
// 	t_v3	c;
// 	t_v3	res;

// 	ba = v_rm(origine, &hit->ray.origin);
// 	bc = cos(v_angle(&ba, &hit->normal)) * v_dist(&hit->ray.origin, origine);
// 	c = v_unit(&hit->normal);
// 	c = v_ponline(&hit->ray.origin, &c, bc);
// 	res = v_rm(&c, origine);
// 	v_cnmult(&res, 2);
// 	hit->ray.direction = v_rm(&res, &hit->ray.origin);
// 	return (hit);
// }
