/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bphilago <bphilago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 11:22:13 by albaud            #+#    #+#             */
/*   Updated: 2023/05/16 11:51:57 by bphilago         ###   ########.fr       */
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

// TODO Ajouter la ++
