/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bphilago <bphilago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 19:51:41 by albaud            #+#    #+#             */
/*   Updated: 2023/05/16 14:10:36 by bphilago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shapes.h"\

void	sphere_function(t_ray *ray, double *sols)
{
	t_v3		oc;
	t_eqt2		eq;

	oc = ray->origin;
	eq.a = v_dotp(&ray->direction, &ray->direction);
	eq.b = 2 * v_dotp(&oc, &ray->direction);
	eq.c = v_dotp(&oc, &oc) - 1;
	find_delta(&eq);
	if (eq.delta < 0)
		return ;
	sols[0] = (-eq.b + sqrt(eq.delta)) / (2.0 * eq.a); // TODO stocker la racine et le diviseur pour opti
	sols[1] = (-eq.b - sqrt(eq.delta)) / (2.0 * eq.a);
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

void	sphere_normal(t_hit *hit, int mode)
{
	(void)mode;
	hit->normal = hit->ray.origin;
}

int	no_condition(const t_ray *local)
{
	(void) local;
	return (1);
}
