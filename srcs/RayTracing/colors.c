/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bphilago <bphilago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 18:11:47 by albaud            #+#    #+#             */
/*   Updated: 2023/05/15 15:36:23 by bphilago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"
#define MIN_SCOLOR 0.01


// // S = origine de la lumirere, O = impact, R = point pour le rayon de reflexion
// // !casse la normal, a utiliser apres le calcule de la luminosite
// void	compute_reflexion(t_v3 *tmp_color, t_v3 *light_origine, t_v3 *normal)
// {
// 	double	beta;
// 	double	angle;
// 	t_v3	plan_son;

// 	angle = v_angle(light_origine, normal); // TODO Duplicate code with brightness;
// 	v_cnmult(normal, cos(angle));
// 	beta = cos(angle) * cos(angle);
// 	plan_son = v_mult(light_origine, normal);
	
// 	// Calculer l'intersection des 2 plans.
// }

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
		current_link = current_link->next;
	}
}
