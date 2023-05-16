/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bphilago <bphilago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 18:11:47 by albaud            #+#    #+#             */
/*   Updated: 2023/05/16 11:42:33 by bphilago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"
#define MIN_SCOLOR 0.01


// S = origine de la lumirere, O = impact, R = point pour le rayon de reflexion
// !casse la normal, a utiliser apres le calcule de la luminosite
void	compute_reflexion(t_v3 *result, const t_v3 *light_origine, t_v3 *normal)
{
	t_v3	projection;
	double	cos_angle;

	cos_angle = cos(v_angle(light_origine, normal));
	v_cnmult(normal, cos_angle);
	projection = v_nmult(light_origine, v_dotp(light_origine, normal) / pow(cos_angle, 2));
	*result = v_nmult(normal, 2);
	v_crm(result, &projection);
}

void	brightness(t_v3 *final_color, const t_v3 *object_color,
	const t_hit *hit, const t_scene *scene)
{
	t_list	*current_link;
	t_light	*current_light;
	t_v3	tmp_color;
	t_ray	r;

	current_link = scene->lights;
	
	while(current_link)
	{
		current_light = current_link->data;
		if (current_light->ratio == 0)
			continue;
		r.direction = v_rm(&current_light->pos, &hit->ray.origin);
		r.origin = hit->ray.origin;
		if (hit_any_obj(scene, &r))
		{
			current_link = current_link->next;
			continue;
		}
		tmp_color = *object_color;
		v_cmult(&tmp_color, &current_light->color);
		t_v3 v1 = v_unit(&r.direction); // TODO Faire propre
		t_v3 v2 = v_unit(&hit->normal);
		double tmp = v_angle(&v1, &v2);
		v_cnmult(&tmp_color, cos(tmp));
		v_cadd(final_color, &tmp_color);
		//t_v3 reflexion;
		//compute_reflexion(&reflexion, &current_light->pos, &v2);
		//t_v3 angle = v_angle(&reflexion, &hit->ray.origin);
		current_link = current_link->next;
	}
}
