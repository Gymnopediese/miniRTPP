/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bphilago <bphilago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 11:22:13 by albaud            #+#    #+#             */
/*   Updated: 2023/05/15 15:46:20 by bphilago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"
#define MIN_SCOLOR 0.01

int	ray_trace_basic(t_scene *scene, t_ray *r)
{
	t_hit		hit;
	t_v3		ambiance_color;
	t_v3		col;

	hit.obj = 0;
	if (hit_obj(scene, r, &hit))
	{
		col = (t_v3){0, 0, 0};
		brightness(&col, &hit.obj->color, &hit, scene);
		ambiance_color = v_mult(&scene->ambiance->color, &hit.obj->color);
		v_cadd(&col, &ambiance_color);
		v_cnmult(&col, 255);
		int tmp = v_tocol(&col);
		if (tmp != 0)
			return (tmp);
		else
			return tmp;
	}
	return (-1);
}

