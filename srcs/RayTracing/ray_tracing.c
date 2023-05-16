/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 11:22:13 by albaud            #+#    #+#             */
/*   Updated: 2023/05/16 08:38:44 by albaud           ###   ########.fr       */
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

void	ray_trace(t_scene *scene, t_ray *r, t_v3 *l_color, t_v3 *s_color)
{
	t_hit	hit;
	t_v3	tmp_color;
	t_obj	*obj_hit;

	obj_hit = 0;
	if (v_norm(s_color) < MIN_SCOLOR)
		return ;
	if (hit_obj(scene, r, &hit))
	{
		*s_color = obj_hit->color;
		tmp_color = obj_hit->color;
		//brightness(&tmp_color, &r->origin, &hit, scene);
		v_cmult(&tmp_color, s_color); //Prendre en compte que la brillance renvoie une partie des rayons dans tous les cas !!!
		//v_cnmult(&tmp_color, disperssion); // Quantite de rayon qui attendra la camera
		v_cnmult(&r->direction, -1);
		// disperssion *= A faire;
		v_cmult(s_color, &obj_hit->color);
		v_cadd(l_color, &tmp_color);
		tmp_color = v_mult(&scene->ambiance->color, &obj_hit->color);
		v_cadd(l_color, &tmp_color);
		//ray_trace(scene, &hit.ray, l_color, s_color, disperssion, ++iter);
	}
}
