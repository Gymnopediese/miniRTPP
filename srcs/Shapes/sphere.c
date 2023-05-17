/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 19:51:41 by albaud            #+#    #+#             */
/*   Updated: 2023/05/17 13:12:36 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shapes.h"

void	sphere_function(t_ray *ray, double *sols)
{
	t_v3		oc;
	t_eqt2		eq;
	double		r;

	oc = ray->origin;
	eq.a = v_dotp(&ray->direction, &ray->direction);
	eq.b = 2 * v_dotp(&oc, &ray->direction);
	eq.c = v_dotp(&oc, &oc) - 1;
	find_delta(&eq);
	if (eq.delta < 0)
		return ;
	r = sqrt(eq.delta);
	sols[0] = (-eq.b + r) / (2.0 * eq.a);
	sols[1] = (-eq.b - r) / (2.0 * eq.a);
}

t_v3	sphere_uv(t_v3 *hit, int mode)
{
	t_v3		uv;
	t_v3		pos;

	(void) mode;
	pos = *hit;
	uv.x = 0.5 + (atan2f(pos.z, pos.x) / (2 * PI));
	uv.y = 0.5 + (asinf(pos.y) / (PI));
	uv.y -= (int)uv.y;
	uv.x -= (int)uv.x;
	return (uv);
}

void	sphere_normal(t_hit *hit, t_ray *normal, int mode)
{
	(void)mode;
	normal->direction = hit->ray.origin;
	normal->origin = ((t_v3){0, 0, 0});
}

int	no_condition(const t_ray *local)
{
	(void) local;
	return (1);
}
