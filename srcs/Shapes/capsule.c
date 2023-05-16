/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   capsule.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 12:50:34 by albaud            #+#    #+#             */
/*   Updated: 2023/05/13 23:24:01 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	capsule_cap(t_ray *ray, double *sols, t_v3 *pos)
{
	t_v3		oc;
	t_eqt2		eq;

	oc = v_rm(&ray->origin, pos);
	eq.a = v_dotp(&ray->direction, &ray->direction);
	eq.b = 2 * v_dotp(&oc, &ray->direction);
	eq.c = v_dotp(&oc, &oc) - 1;
	find_delta(&eq);
	if (eq.delta < 0)
		return ;
	sols[0] = (-eq.b + sqrt(eq.delta)) / (2.0 * eq.a);
	sols[1] = (-eq.b - sqrt(eq.delta)) / (2.0 * eq.a);
}

void	capsule_function(t_ray *ray, double *sols)
{
	t_eqt2	e;

	capsule_cap(ray, &sols[2], &(t_v3){0, 0, 1});
	capsule_cap(ray, &sols[4], &(t_v3){0, 0, -1});
	e.a = ray->direction.x * ray->direction.x
		+ ray->direction.y * ray->direction.y;
	e.b = 2 * (ray->direction.x * ray->origin.x
			+ ray->direction.y * ray->origin.y);
	e.c = ray->origin.x * ray->origin.x
		+ ray->origin.y * ray->origin.y - 1;
	find_delta(&e);
	if (e.delta < 0)
		return ;
	sols[0] = (-e.b + sqrt(e.delta)) / (2.0 * e.a);
	sols[1] = (-e.b - sqrt(e.delta)) / (2.0 * e.a);
}

void	capsule_normal(t_hit *hit, int mode)
{
	if (mode == 2)
		hit->normal = ((t_v3){
				hit->ray.origin.x,
				hit->ray.origin.y,
				hit->ray.origin.z - 1});
	else if (mode == 3)
		hit->normal = ((t_v3){
				hit->ray.origin.x,
				hit->ray.origin.y,
				hit->ray.origin.z + 1});
	else
		hit->normal = ((t_v3){-hit->ray.origin.x, -hit->ray.origin.y, 0});
}

t_v3	capsule_uv(t_v3 *hit, int mode)
{
	t_v3		uv;
	t_v3		pos;

	if (mode > 2)
	{
		(void) mode;
		pos = *hit;
		uv.x = 0.5 + (atan2f(pos.z, pos.x) / (2 * PI));
		uv.y = 0.5 + (asinf(pos.y) / (PI));
		uv.y -= (int)uv.y;
		uv.x -= (int)uv.x;
		return (uv);
	}
	return ((t_v3){atan(hit->y / hit->x), hit->z, 0});
}

int	capsule_condition(const t_ray *local)
{
	return (fabs(local->origin.z) < 1.01
		|| (fabs(local->origin.z) < 2.01
			&& sqrt(local->origin.x * local->origin.x
				+ local->origin.y * local->origin.y) < 0.9999));
}
