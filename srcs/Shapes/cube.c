/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 12:50:34 by albaud            #+#    #+#             */
/*   Updated: 2023/05/16 11:28:38 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	cube_normal(t_hit *hit, int mode)
{
	if (mode == 0)
		hit->normal = (t_v3){0, 0, 1};
	if (mode == 1)
		hit->normal = (t_v3){0, 0, -1};
	if (mode == 2)
		hit->normal = (t_v3){0, 1, 0};
	if (mode == 3)
		hit->normal = (t_v3){0, -1, 0};
	if (mode == 4)
		hit->normal = (t_v3){1, 0, 0};
	if (mode == 5)
		hit->normal = (t_v3){-1, 0, 0};
}

t_v3	cube_uv(t_v3 *hit, int mode)
{
	if (mode < 2)
		return ((t_v3){fabs(hit->x), fabs(hit->y), 0});
	if (mode < 4)
		return ((t_v3){fabs(hit->x), fabs(hit->z), 0});
	return ((t_v3){fabs(hit->y), fabs(hit->z), 0});
}

t_v3	get_xy(t_v3 *normal, t_v3 *p0l0)
{
	t_v3	res;

	if (normal->x)
	{
		res.x = p0l0->y;
		res.y = p0l0->z;
	}
	else if (normal->y)
	{
		res.x = p0l0->x;
		res.y = p0l0->z;
	}
	else
	{
		res.x = p0l0->x;
		res.y = p0l0->y;
	}
	return (res);
}

void	cube_inter(const t_ray *ray, double *sols, t_v3 *normal)
{
	t_v3	p0l0;
	t_v3	pos;
	double	denom;
	double	t;
	t_v3	xy;

	pos = *normal;
	if (v_dotp(&ray->direction, normal) < 0)
		v_cnmult(normal, -1);
	denom = v_dotp(normal, &ray->direction);
	if (denom <= 1e-6)
		return ;
	p0l0 = v_rm(&pos, &ray->origin);
	t = v_dotp(&p0l0, normal) / denom;
	p0l0 = v_ponline(&ray->origin, &ray->direction, t);
	xy = get_xy(normal, &p0l0);
	if (t <= 1e-6 || xy.x < -1 || xy.y < -1 || xy.x > 1 || xy.y > 1)
		return ;
	sols[0] = t;
}

void	cube_function(const t_ray *ray, double *sols)
{
	cube_inter(ray, &sols[0], &(t_v3){0, 0, 1});
	cube_inter(ray, &sols[1], &(t_v3){0, 0, -1});
	cube_inter(ray, &sols[2], &(t_v3){0, 1, 0});
	cube_inter(ray, &sols[3], &(t_v3){0, -1, 0});
	cube_inter(ray, &sols[4], &(t_v3){1, 0, 0});
	cube_inter(ray, &sols[5], &(t_v3){-1, 0, 0});
}
