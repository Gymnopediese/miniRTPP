/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 11:22:13 by albaud            #+#    #+#             */
/*   Updated: 2023/05/10 21:29:53 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"
#define MIN_SCOLOR 0.01

int	ray_trace_basic(t_scene *scene, t_ray *r)
{
	t_hit		hit;
	t_v3		col;

	hit.obj = 0;
	if (hit_obj(scene, r, &hit))
	{
		col = v_nmult(&hit.obj->color, 255);
		r->origin = hit.ray.origin;
		r->direction = v_rm(&r->origin, &scene->light->pos);
		v_normalize(&r->origin);
		v_normalize(&r->direction);
		col = v_nmult(&col, fabs(v_dotp(&r->origin, &r->direction) / 3)
				* scene->light->ratio + 1 - scene->light->ratio);
		if (v_dotp(&r->origin, &r->direction) < 0)
			col = v_nmult(&col, 0);
		return (v_tocol(&col));
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
