/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylindre.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 12:50:34 by albaud            #+#    #+#             */
/*   Updated: 2023/05/17 13:04:43 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	cylindre_cap(t_ray *ray, double *sols)
{
	double	denom;
	t_v3	pt1;
	t_v3	pt2;
	t_v3	norm;
	t_eqt2	e;

	norm = (t_v3){0, 0, 1};
	if (v_dotp(&ray->direction, &norm) < 0)
		norm = (t_v3){0, 0, -1};
	denom = v_dotp(&norm, &ray->direction);
	if (denom < 0)
		return ;
	pt1 = v_rm(&(t_v3){0, 0, 1}, &ray->origin);
	pt2 = v_rm(&(t_v3){0, 0, -1}, &ray->origin);
	e.x1 = v_dotp(&pt1, &norm) / denom;
	e.x2 = v_dotp(&pt2, &norm) / denom;
	pt1 = v_ponline(&ray->origin, &ray->direction, e.x1);
	pt2 = v_ponline(&ray->origin, &ray->direction, e.x2);
	pt1 = v_rm(&pt1, &(t_v3){0, 0, 1});
	pt2 = v_rm(&pt2, &(t_v3){0, 0, -1});
	if (v_dotp(&pt1, &pt1) < 1)
		sols[2] = e.x1;
	if (v_dotp(&pt2, &pt2) < 1)
		sols[3] = e.x2;
}

void	cylindre_function(t_ray *ray, double *sols)
{
	t_eqt2	e;

	cylindre_cap(ray, sols);
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

void	cylindre_normal(t_hit *hit, t_ray *normal, int mode)
{
	if (mode == 3)
	{
		normal->direction = ((t_v3){0, 0, -1});
		normal->origin = ((t_v3){0, 0, 0});
	}
	else if (mode == 2)
	{
		normal->direction = ((t_v3){0, 0, 1});
		normal->origin = ((t_v3){0, 0, 0});
	}
	else
	{
		normal->direction = hit->ray.origin;
		normal->origin = ((t_v3){0, 0, hit->ray.origin.z});
	}
}

t_v3	cylindre_uv(t_v3 *hit, int mode)
{
	if (mode > 1)
		return (*hit);
	return ((t_v3){atan(hit->y / hit->x) / PI * 2, hit->z, 0});
}

int	cylindre_condition(const t_ray *local)
{
	return (fabs(local->origin.z) < 1.01);
}
