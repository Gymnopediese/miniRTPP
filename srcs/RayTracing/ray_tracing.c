/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bphilago <bphilago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 11:22:13 by albaud            #+#    #+#             */
/*   Updated: 2023/05/17 13:20:31 by bphilago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"
#define MIN_SCOLOR 0.01

int	ray_trace_basic(t_scene *scene, t_ray *r)
{
	t_hit		hit;

	hit.obj = 0;
	if (hit_obj(scene, r, &hit))
	{
		v_cnmult(&hit.color, 255);
		return (v_tocol(&hit.color));
	}
	return (-1);
}

int	ray_trace_phong(t_scene *scene, t_ray *r)
{
	t_hit		hit;
	t_v3		ambiance_color;
	t_v3		col;

	hit.obj = 0;
	if (hit_obj(scene, r, &hit))
	{
		col = (t_v3){0, 0, 0};
		v_cunit(&hit.normal);
		brightness(&col, &hit, scene);
		ambiance_color = v_mult(&scene->ambiance->color, &hit.color);
		v_cadd(&col, &ambiance_color);
		v_cnmult(&col, 255);
		return (v_tocol(&col));
	}
	return (-1);
}
