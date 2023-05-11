/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 19:51:41 by albaud            #+#    #+#             */
/*   Updated: 2023/05/10 21:38:33 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shapes.h"

int	is_sphere_hit(const t_ray *r, const t_obj *sphere)
{
	t_eqt2		eq;
	t_ray		ray;
	t_v3		oc;

	global_to_local(r, &ray, sphere);
	oc = ray.origin;
	eq.a = v_dotp(&ray.direction, &ray.direction);
	eq.b = 2 * v_dotp(&oc, &ray.direction);
	eq.c = v_dotp(&oc, &oc) - pow(sphere->diametre / 2, 2);
	find_delta(&eq);
	if (eq.delta < 0)
		return (0);
	return (1);
}

void	get_sphere_intersect(t_eqt2 *eq, t_ray *ray, const t_obj *sphere)
{
	t_v3		oc;

	oc = ray->origin;
	eq->a = v_dotp(&ray->direction, &ray->direction);
	eq->b = 2 * v_dotp(&oc, &ray->direction);
	eq->c = v_dotp(&oc, &oc) - pow(sphere->diametre / 2, 2);
	find_delta(eq);
	if (eq->delta < 0)
		return ;
	find_xs(eq);
}

int	get_sphere_hit_point(const t_ray *r, const t_obj *sphere, t_hit *hit)
{
	t_eqt2		eq;
	t_ray		ray;
	double		dist;

	global_to_local(r, &ray, sphere);
	get_sphere_intersect(&eq, &ray, sphere);
	if (eq.delta < 0)
		return (0);
	hit->obj = sphere;
	if (eq.x1 <= eq.x2)
		dist = eq.x1;
	else
		dist = eq.x2;
	if (dist < 0)
		return (0);
	hit->ray.origin = v_ponline(&ray.origin, &ray.direction, dist);
	hit->ray.origin = m_3mult(&hit->ray.origin, sphere->transform);
	hit->normal = v_rm(&hit->ray.origin, &sphere->pos);
	return (1);
}
