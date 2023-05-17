/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plan.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 12:50:34 by albaud            #+#    #+#             */
/*   Updated: 2023/05/17 13:05:17 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	plan_normal(t_hit *hit, t_ray *normal, int mode)
{
	(void) mode;
	(void) hit;
	normal->direction = ((t_v3){0, 0, -1});
	normal->origin = ((t_v3){0, 0, 0});
}

t_v3	plan_uv(t_v3 *hit, int mode)
{
	t_v3	res;

	(void) mode;
	res.x = hit->x;
	res.y = hit->y;
	return (res);
}

void	plan_function(const t_ray *ray, double *sols)
{
	double	denom;
	t_v3	p0l0;
	double	t;
	int		norm;

	norm = 1;
	if (v_dotp(&ray->direction, &(t_v3){0, 0, 1}) < 0)
		norm = -1;
	denom = v_dotp(&(t_v3){0, 0, norm}, &ray->direction);
	if (denom <= 1e-6)
		return ;
	p0l0 = v_rm(&(t_v3){0, 0, 0}, &ray->origin);
	t = v_dotp(&p0l0, &(t_v3){0, 0, norm}) / denom;
	if (t <= 1e-6)
		return ;
	sols[0] = t;
}
